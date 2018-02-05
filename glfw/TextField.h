#include "Object.h"



class TextField : public Object
{
public:
	TextField();
	void Render(const mat4& view, const mat4& projection);
	
	string text_to_write;



private:
	void SetTexCoords(int& letter_num, float& letter_height, float& letter_width, GLfloat* vericies);
	void WriteLetter(int letter_num, const mat4& view, const mat4& projection);
	void DropLine();
	void Move(glm::vec3 vec);

	Object** letters;
	int letters_count;
	float letter_width;
	float letter_height;
	float letter_spacing;
	float line_spacing;
	int letters_per_line;
	int current_line_num;
	int current_letter_num;
};

