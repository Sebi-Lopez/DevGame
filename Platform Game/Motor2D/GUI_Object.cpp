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
	if (texture == nullptr) {
		
		App->render->Blit(atlas, position.x, position.y, &section, 0.0F);
	}
	else {
		App->render->Blit(texture, position.x, position.y, (const SDL_Rect*)0, 0.0F);
	}

}

void GUI_Object::Update()
{
	App->input->GetMousePosition(mousepos.x, mousepos.y);
	MouseInRect();
}

void GUI_Object::MouseInRect()
{

	if (MouseInBorders())
	{
		mousestate = MouseState::MOUSE_HOVER;
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			clicked = true;
			selected = true;
		}
	}
	else mousestate = MouseState::MOUSE_OUT;

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
	{
		if (clicked) clicked = false;
		mouse_upped = true;
	}
}

bool GUI_Object::MouseInBorders()
{
	return (mousepos.x > position.x && mousepos.x < position.x + section.w && mousepos.y > position.y && mousepos.y < position.y + section.h);
}