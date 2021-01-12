#pragma once
#include <string>

class Texture
{
public:
	unsigned int ID;
	Texture(const std::string& path, unsigned int texture_index);
	~Texture();
private:
};