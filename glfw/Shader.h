#include "Main.h"


#define SHADER_LOCAL_MATRIX 2
#define SHADER_MODEL_MATRIX 3
#define SHADER_VIEW_MATRIX 4
#define SHADER_PROJECTION_MATRIX 5


class Shader
{
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;
	std::string LoadShaderSource(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];

public:
	Shader(const std::string& fileName);
	void Bind();
	virtual ~Shader();

	GLuint m_uniforms[NUM_UNIFORMS];
};
