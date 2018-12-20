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
	//App->render->Blit(texture, position.x, position.y);

}

void GUI_Object::Update()
{
	App->input->GetMousePosition(mousepos.x,mousepos.y);
}
