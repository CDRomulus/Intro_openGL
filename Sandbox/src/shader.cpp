#include "shader.h"
#include <fstream>
#include <iostream>
#include <windows.h>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string fileName);
static GLuint CreateShader(const std::string text, GLenum shaderType);
std::string GetExeFileName();
std::string GetExePath();

Shader::Shader(const std::string& fileName)
{
	
	m_program = glCreateProgram();

	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"),GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);


	for (unsigned int i = 0; i<NUM_SHADERS; i++)	
		glAttachShader(m_program,m_shaders[i]);
	
	glBindAttribLocation(m_program,0,"position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glLinkProgram(m_program);
	CheckShaderError(m_program,GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program,"transform");

}
Shader::~Shader()
{
	for (unsigned int i=0; i<NUM_SHADERS;i++)
	{
		glDetachShader(m_program,m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}
void Shader::Bind()
{
	glUseProgram(m_program);

}
void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}
static GLuint CreateShader(const std::string text, GLenum shaderType)
{

	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cout << "Error: Shader Creation Failed!" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = GLint(text.length());

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader,GL_COMPILE_STATUS, false, "ERROR: Shader compilation failed: ");
	
	return shader;
}
static std::string LoadShader(const std::string fileName)
{
	std::ifstream file;
	file.open(fileName);

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file,line);
			output.append(line+"\n");
		}

	}
	else
	{
		std::cout << "Unable to load Shader: " << fileName << std::endl;
	}
	return output;

}
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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
			glGetProgramInfoLog(shader, sizeof(error),NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cout << errorMessage << ": '" << error << "'" << std::endl;
	}
	
}
std::string GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}

std::string GetExePath()
{
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}