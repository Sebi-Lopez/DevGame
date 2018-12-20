#ifndef UI_LOGO_H__
#define UI_LOGO_H__

#include "GUI_Object.h"

struct SDL_Rect; 

class UI_Logo : public GUI_Object
{
public:
	UI_Logo(int x, int y, SDL_Rect& atlasrect, GUI_Object* parent);
};


#endif //UI_LOGO_H__
