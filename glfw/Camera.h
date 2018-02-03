#include "Main.h"



class Camera
{
public:
	Camera(const int& window_width, const int& window_height);
	void LookAtPoint(glm::vec3& target);
	void MoveBackward();
	void MoveForward();
	void MoveRight();
	void MoveLeft();
	void Reset();
	~Camera();

	glm::mat4 projection;
	glm::mat4 view;
	float* camera_x;
	float* camera_y;
	float* camera_z;
	float camera_speed;



private:
	void LookFront();

	glm::vec3 camera_pos;
	glm::vec3 camera_target; //where to look
	glm::vec3 camera_axis_y;
	glm::vec3 camera_front;;
};

