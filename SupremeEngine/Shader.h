#pragma once
#include <string>

class Shader
{
public:
	const unsigned int ID;
	Shader(const unsigned int type, const std::string& path);
	~Shader();
private:
	static std::string read(const std::string& path);
	static bool check(const unsigned int shader);
	static unsigned int create(const unsigned int type, const std::string& shader_source);
};

