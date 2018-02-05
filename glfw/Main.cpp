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



//������� �������
int main()
{
	int frames_count = 0;
	GLFWwindow* window;

	if (!Init_window(&window, window_width, window_height, 1))
		return -1;

	if (!Init_GLEW(window))
		return -1;

	//��������� �������
	scene = new Scene(window_width, window_height);

	//����������� � ���� ���������� ������� ������
	glfwSetKeyCallback(window, Key_callback);

	//������ �������
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPosCallback(window, Cursor_position_callback);

	//������� ����
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




//������� ����
bool Init_window(GLFWwindow** window, int w, int h, bool is_resizeble)
{
	//��������� glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, is_resizeble);

	//�������� ����
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


//�������������� opengl
bool Init_GLEW(GLFWwindow* window)
{
	int width, height;
	GLint nrAttributes;

	//������������� GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		std::system("pause");
		return 0;
	}

	//������������ ����� ������������ ����������
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "\r\n\r\nGLEW succesfully initialized\r\nMaximum nr of vertex attributes supported: " << nrAttributes;

	//�������� opengl ������ ������������� ����
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	return 1;
}




//������ �� ������� ������
void Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	scene->Key_callback(window, key, scancode, action, mode);
}


void Cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	scene->Cursor_position_callback(window, xpos, ypos);
}




//������ ���
void CalculateFrameRate()
{
	//���� �� �������� ��������� ��������� ����������, �.�. �����, ����� ��� ��������� ���
	//�������� ����� ���������� ������ �-��. �� ����� �� ������� �� �����������, �� ��� �����
	//��������.

	static float framesPerSecond = 0.0f;    //���� ���
	static float lastTime = 0.0f;           //��� �������� �����, ��������� � ���������� �����

											//��� �� �������� ������� tick count � �������� ��� �� 0.001 ��� ����������� �� ����������� � �������.
	float currentTime = clock() * 0.001f;

	//����������� ������� ������
	framesPerSecond++;

	//������ ������ �� �������� ������� ��������� ����������� �����. ���� ��������� ������ �������,
	//��� ������, ��� ������� ������ � ����� ������� ����� FPS.
	if (currentTime - lastTime > 1.0f)
	{
		//������������� lastTime � ������� �����. ������ ��� ����� ������������� ��� ���������� �����
		//��� ����. �������.
		lastTime = currentTime;

		// ��������� FPS ��� ������:
		FPS = framesPerSecond;
		cout << "\r\n" << FPS;

		//������� FPS
		framesPerSecond = 0;
	}
}