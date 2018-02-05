#include "Main.h"
#include "Object.h"
#include "Camera.h"



class Scene
{
public:
	void Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void Cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	Scene(const int& window_width, const int& window_height);
	void ProcessPressedKeys();
	void Render();
	~Scene();

	Object* selected_object;
	bool show_vecs = true;


private:
	void LoadObjects();

	int selected_object_index;
	vector <Object*> objects;
	Camera* camera;
	bool keys[1024];
};

