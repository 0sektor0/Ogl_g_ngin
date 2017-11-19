#include "Shader.h"


Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShaderSource(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShaderSource(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

	m_uniforms[0] = glGetUniformLocation(m_program, "clr");
	m_uniforms[1] = glGetUniformLocation(m_program, "tex");
	m_uniforms[2] = glGetUniformLocation(m_program, "local");
	m_uniforms[3] = glGetUniformLocation(m_program, "model");
	m_uniforms[4] = glGetUniformLocation(m_program, "view");
	m_uniforms[5] = glGetUniformLocation(m_program, "projection");
}


Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}


void Shader::Bind()
{
	glUseProgram(m_program);
}


std::string Shader::LoadShaderSource(const std::string& fileName)
{
	std::ifstream file;
	std::string shader_source;
	std::string line;

	file.open((fileName).c_str());
	if (file.is_open())
		while (file.good())
		{
			getline(file, line);
			shader_source.append(line + "\n");
		}
	else
		std::cout << "Unable to load shader: " << fileName << std::endl;

	return shader_source;
}


void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cout << errorMessage << ": '" << error << "'" << std::endl;
	}
}


GLuint Shader::CreateShader(const std::string& shader_source, unsigned int type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		std::cout << "Error compiling shader type:\r\n" << type << std::endl;

	const GLchar* p[1];
	p[0] = shader_source.c_str();
	GLint lengths[1];
	lengths[0] = shader_source.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader:\r\n");

	return shader;
}