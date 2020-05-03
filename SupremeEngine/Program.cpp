#include "Program.h"
#include <fstream>
#include "Logger.h"
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

bool Program::check(const unsigned int program)
{
	int  success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
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

	check(ID);
}

void Program::use() const
{
	glUseProgram(ID);
}

void Program::delete_program()
{
	glDeleteProgram(ID);
}


void Program::set_uniform_1f(const std::string& name, const float value) const
{
	int location{ glGetUniformLocation(ID, name.c_str()) };
	if (location == -1)
	{
		print_log_message("UNIFORM LOCATION NOT FOUND: " + name);
	}

	glUniform1f(location, value);
}

void Program::set_uniform_matrix_4fv(const std::string& name, glm::mat4& transform) const
{
	unsigned int transform_location = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
}