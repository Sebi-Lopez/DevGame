#include "j1App.h"
#include "j1Textures.h"
#include"j1Render.h"
#include "GUI_Object.h"
#include"j1Input.h"
#include "SDL/include/SDL_rect.h"

GUI_Object::GUI_Object(int x, int y,GUI_Object* parent)
{
}

GUI_Object::~GUI_Object()
{
}

void GUI_Object::Draw(SDL_Texture* atlas)
{

	App->render->Blit(atlas, position.x, position.y, &cut, 0.0F);
	App->render->Blit(texture, position.x, position.y);

}

void GUI_Object::Update()
{
	App->input->GetMousePosition(mousepos.x,mousepos.y);
}

void GUI_Object::MouseInRect(GUI_Object* object) {

	

	if (mousepos.x > position.x && mousepos.x < position.x + buttonstate.w && mousepos.y > position.y && mousepos.y < position.y + buttonstate.h) {
		
		
	}
	if (mousepos.x > position.x && mousepos.x < position.x + buttonstate.w && mousepos.y > position.y && mousepos.y < position.y + buttonstate.h && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
		
	}
}
