#pragma once
#include <string>
#include "Shader.h"
#include <vector>
#include <glm/glm.hpp>


class Program
{
public:
	const unsigned int ID;
	Program(const std::string& vertex_path, const std::string& fragment_path);
	// Treat program object as its ID
	operator unsigned int() const { return ID; };
	void use() const;
	void delete_program();
	// Send value to shader
	void set_uniform_1f(const std::string& name, const float value) const;
	// Send transformation matrix to shader
	void set_uniform_matrix_4fv(const std::string& name, const glm::mat4& transform) const;
private:
	// Check if program links
	static bool check(const unsigned int program);
};

