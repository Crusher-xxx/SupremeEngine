#include "Program.h"
#include<fstream>
#include"Logger.h"
#include<glad/glad.h>
#include<iostream>
#include<vector>
#include<sstream>

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


void Program::set_uniform (const std::string& name, const std::vector<float>& values) const
{
	int location{ glGetUniformLocation(ID, name.c_str()) };
	if (location == -1)
	{
		print_log_message("UNIFORM LOCATION NOT FOUND: " + name);
	}

	switch (values.size())
	{
	case 1:
		glUniform1f(location, values[0]);
		break;
	case 4:
		glUniform4f(location, values[0], values[1], values[2], values[3]);
		break;
	default:
		print_log_message("UNSUPPORTED UNIFORM FOR SIZE OF: " + std::to_string(values.size()));
		break;
	}
}