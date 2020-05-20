#include "Camera.h"

void Camera::process_keyboard(Movement_direction direction, float delta_time)
{
	float velocity{ movement_speed * delta_time };

	switch (direction)
	{
	case Movement_direction::Forward:
		position += front * velocity;
		break;
	case Movement_direction::Backward:
		position -= front * velocity;
		break;
	case Movement_direction::Right:
		position += right * velocity;
		break;
	case Movement_direction::Left:
		position -= right * velocity;
		break;
	case Movement_direction::Jump:
		position += up * velocity;
		break;
	default:
		break;
	}
}

void Camera::process_mouse_movement(double x, double y)
{
	if (first_capture)
	{
		last_x = x;
		last_y = y;
		first_capture = false;
	}

	yaw += (x - last_x) * mouse_sensitivity;
	pitch += (last_y - y) * mouse_sensitivity;
	last_x = x;
	last_y = y;

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
	//up = glm::normalize(glm::cross(right, front)); // don't update for FPS camera
}
