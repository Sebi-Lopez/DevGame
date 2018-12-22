#ifndef GUI_OBJECT_H__
#define GUI_OBJECT_H__

#include "j1Gui.h"
#include "p2Point.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;
struct SDL_Rect;
struct UI_Button;

enum class MouseState {
	MOUSE_OUT,
	MOUSE_HOVER,
	MOUSE_CLICKED,
	MOUSE_UP
};

class GUI_Object
{
public:
	iPoint position;
	UI_Type type = UI_Type::NON;
	SDL_Texture* texture = nullptr;
	GUI_Object* parent;
	SDL_Rect section;
	MouseState mousestate = MouseState::MOUSE_OUT;


	//UI_Type ui_type = UI_Type::NONE;
	iPoint mousepos;


public:
	GUI_Object(int x, int y, GUI_Object* parent);
	virtual ~GUI_Object();

	virtual void Draw(SDL_Texture* atlas);
	virtual void MouseInRect();
	virtual void Update();
};


#endif //GUI_OBJECT_H__