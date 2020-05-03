#include "Texture.h"
#include <glad/glad.h>
#include "..\OpenGL_Dependencies\Dependencies\Additonal\stb_image.h"
#include <iostream>
#include "Logger.h"


Texture::Texture(const std::string& path, unsigned int texture_index)
{
	glGenTextures(1, &ID);
	switch (texture_index)
	{
	case 0:
		glActiveTexture(GL_TEXTURE0);
		break;
	case 1:
		glActiveTexture(GL_TEXTURE1);
		break;
	default:
		glActiveTexture(GL_TEXTURE0);
		print_log_message("UNSUPPORTED TEXTURE INDEX: " + std::to_string(texture_index));
		break;
	}
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channels_count;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels_count, 0);
	if (data)
	{
		//make sure you load format correctly
		if (path.substr(path.length() - 3) == "jpg")
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (path.substr(path.length() - 3) == "png")
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			print_log_message("UNSUPPORTED TEXTURE FORMAT");
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		print_log_message("FAILED TO LOAD TEXTURE");
	}
	stbi_image_free(data);
}