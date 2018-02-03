#include "Main.h"
#include "Mesh.h"

class Object
{
public:
	Object(char* tex_file, GLfloat* vert, int verticies_count, GLuint* ind, int indices_count);
	void Render(const mat4& view, const mat4& projection);
	void MoveRight(float l);
	void MoveForward(float l);
	void RotateX(float l);
	void RotateY(float l);
	void RotateZ(float l);
	~Object();
	Object();

	glm::mat4 model; //model to world, положение на мировой плосеости
	float* object_x;
	float* object_y;
	float* object_z;


private:
	void Move(glm::vec3 vec);
	void Rotate(float angle, glm::vec3 vec);

	Mesh* mesh;
};

