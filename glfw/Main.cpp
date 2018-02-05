#include "Main.h"
#include "Scene.h"



void Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void Cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
bool Init_window(GLFWwindow** window, int w, int h, bool is_resizeble);
bool Init_GLEW(GLFWwindow* window);
void CalculateFrameRate();

int window_width = 800;
int window_height = 600;
float FPS;

Scene* scene;



//главная функция
int main()
{
	int frames_count = 0;
	GLFWwindow* window;

	if (!Init_window(&window, window_width, window_height, 1))
		return -1;

	if (!Init_GLEW(window))
		return -1;

	//загружаем объекты
	scene = new Scene(window_width, window_height);

	//привязываем к окну обработчик нажатия клавиш
	glfwSetKeyCallback(window, Key_callback);

	//захват курсора
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPosCallback(window, Cursor_position_callback);

	//игровой цикл
	while (!glfwWindowShouldClose(window))
	{
		scene->Render();
		glfwSwapBuffers(window);
		//CalculateFrameRate();

		glfwPollEvents();
		scene->ProcessPressedKeys();
	}

	return 0;
}




//создаем окно
bool Init_window(GLFWwindow** window, int w, int h, bool is_resizeble)
{
	//настройка glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, is_resizeble);

	//создание окна
	*window = glfwCreateWindow(w, h, "Kongyne", NULL/*glfwGetPrimaryMonitor()*/, NULL);
	if (window == nullptr)
	{
		glfwTerminate();
		std::cout << "Failed to create window";
		std::system("pause");
		return 0;
	}
	std::cout << "window successfuly created";

	glfwMakeContextCurrent(*window);
	return 1;
}


//инициализируем opengl
bool Init_GLEW(GLFWwindow* window)
{
	int width, height;
	GLint nrAttributes;

	//инициализация GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		std::system("pause");
		return 0;
	}

	//максимальное число передаваемых параметров
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "\r\n\r\nGLEW succesfully initialized\r\nMaximum nr of vertex attributes supported: " << nrAttributes;

	//сообщаем opengl размер отрисовочного окна
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	return 1;
}




//отклик на нажатие клавиш
void Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	scene->Key_callback(window, key, scancode, action, mode);
}


void Cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	scene->Cursor_position_callback(window, xpos, ypos);
}




//расчет фпс
void CalculateFrameRate()
{
	//Ниже мы создадим несколько статичных переменных, т.к. хотим, чтобы они сохраняли своё
	//значение после завершения работы ф-ии. Мы могли бы сделать их глобальными, но это будет
	//излишним.

	static float framesPerSecond = 0.0f;    //наши фпс
	static float lastTime = 0.0f;           //Тут хранится время, прошедшее с последнего кадра

											//Тут мы получаем текущий tick count и умножаем его на 0.001 для конвертации из миллисекунд в секунды.
	float currentTime = clock() * 0.001f;

	//Увеличиваем счетчик кадров
	framesPerSecond++;

	//Теперь вычтем из текущего времени последнее запомненное время. Если результат больше единицы,
	//это значит, что секунда прошла и нужно вывести новый FPS.
	if (currentTime - lastTime > 1.0f)
	{
		//Устанавливаем lastTime в текущее время. Теперь оно будет использоватся как предидущее время
		//для след. секунды.
		lastTime = currentTime;

		// Установим FPS для вывода:
		FPS = framesPerSecond;
		cout << "\r\n" << FPS;

		//Сбросим FPS
		framesPerSecond = 0;
	}
}