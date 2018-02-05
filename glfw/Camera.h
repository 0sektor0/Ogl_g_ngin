#include "Main.h"

#define CAM_DEFAULT_ORTHO_RIGHT 800.0f
#define CAM_DEFAULT_SENSITIVITY 0.05f
#define CAM_DEFAULT_SIDE_RATIO 1.5f
#define CAM_DEFAULT_ORTHO_LEFT 0.0f
#define CAM_DEFAULT_ORTHO_DOWN 0.0f
#define CAM_DEFAULT_ORTHO_UP 600.0f
#define CAM_DEFAULT_NEAR_PLANE 0.1f
#define CAM_DEFAULT_FAR_PLANE 100.f
#define CAM_PROJECTION_PERSPECTIVE 0
#define CAM_PROJECTION_ORTHO 1
#define CAM_DEFAULT_SPEED 0.1f
#define CAM_DEFAULT_FOV 45.0f



class Camera
{
public:
	void SetOrthoProjection(float left, float right, float down, float up, float near_plane, float far_plane);
	void SetPerspectiveProjection(float fov, float side_ratio, float near_plane, float far_plane);
	Camera(int projection_type);
	Camera();	
	//cam movement
	void Rotate(const double& xpos, const double& ypos);
	void LookAtPoint(glm::vec3& target);
	void MoveBackward();
	void MoveForward();
	void MoveRight();
	void MoveLeft();
	void MoveDown();
	void MoveUp();
	void Reset();
	
	//cam matricies
	glm::mat4 projection;
	glm::mat4 view;
	//cam parametrs
	float camera_speed;
	float sensitivity;
	float* camera_x;
	float* camera_y;
	float* camera_z;

	

private:
	void LookFront();
	
	//var fo cam rotation
	bool first_mouse_move = true;
	double mouse_x = 0;
	double mouse_y = 0;
	GLfloat pitch;
	GLfloat yaw;
	//cam vectors
	glm::vec3 camera_target;
	glm::vec3 camera_axis_x;
	glm::vec3 camera_axis_y;
	glm::vec3 camera_front;
	glm::vec3 camera_pos;
};

