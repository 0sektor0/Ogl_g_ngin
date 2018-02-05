#include "Mesh.h"



Mesh::Mesh(GLfloat* vert, int v_count, GLuint* ind, int i_count)
{
	Constructor("", vert, v_count, ind, i_count, nullptr, nullptr);
}


Mesh::Mesh(GLfloat* vert, int v_count, GLuint* ind, int i_count, Shader* sh)
{
	Constructor("", vert, v_count, ind, i_count, nullptr, sh);
}


Mesh::Mesh(string nm, GLfloat* vert, int v_count, GLuint* ind, int i_count)
{
	Constructor(nm, vert, v_count, ind, i_count, nullptr, nullptr);
}


void Mesh::Constructor(string nm, GLfloat* vert, int v_count, GLuint* ind, int i_count, mat4* local_mat, Shader* sh)
{
	//������� � ����������� ������ ��������� ���������
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//������� ������� �������� � ������
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	name = nm;

	//����������� ������ ������
	vertices_count = v_count;
	if (vert != nullptr)
		vertices = vert;
	else
		vertices = new GLfloat[vertices_count];

	//����������� ������ ��������
	indices_count = i_count;
	if (ind != nullptr)
		indices = ind;
	else
		indices = new GLuint[indices_count];

	Bind_buffers();

	//����������� �������
	if (local_mat != nullptr)
		local = *local_mat;

	if (sh != nullptr)
		shader = sh;

	/*layouts
	��������� ����, ��� ���������� ������� ���������������� �� ������
	[����� �������� ������� �����������], [����� ��������], [������ ������], [������������� ������?], [����� �����], [�������� ������ �������] */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 /*������ �����*/* sizeof(GLfloat), (GLvoid*)0);		// layout 0 xyz �������
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));	// layout 1 rgb 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));	// layout 2 xy ��������

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//���������� �������
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
	//����������� ������� � ��������� � ��� ������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(indices), indices, GL_DYNAMIC_DRAW);
}


void Mesh::Render(const mat4& model, const mat4& view, const mat4& projection)
{
	//��������
	shader->Bind();
	glBindVertexArray(VAO);

	//��������� ������ ������� � opengl
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	//�������� ������� ������� � ��������� �������
	glUniformMatrix4fv(shader->m_uniforms[SHADER_LOCAL_MATRIX], 1, GL_FALSE, glm::value_ptr(local));
	glUniformMatrix4fv(shader->m_uniforms[SHADER_MODEL_MATRIX], 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(shader->m_uniforms[SHADER_VIEW_MATRIX], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(shader->m_uniforms[SHADER_PROJECTION_MATRIX], 1, GL_FALSE, glm::value_ptr(projection));
	
	//���������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture->descriptor);
	glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);

	//���������� �������
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}


void Mesh::Bind_texture(Texture2d* tex) 
{
	texture = tex;
}


void Mesh::Bind_shader(Shader* sh)
{
	shader = sh;
}