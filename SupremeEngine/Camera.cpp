#include "Camera.h"

void Camera::process_keyboard(Movement_direction direction, float delta_time)
{
	float velocity{ movement_speed * delta_time };

	switch (direction)
	{
	case Movement_direction::forward:
		position += front * velocity;
		break;
	case Movement_direction::backward:
		position -= front * velocity;
		break;
	case Movement_direction::right:
		position += right * velocity;
		break;
	case Movement_direction::left:
		position -= right * velocity;
		break;
	case Movement_direction::up:
		position += up * velocity;
		break;
	case Movement_direction::down:
		position -= up * velocity;
		break;
	default:
		break;
	}
}

void Camera::process_mouse_movement(float x, float y)
{
	// check to prevent camera jump on cursor capture
	if (first_capture)
	{
		last_x = x;
		last_y = y;
		first_capture = false;
	}

	yaw = glm::mod(yaw + (x - last_x) * mouse_sensitivity, 360.0f); // Float has loss of precision on big values. Limit to (-360, 360) range.
	pitch += (last_y - y) * mouse_sensitivity;
	last_x = x;
	last_y = y;

	// check to prevent LookAt matrix from inverting
	if (pitch > 89)
		pitch = 89;
	if (pitch < -89)
		pitch = -89;

	update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix()
{
	return glm::lookAt(position, position + front, up);
}


void Camera::update_camera_vectors()
{
	front = glm::normalize(glm::vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))));


	right = glm::normalize(glm::cross(front, world_up));
	//up = glm::normalize(glm::cross(right, front)); // no update — move in world's up coordinate (FPS camera) | update — move in camera's up coordinate
}
