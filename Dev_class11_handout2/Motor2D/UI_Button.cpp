#include"UI_Button.h"
#include"j1Textures.h"
#include"j1App.h"
#include"j1Input.h"

UI_Button::UI_Button(int x, int y, SDL_Rect rect, SDL_Rect rect2, SDL_Rect rect3, UI_Type type, GUI_Object* parent) :GUI_Object(x, y, parent) {

	position.x = x;
	position.y = y;
	mouseout = rect;
	mousein = rect2;
	mouseclick = rect3;
	buttonstate = mouseout;

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
	this->text = text;
	//colocar on aniria el text dins del cuadre del boto
}



