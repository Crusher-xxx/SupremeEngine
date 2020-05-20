#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum class Movement_direction
{
	Forward,
	Backward,
	Right,
	Left,
	Jump
};

class Camera
{
public:
	float movement_speed{ 5.5 };
	float mouse_sensitivity{ 0.05 };
	float field_of_view{ 45 };

	void process_keyboard(Movement_direction direction, float delta_time);
	void process_mouse_movement(double x, double y);
	glm::mat4 get_view_matrix();
	void update_camera_vectors();

private:
	float last_x{ 400 };
	float last_y{ 300 };
	bool first_capture{ true };
	float pitch{ 0 };
	float yaw{ -90.0f };

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f); // vector in world space that points to the camera's position
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f); // vector in world space that points to where camera looks
	glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f); //
	glm::vec3 right = glm::normalize(glm::cross(front, world_up));
	glm::vec3 up = glm::normalize(glm::cross(right, front));
};

