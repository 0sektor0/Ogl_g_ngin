#include "Object.h"



Object::Object()
{
	GLfloat vertices[] = {
		// Позиции            // Цвета                  // Текстурные координаты
		1.0f,  1.0f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // Верхний правый
		1.0f, -1.0f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // Нижний правыйglfw.rc
		-1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // Нижний левыйglfw
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // Верхний левый
	};
	GLuint indices[] = {
		2, 3, 0,
		0, 1, 2
	};

	Shader* shader = new Shader("shader");
	Texture2d* texture = new Texture2d("D:\\Textures\\container.jpg");

	mesh = new Mesh(&vertices[0], 36, &indices[0], 6);
	mesh->Bind_shader(shader);
	mesh->Bind_texture(texture);

	object_x = &model[3][0];
	object_y = &model[3][1];
	object_z = &model[3][2];
}


Object::Object(char* tex_file, GLfloat* vert, int verticies_count, GLuint* ind, int indices_count)
{
	Shader* shader = new Shader("shader");
	Texture2d* texture = new Texture2d(tex_file);

	mesh = new Mesh(vert, verticies_count, ind, indices_count);
	mesh->Bind_shader(shader);
	mesh->Bind_texture(texture);

	object_x = &model[3][0];
	object_y = &model[3][1];
	object_z = &model[3][2];
}


Object::~Object()
{
}


void Object::Render(const mat4& view, const mat4& projection)
{
	mesh->Render(model, view, projection);
}




void Object::Move(glm::vec3 vec)
{
	model = glm::translate(model, vec);
}


void Object::Rotate(float angle, glm::vec3 vec)
{
	model = glm::rotate(model, -angle, vec);
}


void Object::MoveForward(float l)
{
	Move(glm::vec3(0.0f, 0.0f, l));
}


void Object::RotateY(float angle)
{
	Rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
}


void Object::RotateX(float angle)
{
	Rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
}


void Object::RotateZ(float angle)
{
	Rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
}