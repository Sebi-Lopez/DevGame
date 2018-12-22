#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "GUI_Object.h"
#include "j1Input.h"
#include "SDL/include/SDL_rect.h"
#include "p2Log.h"

GUI_Object::GUI_Object(int x, int y, GUI_Object* parent)
{
}

GUI_Object::~GUI_Object()
{
}

void GUI_Object::Draw(SDL_Texture* atlas)
{

	App->render->Blit(atlas, position.x, position.y, &section, 0.0F);
	App->render->Blit(texture, position.x, position.y);


}

void GUI_Object::Update()
{
	App->input->GetMousePosition(mousepos.x, mousepos.y);
	MouseInRect();
}

void GUI_Object::MouseInRect()
{

	if (mousepos.x > position.x && mousepos.x < position.x + section.w && mousepos.y > position.y && mousepos.y < position.y + section.h)
	{
		mousestate = MouseState::MOUSE_HOVER;

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			mousestate = MouseState::MOUSE_CLICKED;
		}
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
		{
			mousestate = MouseState::MOUSE_UP;
		}
	}
	else mousestate = MouseState::MOUSE_OUT;
}
