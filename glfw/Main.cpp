#include "Main.h"
#include "Mesh.h"




void Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
bool Init_window(GLFWwindow** window, int w, int h, bool is_resizeble);
void Draw_frame(Shader& shader, vector<Mesh*>& objects);
bool Init_GLEW(GLFWwindow* window);
void Load_objets(Shader* shader);




int screen_width = 800;
int screen_height = 600;
int selected_object_index = 0; 
vector <Mesh*> objects;
Mesh* selected_object;




//главная функция
int main()
{
	GLFWwindow* window;
	Shader* shader;

	if (!Init_window(&window, screen_width, screen_height, 1))
		return -1;

	if (!Init_GLEW(window))
		return -1;

	//загружаем объекты
	shader = new Shader("shader");
	Load_objets(shader);

	//привязываем к окну обработчик нажатия клавиш
	glfwSetKeyCallback(window, Key_callback);

	//игровой цикл
	while (!glfwWindowShouldClose(window))
	{
		Draw_frame(*shader, objects);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//завершение работы
	glfwTerminate();
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
	*window = glfwCreateWindow(w, h, "LearnOpenGL", NULL/*glfwGetPrimaryMonitor()*/, NULL);
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
	int buf;

	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;

	case GLFW_KEY_W:
		selected_object->model = glm::translate(selected_object->model, vec3(0.0f, 0.0f, -0.1f));
		break;

	case GLFW_KEY_S:
		selected_object->model = glm::translate(selected_object->model, vec3(0.0f, 0.0f, +0.1f));
		break;

	case GLFW_KEY_A:
		selected_object->model = glm::translate(selected_object->model, vec3(-0.1f, 0.0f, 0));
		break;

	case GLFW_KEY_D:
		selected_object->model = glm::translate(selected_object->model, vec3(+0.1f, 0.0f, 0.0f));
		break;

	case GLFW_KEY_E:
		selected_object->local = glm::rotate(selected_object->local, -0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
		break;
		
	case GLFW_KEY_1:
		if (objects.size() > 0 && action == GLFW_PRESS)
		{
			if (--selected_object_index < 0)
				selected_object_index = 0;

			selected_object = objects[selected_object_index];
			cout << "\r\nobject " << selected_object_index << " selected";
		}
		else
			cout << "there is no objects to select\r\n";
		break;

	case GLFW_KEY_2:
		buf = objects.size();
		if (buf > 0 &&  action == GLFW_PRESS)
		{
			if (++selected_object_index >= buf)
				selected_object_index = 0;
			
			selected_object = objects[selected_object_index];
			cout << "\r\nobject " << selected_object_index << " selected";
		}
		else
			cout << "\r\nthere is no objects to select\r\n";
		break;

	default:
		break;
	}
}




//функция отрисовки
void Draw_frame(Shader& shader, vector <Mesh*>& objects)
{
	//cout << "\r\n" << (GLfloat)glfwGetTime();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //установка состояния очистки
	glClear(GL_COLOR_BUFFER_BIT); //очистка
		
	shader.Bind();

	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(45.0f, (float)(screen_width / screen_height), 0.1f, 100.0f);
	// 1/2: левая/правая координата усеченной прирамиды; 3/4 нижняя и верхняя границы пирамиды 
	//projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -0.1f, 1.0f);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Draw(screen_width, screen_height, view, projection);
}




void Load_objets(Shader* shader)
{
	vector <Texture*> textures;
	GLfloat vertices1[] = {
		// Позиции            // Цвета            // Текстурные координаты
		0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Верхний правый
		0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Нижний правый
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Нижний левый
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Верхний левый
	};
	GLfloat vertices2[] = {
		// Позиции            // Цвета            // Текстурные координаты
		0.5f,  1.0f, 0.0f,    1.0f, 0.0f, 0.0f,   0.75f, 1.0f,   // Верхний правый
		1.0f,  0.0f, 0.0f,    1.0f, 1.0f, 0.0f,   1.0f, 0.5f,    // средний правый
		0.5f, -1.0f, 0.0f,    0.0f, 1.0f, 0.0f,   0.75f, 0.0f,   // Нижний правый
		-0.5f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.25f, 0.0f,   // Нижний левый
		-1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.5f,    // средний левый
		-0.5f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.25f, 1.0f    // Верхний левый
	};
	GLuint indices1[] = {
		2, 3, 0,
		0, 1, 2
	};
	GLuint indices2[] = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 5,
		3, 4, 5,
	};

	objects.insert(objects.end(), new Mesh(&vertices1[0], 32, &indices1[0], 6));
	objects.insert(objects.end(), new Mesh(&vertices2[0], 48, &indices2[0], 12));

	 textures.insert(textures.end(), new Texture("D:\\Textures\\container.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE));
	 textures.insert(textures.end(), new Texture("D:\\Textures\\default.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE));

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Bind_shader(shader);
		objects[i]->Bind_texture(textures[i]);
	}

	selected_object = objects[0];
}