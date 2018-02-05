#include "Object.h"



void Object::InitObject(Shader* shader, Texture2d* texture, GLfloat* vertices, int vertices_count, GLuint* indices, int indices_count)
{
	mesh = new Mesh(vertices, 36, indices, 6);
	mesh->Bind_shader(shader);
	mesh->Bind_texture(texture);

	object_x = &model[3][0];
	object_y = &model[3][1];
	object_z = &model[3][2];
}


Object::Object()
{
	GLfloat* vertices = new GLfloat[36]{
		// Позиции            // Цвета                  // Текстурные координаты
		1.0f,  1.0f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // Верхний правый
		1.0f, -1.0f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // Нижний правыйglfw.rc
		-1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // Нижний левыйglfw
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // Верхний левый
	};
	GLuint* indices = new GLuint[6]{
		2, 3, 0,
		0, 1, 2
	};

	Shader* shader = new Shader("shader");
	Texture2d* texture = new Texture2d("D:\\Textures\\container.jpg");

	InitObject(shader, texture, vertices, 36, indices, 6);
}


Object::Object(char* file)
{
	GLfloat* vertices = new GLfloat[36]{
		// Позиции            // Цвета                  // Текстурные координаты
		1.0f,  1.0f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // Верхний правый
		1.0f, -1.0f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // Нижний правыйglfw.rc
		-1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // Нижний левыйglfw
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // Верхний левый
	};
	GLuint* indices = new GLuint[6]{
		2, 3, 0,
		0, 1, 2
	};

	Shader* shader = new Shader("shader");
	Texture2d* texture = new Texture2d(file);
	
	InitObject(shader, texture, vertices, 36, indices, 6);
}


Object::Object(char* tex_file, GLfloat* vertices, int vertices_count, GLuint* indices, int indices_count)
{
	Shader* shader = new Shader("shader");
	Texture2d* texture = new Texture2d(tex_file);
	
	InitObject(shader, texture, vertices, vertices_count, indices, indices_count);
}


Object::Object(Shader* shader, Texture2d* texture, GLfloat* vertices, int vertices_count, GLuint* indices, int indices_count)
{
	InitObject(shader, texture, vertices, vertices_count, indices, indices_count);
}


Object::~Object()
{
	delete mesh;
}




void Object::Render(const mat4& view, const mat4& projection)
{
	mesh->Render(model, view, projection);
}


void Object::Render(const mat4& model_matrix, const mat4& view, const mat4& projection)
{
	mesh->Render(model_matrix, view, projection);
}




void Object::Move(glm::vec3 vec)
{
	model = glm::translate(model, vec);
}


glm::mat4 Object::GetMovement(glm::vec3 vec)
{
	return glm::translate(model, vec);
}


void Object::Rotate(float angle, glm::vec3 vec)
{
	model = glm::rotate(model, -angle, vec);
}


glm::mat4 Object::GetRotation(float angle, glm::vec3 vec)
{
	return glm::rotate(model, -angle, vec);
}


void Object::MoveForward(float l)
{
	Move(glm::vec3(0.0f, 0.0f, l));
}


void Object::MoveRight(float l)
{
	Move(glm::vec3(l, 0.0f, 0.0f));
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