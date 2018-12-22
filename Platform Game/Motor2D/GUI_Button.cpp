#include "GUI_Button.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"
#include "p2SString.h"
#include "j1GUI.h"

GUI_Button::GUI_Button(int x, int y, SDL_Rect rect, SDL_Rect rect2, SDL_Rect rect3, char* name, UI_Type type, GUI_Object* parent) :GUI_Object(x, y, parent) {

	position.x = x;
	position.y = y;
	mouseout = rect;
	mousein = rect2;
	mouseclick = rect3;
	section = mouseout;
	button_name = name;

}
GUI_Button::~GUI_Button()
{
	if (text != nullptr) {
		App->tex->UnLoad(texture);
		text = nullptr;
		delete text;
	}
}



void GUI_Button::Update() {
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
