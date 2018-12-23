#include "UI_Button.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"
#include "p2SString.h"


UI_Button::UI_Button(int x, int y, SDL_Rect rect, SDL_Rect rect2, SDL_Rect rect3, char* name, UI_Type type, GUI_Object* parent) :GUI_Object(x, y, parent) {

	position.x = x;
	position.y = y;
	mouseout = rect;
	mousein = rect2;
	mouseclick = rect3;
	section = mouseout;
	dragable = true; 

	this->parent = parent;

	button_name = name; 


}
UI_Button::~UI_Button()
{
	if (text != nullptr) {
		App->tex->UnLoad(texture);
		text = nullptr;
		delete text;
	}
}

void UI_Button::SetText(UI_Label* text)
{
	text->position.x = this->position.x + section.w / 2;
	text->position.y = this->position.y + section.h / 2;
	this->text = text;
	
	
}

void UI_Button::Update() {
	if (mousestate == MouseState::MOUSE_OUT) 
	{
		section = mouseout;
	}
	if (mousestate == MouseState::MOUSE_HOVER) 
	{
		section = mousein;
	}
	if (mousestate == MouseState::MOUSE_CLICKED) {
		section = mouseclick;
		to_interact = true; 

	}
	if (mousestate == MouseState::MOUSE_UP && to_interact)
	{
		interacted = false; 
		to_interact = false; 
		App->gui->ButtonAction(button_name);
	}


	App->input->GetMousePosition(mousepos.x, mousepos.y);
	MouseInRect();
}


