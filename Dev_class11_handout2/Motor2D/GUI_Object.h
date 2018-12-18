#ifndef GUI_OBJECT_H__
#define GUI_OBJECT_H__

#include "j1Gui.h"
#include "p2Point.h"
struct SDL_Texture;
struct SDL_Rect;
class GUI_Object 
{
public:
	iPoint position;
	UI_Type type;
	SDL_Texture* texture;
	GUI_Object* parent;


public:
	GUI_Object(int x, int y, GUI_Object* parent);
	virtual ~GUI_Object(); 

	void Draw(SDL_Texture* atlas);	
	void Update(float dt); 
};


#endif //GUI_OBJECT_H__