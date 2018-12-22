#ifndef GUI_LOGO_H__
#define GUI_LOGO_H__

#include "GUI_Object.h"

struct SDL_Rect;

class GUI_Logo : public GUI_Object
{
public:
	GUI_Logo(int x, int y, SDL_Rect& atlasrect, GUI_Object* parent);
};


#endif //UI_LOGO_H__
