#include "Shader.h"
#include <fstream>
#include "Logger.h"
#include <glad/glad.h>
#include <iostream>

std::string Shader::read(const std::string& path)
{
	std::ifstream file{ path };

	if (!file)
	{
		print_log_message("Failed to open file " + path);
	}

	// Iterate throughout file and construct string with shader source code
	std::string shader{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
	return shader;
}

bool Shader::check() const
{
	char shaderLog[2048];
	glGetShaderSource(ID, 2048, NULL, shaderLog);
	print_log_message("SHADER", 1);
	std::clog << shaderLog << '\n';

	int  success;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ID, 2048, NULL, shaderLog);
		std::clog << shaderLog << '\n';
		print_log_message("COMPILATION_FAILED");
		return false;
	}
	else
	{
		print_log_message("COMPILATION SUCCESSFUL");
		return true;
	}
}

unsigned int Shader::create(unsigned int type, const std::string& shader_source)
{
	// create EMPTY shader object
	unsigned int shader{ glCreateShader(type) };
	// make c-string
	const char* source{ shader_source.c_str() };
	// replace shader with source
	glShaderSource(shader, 1, &source, nullptr);
	// compile and check for errors
	glCompileShader(shader);

	return shader;
}

Shader::Shader(unsigned int type, const std::string& path) : ID{ create(type, read(path)) }
{
	check();
}

Shader::~Shader()
{
	glDeleteShader(ID);
}
