#include"UI_Slider.h"
#include"j1Textures.h"
#include"j1App.h"
#include"j1Input.h"


UI_Slider::UI_Slider(int x, int y, GUI_Object* parent) : GUI_Object(x, y, parent) {
	position.x = x;
	position.y = y;
	this->parent = parent;
	slidersection = {1085,168,193,50};
	slider = { 1504,97,29,43 };
	section = slider;
}
UI_Slider::~UI_Slider() {

}

void UI_Slider::Update()
{
	App->input->GetMousePosition(mousepos.x, mousepos.y);


}

void UI_Slider::DragSlider()
{

	if (!App->input->GetMouseButtonDown(1) == KEY_UP && mousepos.x > position.x && mousepos.x < position.x + section.w && mousepos.y > position.y && mousepos.y < position.y + section.h)
	{
		 
	}
}