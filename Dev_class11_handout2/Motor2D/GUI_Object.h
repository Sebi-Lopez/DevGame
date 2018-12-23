#ifndef GUI_OBJECT_H__
#define GUI_OBJECT_H__

#include "j1Gui.h"
#include "p2Point.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;
struct SDL_Rect;
struct UI_Button;

enum class MousePosition {
	MOUSE_OUT,
	MOUSE_HOVER,	
};

class GUI_Object 
{
public:
	iPoint position;
	UI_Type type;
	SDL_Texture* texture = nullptr;
	GUI_Object* parent;
	SDL_Rect section;
	MousePosition mouseposition = MousePosition::MOUSE_OUT; 
	bool clicked = false; 
	bool mouse_upped = false; 
	bool selected = false; 

	bool dragable = false; 
	//UI_Type ui_type = UI_Type::NONE;
	iPoint mousepos;
	

public:
	GUI_Object(int x, int y, GUI_Object* parent);
	virtual ~GUI_Object(); 

	virtual void Draw(SDL_Texture* atlas);	
	virtual void MouseInRect();
	virtual void Update();

	bool MouseInBorders();
	void Drag();
};


#endif //GUI_OBJECT_H__