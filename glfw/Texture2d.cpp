#include "Texture2d.h"



Texture2d::Texture2d(char* filename)
{
	/*#loading tex from file#*/
	int width, height;
	//tex file adr, width pointer, height pointer, chanels count, which info load
	unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
	
	/*#generating tex#*/
	//how much texs would be loaded, array of texs descriptors
	glGenTextures(1, &descriptor);
	glBindTexture(GL_TEXTURE_2D, descriptor);

	/*#generating tex data#*/
	//tex goal, mipmap lvl (0=>opengl itself will generate mipmap), tex format, w, h, *dont use*, source image format, source image data type, image  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	/*#Cleaning of mem#*/
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


Texture2d::~Texture2d()
{
}
