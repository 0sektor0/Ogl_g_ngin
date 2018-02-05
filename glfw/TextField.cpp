#include "TextField.h"




TextField::TextField()
{
	Shader* shader = new Shader("shader");
	Texture2d* texture_background = new Texture2d("D:\\Textures\\default.jpg");
	Texture2d* texture_font = new Texture2d("D:\\Textures\\fonts_0.png");

	float background_z = 0.01f;
	letter_width = 0.05f;
	letter_height = 0.05f;
	letter_spacing = 0.005f;
	line_spacing = 0.05f;
	letters_per_line = 2.0f/( letter_width + letter_spacing) - 1;
	letters_count = 60;

	//text field coords
	glm::vec3 field_lu = glm::vec3(-1.0f, -0.5f, background_z);
	glm::vec3 field_ld = glm::vec3(-1.0f, -1.0f, background_z);
	glm::vec3 field_ru = glm::vec3(1.0f, field_lu.y, background_z);
	glm::vec3 field_rd = glm::vec3(field_ru.x,  field_ld.y, background_z);

	//letter coords
	glm::vec3 letter_lu = glm::vec3(field_lu.x + letter_spacing, field_lu.y - letter_spacing, background_z + 0.01f);
	glm::vec3 letter_ld = glm::vec3(letter_lu.x, letter_lu.y - letter_height, background_z + 0.01f);
	glm::vec3 letter_ru = glm::vec3(letter_lu.x + letter_width, letter_lu.y, background_z + 0.01f);
	glm::vec3 letter_rd = glm::vec3(letter_ru.x, letter_ld.y, background_z + 0.01f);

	//meshes data
	GLfloat* vertices_background = new GLfloat[36]{
		// Позиции                            // Цвета                  // Текстурные координаты
		field_ru.x, field_ru.y, field_ru.z,   1.0f, 0.5f, 0.9f, 0.6f,   1.0f, 1.0f,   // Верхний правый
		field_rd.x, field_rd.y, field_rd.z,   1.0f, 0.5f, 0.9f, 0.6f,   1.0f, 0.0f,   // Нижний правый
		field_ld.x, field_ld.y, field_ld.z,   1.0f, 0.5f, 0.9f, 0.6f,   0.0f, 0.0f,   // Нижний левый
		field_lu.x, field_lu.y, field_lu.z,   1.0f, 0.5f, 0.9f, 0.6f,   0.0f, 1.0f    // Верхний левый
	};
	GLuint* indices = new GLuint[6]{
		2, 3, 0,
		0, 1, 2
	};
	GLfloat* vertices_symblos;

	//creating background
	mesh = new Mesh(vertices_background, 36, indices, 6);
	mesh->Bind_shader(shader);
	mesh->Bind_texture(texture_background);

	object_x = &model[3][0];
	object_y = &model[3][1];
	object_z = &model[3][2];

	//создаем символы
	letters = new Object*[letters_count];
	float letter_tex_height = 0.1f;
	float letter_tex_width = 0.1f;

	for (int i = 0; i < letters_count; i++)
	{
		vertices_symblos = new GLfloat[36]{
			// Позиции                               // Цвета                  // Текстурные координаты
			letter_ru.x, letter_ru.y, letter_ru.z,   1.0f, 0.5f, 0.9f, 1.0f,   0.0f, 0.0f,   // правый верхний
			letter_rd.x, letter_rd.y, letter_rd.z,   1.0f, 0.5f, 0.9f, 1.0f,   0.0f, 0.0f,   // правый Нижний 
			letter_ld.x, letter_ld.y, letter_ld.z,   1.0f, 0.5f, 0.9f, 1.0f,   0.0f, 0.0f,   // левый Нижний
			letter_lu.x, letter_lu.y, letter_lu.z,   1.0f, 0.5f, 0.9f, 1.0f,   0.0f, 0.0f    // левый Верхний 
		};
		SetTexCoords(i, letter_tex_height, letter_tex_width, vertices_symblos);
		letters[i] = new Object(shader, texture_font, vertices_symblos, 36, indices, 6);
	}

	DropLine();
}


void TextField::SetTexCoords(int& letter_num, float& letter_height, float& letter_width, GLfloat* vericies)
{
	int columns_num = 1.0f / letter_width;
	int lines_num = 1.0f / letter_height;
	int line = letter_num / columns_num;
	int column = letter_num - line * columns_num;

	float border_left = column * letter_width;
	float border_right = border_left + letter_width;
	float border_top = 1.0f - line * letter_height;
	float border_bottom = border_top - letter_width;

	vericies[7] = border_right;
	vericies[8] = border_top;

	vericies[16] = border_right;
	vericies[17] = border_bottom;

	vericies[25] = border_left;
	vericies[26] = border_bottom;

	vericies[34] = border_left;
	vericies[35] = border_top;
}


void TextField::Render(const mat4& view, const mat4& projection)
{
	mesh->Render(model, view, projection);

	for(int i = 0; i < 60; i++)
		WriteLetter(i, view, projection);

	DropLine();
}




void TextField::WriteLetter(int letter_num, const mat4& view, const mat4& projection)
{
	Object* letter = letters[letter_num];
	float offsetx = current_letter_num * (letter_spacing + letter_width) + 3 * letter_spacing;
	float offsety = current_line_num * (line_spacing + letter_height) + 3 * line_spacing;

	if (current_line_num == 0)
		offsety = 3 * line_spacing;
	if (current_letter_num == 0)
		offsetx = 3 * letter_spacing;

	glm::mat4 new_model = letter->GetMovement(glm::vec3(offsetx, -offsety, 0));
	letters[letter_num]->Render(new_model, view, projection);

	current_letter_num++;
	if (current_letter_num > letters_per_line)
	{
		current_line_num++;
		current_letter_num = 0;
	}
}


void TextField::DropLine() 
{
	current_letter_num = 0;
	current_line_num = 0;
}


void TextField::Move(glm::vec3 vec)
{
	model = glm::translate(model, vec);
}