#include "Main.h"
#include "Texture2d.h"
#include "Shader.h"


using namespace glm;
using namespace std;

#define VERTIVES_VECTOR_LEN 8




class Mesh
{
public:
	Mesh::Mesh(GLfloat* vert, int verticies_count, GLuint* ind, int indices_count);
	Mesh::Mesh(GLfloat* vert, int v_count, GLuint* ind, int i_count, Shader* sh);
	Mesh::Mesh(string nm, GLfloat* vert, int v_count, GLuint* ind, int i_count);
	void Render(const mat4&model, const mat4& view, const mat4& projection);
	void Bind_texture(Texture2d* tex);
	void Bind_shader(Shader* sh);
	virtual ~Mesh();

	std::string name;
	mat4 local; //базис объекта


private:
	void Constructor(string name, GLfloat* vert, int v_count, GLuint* ind, int i_count, mat4* local_mat, Shader* sh);
	void Bind_buffers();

	GLuint VBO; //Vertex object buffer, буффер, который хранит вершины
	GLuint EBO; //Element buffer object, буффер, который хранит индексы вершин
	GLuint VAO; //Vertex atribute object буффер, который хранит настройки четния вершин и VBO ассоциированные с этими вершинами
	Texture2d* texture;
	GLfloat* vertices;
	GLuint* indices;
	int vertices_count;
	int indices_count;
	Shader* shader;
};

