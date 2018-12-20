#include "UI_Logo.h"
#include "SDL/include/SDL_rect.h"

UI_Logo::UI_Logo(int x, int y, SDL_Rect atlasrect, GUI_Object* parent) : GUI_Object(x, y, parent)
{
	position.x = x;
	position.y = y; 
	cut = atlasrect; 

	/*cut.x = atlasrect.x; 
	cut.y = atlasrect.y;
	cut.w = atlasrect.w;
	cut.h = atlasrect.h;*/

}
