#include "Shader.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>






Shader::Shader(const std::string& filepath_)
	:filepath(filepath_)
{
	ShaderProgramSource source = parseShader(filepath);
	
	m_RendererID = createShader(source.vertexSource, source.fragmentSource);
	
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, float a, float b, float c, float d)
{
	
	glUniform4f(getUniformLocation(name), a, b, c, d);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr (matrix));
}

void Shader::setUniform1i(const std::string& name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

unsigned int Shader::getUniformLocation(const std::string& name)
{
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1) {
		std::cout << "Warning: Uniform " << name << " does not exist." << std::endl;
	}
	return location;
}

ShaderProgramSource Shader::parseShader(const std::string& filepath) {

	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	// Each line of stream will be stored in this
	std::string line;

	// 2 stringstreams, one for vertex shader, one for fragment shader
	std::stringstream sStream[2];

	ShaderType sType = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {



			if (line.find("vertex") != std::string::npos) {
				// vertex init
				sType = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				// fragment init

				sType = ShaderType::FRAGMENT;
			}
		}
		else {
			if ((int)sType == 0) {
				sStream[0] << line << '\n';

			}
			else if ((int)sType == 1) {
				sStream[1] << line << '\n';


			}
		}
	}
	return { sStream[0].str(), sStream[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Basic error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* errorMessage = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, errorMessage);

		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {

	unsigned int program = glCreateProgram();

	// Compile actual shaders
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	// Attach shaders
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	// Link program
	glLinkProgram(program);
	glValidateProgram(program);

	// Delete intermediate shaders
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
