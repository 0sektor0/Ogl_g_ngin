#include "Main.h"
#include "Texture.h"
#include "Shader.h"

using namespace glm;
using namespace std;

#define VERTIVES_VECTOR_LEN 8



class Mesh
{
public:
	Mesh::Mesh(string nm, GLfloat* vert, int v_count, GLuint* ind, int i_count, mat4* local_mat, mat4* model_mat);
	Mesh::Mesh(GLfloat* vert, int verticies_count, GLuint* ind, int indices_count);
	Mesh::Mesh(string nm, GLfloat* vert, int v_count, GLuint* ind, int i_count);
	void Draw(int& screen_width, int& screen_height, mat4& view, mat4& projection);
	void Bind_shader(Shader* shader);
	void Bind_texture(Texture* tex);
	virtual ~Mesh();

	std::string name;
	mat4 local;
	mat4 model;


private:
	void Constructor(string name, GLfloat* vert, int v_count, GLuint* ind, int i_count, mat4* local_mat, mat4* model_mat);
	void Bind_buffers();

	GLuint VBO; //Vertex object buffer, буффер, который хранит вершины
	GLuint EBO; //Element buffer object, буффер, который хранит индексы вершин
	GLuint VAO; //Vertex atribute object буффер, который хранит настройки четния вершин и VBO ассоциированные с этими вершинами
	Texture* texture;
	GLfloat* vertices;
	GLuint* indices;
	Shader* shader;
	int vertices_count;
	int indices_count;
};

