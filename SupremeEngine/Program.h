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
	operator unsigned int() const { return ID; }; // Treat program object as its ID
	void use() const;
	void delete_program();
	// Send value to shader
	void set_uniform(const std::string& name, const float value) const;
	void set_uniform(const std::string& name, const int value) const;
	// Send transformation matrix to shader
	void set_uniform(const std::string& name, const glm::mat4& transform) const;
private:
	bool check() const; // Check if program links
	static bool check_uniform_location(const unsigned int location, const std::string& name); // Check if shader sees your uniform
};

