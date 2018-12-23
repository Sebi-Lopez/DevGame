#include "GUI_Button.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"
#include "p2SString.h"
#include "j1GUI.h"
#include "j1Audio.h"
#include "Brofiler/Brofiler.h"
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



void GUI_Button::Update() 
{
	BROFILER_CATEGORY("Update Button", Profiler::Color::Maroon);

	App->input->GetMousePosition(mousepos.x, mousepos.y);
	MouseInRect();

	if (mousestate == MouseState::MOUSE_OUT)
	{
		fx_played = false; 
		section = mouseout;
	}
	if (mousestate == MouseState::MOUSE_HOVER)
	{
		if (!fx_played) 
		{
			App->audio->PlayFx(1);
			fx_played = true;
		}
		section = mousein;
	}
	if (clicked) {
		if (!fx_clicked)
		{
			App->audio->PlayFx(2);
			fx_clicked = true; 
		}
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
		fx_clicked = false; 
	}
}
