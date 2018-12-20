#ifndef GUI_OBJECT_H__
#define GUI_OBJECT_H__

#include "j1Gui.h"
#include "p2Point.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;
struct SDL_Rect;
class UI_Button;

class GUI_Object 
{
public:
	iPoint position;
	UI_Type type;
	SDL_Texture* texture;
	GUI_Object* parent;
	SDL_Rect cut;

	SDL_Rect buttonstate;
	UI_Type ui_type = UI_Type::NONE;
	iPoint mousepos;


public:
	GUI_Object(int x, int y, GUI_Object* parent);
	virtual ~GUI_Object(); 
	
	virtual void MouseInRect(GUI_Object* object);
	virtual void Draw(SDL_Texture* atlas);	
	virtual void Update();
};


#endif //GUI_OBJECT_H__