#include "Program.h"
#include <fstream>
#include "Logger.h"
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

bool Program::check() const
{
	int  success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::clog << infoLog << '\n';
		print_log_message("LINKING FAILED");
		return false;
	}
	else
	{
		print_log_message("LINKING SUCCESSFUL");
		return true;
	}
}

Program::Program(const std::string& vertex_path, const std::string& fragment_path) : ID{ glCreateProgram() }
{
	Shader vertex_shader{ GL_VERTEX_SHADER, vertex_path };
	Shader fragment_shader{ GL_FRAGMENT_SHADER, fragment_path };

	glAttachShader(ID, vertex_shader.ID);
	glAttachShader(ID, fragment_shader.ID);
	glLinkProgram(ID);

	check();
}

void Program::use() const
{
	glUseProgram(ID);
}

void Program::delete_program()
{
	glDeleteProgram(ID);
}

void Program::set_uniform(const std::string& name, const float value) const
{
	int location{ glGetUniformLocation(ID, name.c_str()) };
	check_uniform_location(location, name); 

	glUniform1f(location, value);
}

void Program::set_uniform(const std::string& name, const glm::mat4& transform) const
{
	int location{ glGetUniformLocation(ID, name.c_str()) };
	check_uniform_location(location, name);

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(transform));
}

void Program::set_uniform(const std::string& name, const int value) const
{
	int location{ glGetUniformLocation(ID, name.c_str()) };
	check_uniform_location(location, name);

	glUniform1i(location, value);
}

bool Program::check_uniform_location(const unsigned int location, const std::string& name)
{
	if (location == -1)
	{
		print_log_message("UNIFORM LOCATION NOT FOUND: " + name);
		return false;
	}
	return true;
}