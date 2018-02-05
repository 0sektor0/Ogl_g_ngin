#include "Camera.h"




Camera::Camera(const int& window_width, const int& window_height)
{
	Reset();
	
	camera_x = &camera_pos[0];
	camera_y = &camera_pos[1];
	camera_z = &camera_pos[2];

	projection = glm::perspective(CAM_DEFAULT_FOV, (float)(window_width / window_height), CAM_DEFAULT_NEAR_PLANE, CAM_DEFAULT_FAR_PLANE);	
}


void Camera::Reset()
{
	camera_front = glm::vec3(0.0f, 0.0f, -1.0f);

	camera_speed = CAM_DEFAULT_SPEED;
	sensitivity = CAM_DEFAULT_SENSITIVITY;

	camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
	LookAtPoint(glm::vec3(0.0f, 0.0f, 0.0f));

	yaw = -90.0f;
	pitch = 0.0f;
}




void Camera::SetPerspectiveProjection(float fov, float side_ratio, float near_plane, float far_plane)
{
	projection = glm::perspective(fov, side_ratio, near_plane, far_plane);
}


void Camera::SetOrthoProjection(float left, float right, float down, float up, float near_plane, float far_plane)
{
	projection = glm::ortho(left, right, down, up, near_plane, far_plane);
}




void Camera::LookAtPoint(glm::vec3& target)
{
	camera_target = target;
	glm::vec3 camera_direction = glm::normalize(camera_pos - camera_target);

	glm::vec3 axis_y = glm::vec3(0.0f, 1.0f, 0.0f);
	camera_axis_x = glm::normalize(glm::cross(axis_y, camera_direction));
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


void Camera::MoveUp()
{
	camera_pos -= glm::normalize(glm::cross(camera_front, camera_axis_x)) * camera_speed;
	LookFront();
}


void Camera::MoveDown()
{
	camera_pos += glm::normalize(glm::cross(camera_front, camera_axis_x)) * camera_speed;
	LookFront();
}


void Camera::Rotate(const double& xpos, const double& ypos)
{	
	if (!first_mouse_move) 
	{
		float xoffset = xpos - mouse_x;
		float yoffset = mouse_y - ypos;
		mouse_x = xpos;
		mouse_y = ypos;

		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		camera_front = glm::normalize(front);

		LookFront();
	}
	else
	{
		mouse_x = xpos;
		mouse_y = ypos;

		first_mouse_move = false;
	}
}