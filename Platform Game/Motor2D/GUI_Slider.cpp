#include "GUI_Slider.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "p2Log.h"

GUI_Slider::GUI_Slider(int x, int y, uint initial_value, GUI_Object* parent) : GUI_Object(x, y, parent) {
	position.x = x + initial_value;
	position.y = y;
	this->parent = parent;
	slidersection = { 1310, 99,191,50 };
	slider = { 1361, 29,28,40 };
	section = slider;
	min = x;
	max = x + slidersection.w - section.w;
	value = initial_value;
	App->gui->CreateLogo(x, y, slidersection, nullptr); 
	App->gui->CreateLabel(x + 55, y + 10, "Volume", nullptr);
}
GUI_Slider::~GUI_Slider()
{
	if (texture != nullptr) {
		App->tex->UnLoad(texture);
		texture = nullptr;
		delete texture;
	}
}

void GUI_Slider::Update()
{
	App->input->GetMousePosition(mousepos.x, mousepos.y);
	MouseInRect();
	if (mouse_upped)
	{
		selected = false;
		mouse_upped = false;
	}
	DragSlider();
}

void GUI_Slider::DragSlider()
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

void GUI_Slider::CalculateValue()
{
	value = position.x - min;
}
