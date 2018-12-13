#include"UI_Label.h"
#include"j1Textures.h"
#include"j1App.h"

UI_Label::UI_Label(int x, int y, p2SString text, UI_Type type, GUI_Object* parent) :GUI_Object(x, y, parent) {

}
UI_Label::~UI_Label() {
	App->tex->UnLoad(texture);
	texture = nullptr;
	delete texture;
}