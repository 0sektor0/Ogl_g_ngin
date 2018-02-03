#include "Scene.h"




Scene::Scene(const int& window_width, const int& window_height)
{
	camera = new Camera(window_width, window_height);
	Load_objects();
}


Scene::~Scene()
{

}




void Scene::Render()
{
	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 0.0f); //установка состояния очистки
	glClear(GL_COLOR_BUFFER_BIT); //очистка

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render(camera->view, camera->projection);

	glDisable(GL_DEPTH_TEST);
}


void Scene::Load_objects()
{
	GLfloat vertices[] = {
		// Позиции            // Цвета                  // Текстурные координаты
		0.5f,  0.5f, 0.1f,    1.0f, 1.0f, 1.0f, 0.5f,   1.0f, 1.0f,   // Верхний правый
		0.5f, -0.5f, 0.1f,    1.0f, 1.0f, 1.0f, 0.5f,   1.0f, 0.0f,   // Нижний правыйglfw.rc
		-0.5f, -0.5f, 0.1f,   1.0f, 1.0f, 1.0f, 0.5f,   0.0f, 0.0f,   // Нижний левыйglfw
		-0.5f,  0.5f, 0.1f,   1.0f, 1.0f, 1.0f, 0.5f,   0.0f, 1.0f    // Верхний левый
	};
	GLuint indices[] = {
		2, 3, 0,
		0, 1, 2
	};

	Object* new_object = new Object();
	objects.insert(objects.end(), new_object);
	
	new_object = new Object();
	new_object->RotateY(1.5f);
	objects.insert(objects.end(), new_object);

	new_object = new Object();
	new_object->RotateX(1.5f);
	objects.insert(objects.end(), new_object);

	objects.insert(objects.end(), new Object("D:\\Textures\\table.png", vertices, 36, indices, 9));

	selected_object = objects[0];
}




void Scene::Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	int buf;
	glm::vec3 old_vec;
	glm::vec3 movement_vec;

	if (action == GLFW_PRESS)
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;


		case GLFW_KEY_W:
			selected_object->MoveForward(0.5f);
			break;
			
		case GLFW_KEY_S:
			selected_object->MoveForward(-0.5f);
			break;

		case GLFW_KEY_E:
			selected_object->RotateY(0.5f);
			break;
			

		case GLFW_KEY_R:
			selected_object->RotateX(-0.5f);
			break;

		case GLFW_KEY_O:
			camera->MoveForward();
			break;

		case GLFW_KEY_L:
			camera->MoveBackward();
			break;

		case GLFW_KEY_K:
			camera->MoveLeft();
			break;

		case GLFW_KEY_SEMICOLON:
			camera->MoveRight();
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
			if (buf > 0 && action == GLFW_PRESS)
			{
				if (++selected_object_index >= buf)
					selected_object_index = 0;

				selected_object = objects[selected_object_index];
				cout << "\r\nobject " << selected_object_index << " selected";
			}
			else
				cout << "\r\nthere is no objects to select\r\n";
			break;

		case GLFW_KEY_P:
			//camera->LookRight(0.1f);
			break;

		case GLFW_KEY_I:
			//camera->LookRight(-0.1f);
			break;


		case GLFW_KEY_C:
			cout << "\r\n\r\ncamera_x: " << *camera->camera_x 
				 << "\r\ncamera_y: " << *camera->camera_y 
				 << "\r\ncamera_z: " << *camera->camera_z;
			break;

		case GLFW_KEY_B:
			cout << "\r\n\r\nobj_x: " << *selected_object->object_x
				<< "\r\nobj_y: " << *selected_object->object_y
				<< "\r\nobj_z: " << *selected_object->object_z;
			break;

		default:
			break;
		}
}


void Scene::Cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}