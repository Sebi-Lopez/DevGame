#include"UI_Label.h"
#include"j1Textures.h"
#include"j1App.h"
#include"j1Fonts.h"
#include"j1Render.h"

UI_Label::UI_Label(int x, int y, p2SString text, GUI_Object* parent) :GUI_Object(x, y, parent) {
	position.x = x;
	position.y = y;
	this->type = type;
	this->text = text;

	int w = 0, h = 0;
	App->font->CalcSize(this->text.GetString(), w, h, App->font->default);
	texture = App->font->Print(text.GetString(), { 255,255,255,255 }, App->font->default);
}
UI_Label::~UI_Label() {

	text.Clear();
	text = nullptr;
	App->tex->UnLoad(texture);
	texture = nullptr;
	delete texture;
}

void UI_Label::SetText()
{

}
