#include "UI_Logo.h"
#include "SDL/include/SDL_rect.h"
#include "j1Gui.h"
#include "j1App.h"
UI_Logo::UI_Logo(int x, int y, SDL_Rect& atlasrect, GUI_Object* parent) : GUI_Object(x, y, parent)
{
	position.x = x;
	position.y = y; 
	cut = atlasrect; 
	texture = App->gui->GetAtlas();
}
