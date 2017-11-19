#include "Mesh.h"




//подразумеввется, что VAO уже привязан
Mesh::Mesh(GLfloat* vert, int v_count, GLuint* ind, int i_count)
{
	Constructor("", vert, v_count, ind, i_count, nullptr, nullptr);
}


Mesh::Mesh(string nm, GLfloat* vert, int v_count, GLuint* ind, int i_count)
{
	Constructor(nm, vert, v_count, ind, i_count, nullptr, nullptr);
}


Mesh::Mesh(string nm, GLfloat* vert, int v_count, GLuint* ind, int i_count, mat4* local_mat, mat4* model_mat)
{
	Constructor(nm, vert, v_count, ind, i_count, local_mat, model_mat);
}


void Mesh::Constructor(string nm, GLfloat* vert, int v_count, GLuint* ind, int i_count, mat4* local_mat, mat4* model_mat)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	name = nm;

	//привязываем буфферы
	vertices_count = v_count;
	if (vert != nullptr)
		vertices = vert;
	else
		vertices = new GLfloat[vertices_count];

	indices_count = i_count;
	if (ind != nullptr)
		indices = ind;
	else
		indices = new GLuint[indices_count];

	Bind_buffers();

	//привязываем матрицы
	if (local_mat != nullptr)
		local = *local_mat;
	if (model_mat != nullptr)
		model = *model_mat;

	/*настройка того, как вершинному шейдеру интерпретировать вх данные
	[какой аргумент шейдера настраивать], [длина операнда], [формат данных], [нормализовать данные?], [длина блока], [смещение начала буффера] */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//отвязываем буфферы
	glBindVertexArray(0);
}


Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &EBO);

	delete vertices;
	delete indices;
	delete texture;
}




void Mesh::Bind_buffers() 
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(indices), indices, GL_DYNAMIC_DRAW);
}


void Mesh::Draw(int& screen_width, int& screen_height, mat4& view, mat4& projection)
{
	glBindVertexArray(VAO);

	glUniformMatrix4fv(shader->m_uniforms[SHADER_LOCAL_MATRIX], 1, GL_FALSE, glm::value_ptr(local));
	glUniformMatrix4fv(shader->m_uniforms[SHADER_MODEL_MATRIX], 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(shader->m_uniforms[SHADER_VIEW_MATRIX], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(shader->m_uniforms[SHADER_PROJECTION_MATRIX], 1, GL_FALSE, glm::value_ptr(projection));
	
	//отрисовка
	glBindTexture(GL_TEXTURE_2D, texture->tex_pointer);
	glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
}


void Mesh::Bind_texture(Texture* tex) 
{
	texture = tex;
}


void Mesh::Bind_shader(Shader* sh)
{
	shader = sh;
}