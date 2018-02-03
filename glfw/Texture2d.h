#include "Main.h"


class Texture2d
{
public:
	Texture2d(char* filename);
	~Texture2d();

	GLuint descriptor; //texturte descriptor
};

