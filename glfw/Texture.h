#include "Main.h"




class Texture
{
public:
	Texture(std::string fname, int tex_dimension, int mipmap_lvl, int color_of, int color_if, int data_format);
	Texture();
	virtual ~Texture();

	GLuint tex_pointer;


private:
	void Gen_tex(int tex_dimension, int mipmap_lvl, int color_of, int color_if, int data_format);
	void Cleanout_mem(int tex_dimension);
	void Load_tex(std::string fname);

	unsigned char* image;
	int width, height;
};

