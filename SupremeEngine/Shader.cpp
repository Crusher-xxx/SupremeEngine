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

	std::string shader{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() }; // Iterate throughout file and construct string with shader source code
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
	unsigned int shader{ glCreateShader(type) }; // create EMPTY shader object
	const char* const source{ shader_source.c_str() }; // make c-string
	glShaderSource(shader, 1, &source, nullptr); // INITIALIZE shader with source
	glCompileShader(shader); // compile and check for errors

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
