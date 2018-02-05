#include "Main.h"
#include "Mesh.h"



class Object
{
public:
	Object(char* tex_file, GLfloat* vert, int verticies_count, GLuint* ind, int indices_count);
	Object(Shader* shader, Texture2d* tex, GLfloat* vert, int verticies_count, GLuint* ind, int indices_count);
	Object(char* tex_file);
	~Object();
	Object();

	void Render(const mat4& model_matrix, const mat4& view, const mat4& projection);
	void virtual Render(const mat4& view, const mat4& projection);

	glm::mat4 GetRotation(float angle, glm::vec3 vec);
	glm::mat4 GetMovement(glm::vec3 vec);
	void MoveForward(float l);
	void MoveRight(float l);
	void RotateX(float l);
	void RotateY(float l);
	void RotateZ(float l);

	float* object_x;
	float* object_y;
	float* object_z;


protected:
	void InitObject(Shader* shader, Texture2d* texture, GLfloat* verticies, int verticies_count, GLuint* indices, int indices_count);
	void Move(glm::vec3 vec);
	void Rotate(float angle, glm::vec3 vec);

	glm::mat4 model; //model to world, положение на мировой плосеости
	Mesh* mesh;
};

