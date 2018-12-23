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
	if (mouseposition == MousePosition::MOUSE_OUT) 
	{
		section = mouseout;
	}
	if (mouseposition == MousePosition::MOUSE_HOVER) 
	{
		section = mousein;
	}
	if (clicked) {
		section = mouseclick;
	}
	if (mouse_upped)
	{		
		if (MouseInBorders() && selected)
		{
			App->gui->ButtonAction(button_name);
		}		
		selected = false; 
		mouse_upped = false; 
	}


	App->input->GetMousePosition(mousepos.x, mousepos.y);
	MouseInRect();
}


