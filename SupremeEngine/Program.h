#pragma once
#include<string>
#include"Shader.h"
#include<vector>

class Program
{
public:
	const unsigned int ID;
	Program(const std::string& vertex_path, const std::string& fragment_path);
	operator unsigned int() const { return ID; };
	void use() const;
	void delete_program();
	void set_uniform(const std::string& name, const std::vector<float>& values) const;
private:
	static bool check(const unsigned int program);
};

