#include "Camera.h"



Camera::Camera(const int& window_width, const int& window_height)
{
	camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
	Reset();
	
	camera_x = &camera_pos[0];
	camera_y = &camera_pos[1];
	camera_z = &camera_pos[2];

	projection = glm::perspective(45.0f, (float)(window_width / window_height), 0.1f, 100.0f);
}


Camera::~Camera()
{
}


void Camera::Reset()
{
	camera_speed = 0.5f;
	camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
	LookAtPoint(glm::vec3(0.0f, 0.0f, 0.0f));
}




void Camera::LookAtPoint(glm::vec3& target)
{
	camera_target = target;
	glm::vec3 camera_direction = glm::normalize(camera_pos - camera_target);

	glm::vec3 axis_y = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 camera_axis_x = glm::normalize(glm::cross(axis_y, camera_direction));
	camera_axis_y = glm::cross(camera_direction, camera_axis_x);

	view = glm::lookAt(camera_pos, camera_target, camera_axis_y);
}


void Camera::LookFront()
{
	view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_axis_y);
}




void Camera::MoveForward()
{
	camera_pos += camera_front * camera_speed;
	LookFront();
}


void Camera::MoveBackward()
{
	camera_pos -= camera_front * camera_speed;
	LookFront();
}


void Camera::MoveLeft()
{
	camera_pos -= glm::normalize(glm::cross(camera_front, camera_axis_y)) * camera_speed;
	LookFront();
}


void Camera::MoveRight()
{
	camera_pos += glm::normalize(glm::cross(camera_front, camera_axis_y)) * camera_speed;
	LookFront();
}