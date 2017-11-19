#include "Texture.h"



Texture::Texture() 
{
	//Texture("D:\\Textures\\default.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
	Load_tex("D:\\Textures\\default.jpg");
	Gen_tex(GL_TEXTURE_2D, 0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
	Cleanout_mem(GL_TEXTURE_2D);
}


Texture::Texture(std::string fname, int tex_dimension, int mipmap_lvl, int color_of, int color_if, int data_format)
{
	Load_tex(fname);
	Gen_tex(tex_dimension, mipmap_lvl, color_of, color_if, data_format);
	Cleanout_mem(tex_dimension);
}


Texture::~Texture()
{
}




void Texture::Load_tex(std::string fname)
{
	image = SOIL_load_image(fname.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	std::cout << "\r\n\r\n" << fname << " loaded";
}


void Texture::Gen_tex(int tex_dimension, int mipmap_lvl, int color_of, int color_if, int data_format)
{
	glGenTextures(1, &tex_pointer);
	glBindTexture(tex_dimension, tex_pointer);
	std::cout << "\r\ntexture binded: " << tex_pointer;

	glTexImage2D(tex_dimension, mipmap_lvl, color_of, width, height, 0, color_if, data_format, image);
	glGenerateMipmap(tex_dimension);
}


void Texture::Cleanout_mem(int tex_dimension)
{
	SOIL_free_image_data(image);
	glBindTexture(tex_dimension, 0);
	std::cout << "\r\nmemmory cleaned";
}