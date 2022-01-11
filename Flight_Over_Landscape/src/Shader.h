#pragma once
#include <string>
#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:

	

	unsigned int m_RendererID;
	std::string filepath;

	unsigned int getUniformLocation(const std::string& name);
	ShaderProgramSource parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);

	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

public:
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unbind() const;

	
	// Set uniforms
	void setUniform4f(const std::string& name, float a, float b, float c, float d);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void setUniform1i(const std::string& name, int value);
};

