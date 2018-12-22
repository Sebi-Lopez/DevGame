#include "GUI_Label.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"

GUI_Label::GUI_Label(int x, int y, p2SString text, UI_Type type, GUI_Object* parent) :GUI_Object(x, y, parent) {
	position.x = x;
	position.y = y;
	this->type = type;
	this->text = text;

	int w = 0, h = 0;
	App->fonts->CalcSize(this->text.GetString(), w, h, App->fonts->default);
	texture = App->fonts->Print(text.GetString(), { 255,255,255,255 }, App->fonts->default);
}
GUI_Label::~GUI_Label() {

	text.Clear();
	text = nullptr;
	App->tex->UnLoad(texture);
	texture = nullptr;
	delete texture;
}

void GUI_Label::SetText()
{

}
