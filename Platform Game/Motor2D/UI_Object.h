#ifndef UI_OBJECT_H__
#define UI_OBJECT_H__

#include "j1Gui.h"
#include "p2Point.h"
#include"j1GUI.h"
struct SDL_Texture;
struct SDL_Rect;
class UI_Object
{
public:
	iPoint position;
	UI_Type type;
	SDL_Texture* texture;
	UI_Object* parent;
	


public:
	UI_Object(int x, int y, UI_Object* parent);
	virtual ~UI_Object();

	virtual void Draw(SDL_Texture* atlas);
	virtual void Update();
};


#endif //UI_OBJECT_H__
