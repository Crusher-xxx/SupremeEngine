#pragma once
#include <glm/glm.hpp>

class GameObject
{
public:
	glm::vec3 position;

	GameObject(glm::vec3 position);
	virtual void render() = 0;
};

