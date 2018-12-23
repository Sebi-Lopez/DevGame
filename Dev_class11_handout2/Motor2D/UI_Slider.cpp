#include "UI_Slider.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "p2Log.h"

UI_Slider::UI_Slider(int x, int y, uint initial_value, SDL_Rect sliderSection, GUI_Object* parent) : GUI_Object(x, y, parent) {
	fixed_position.x = x;
	fixed_position.y = y; 
	position.x = fixed_position.x + initial_value;
	position.y = fixed_position.y;
	this->parent = parent;
	slidersection = {1085,168,193,50};
	slider = { 1504,97,29,43 };
	section = slider;
	min = fixed_position.x;
	max = fixed_position.x + slidersection.w - section.w;
	value = initial_value; 
}
UI_Slider::~UI_Slider() {

}

void UI_Slider::Update()
{
	App->input->GetMousePosition(mousepos.x, mousepos.y);
	MouseInRect(); 
	App->render->Blit(App->gui->GetAtlas(), fixed_position.x, fixed_position.y, &slidersection, 0.0F);
	if (mouse_upped)
	{
		selected = false;
		mouse_upped = false;
	}
	DragSlider();
}

void UI_Slider::DragSlider()
{

	if (selected == true)
	{
		iPoint mouse;
		App->input->GetMousePosition(mouse.x, mouse.y);
		position.x = mouse.x - section.w * 0.5;


		if (position.x < min)
		{
			position.x = min;
		}
		if (position.x > max)
		{
			position.x = max;
		}

		CalculateValue();
		App->gui->SliderAction(this); 
	}
}

void UI_Slider::CalculateValue()
{
	value = position.x - min; 
}
