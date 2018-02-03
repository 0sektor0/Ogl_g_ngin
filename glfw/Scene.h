#include "Main.h"
#include "Object.h"
#include "Camera.h"


class Scene
{
public:
	void Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void Cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	Scene(const int& window_width, const int& window_height);
	void Render();
	~Scene();

	Object* selected_object;
	bool show_vecs = true;


private:
	void Load_objects();

	int selected_object_index = 0;
	vector <Object*> objects;
	Camera* camera;
	double mouse_x = 0;
	double mouse_y = 0;
};

