#include "GUI_Logo.h"
#include "SDL/include/SDL_rect.h"
#include "j1GUI.h"
#include "j1App.h"

GUI_Logo::GUI_Logo(int x, int y, SDL_Rect& atlasrect, GUI_Object* parent) : GUI_Object(x, y, parent)
{
	position.x = x;
	position.y = y;
	section = atlasrect;
	texture = App->gui->GetAtlas();
}
