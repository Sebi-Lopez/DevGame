#ifndef GUI_OBJECT_H__
#define GUI_OBJECT_H__

#include "j1Gui.h"
#include "p2Point.h"

class UI_Object 
{
public:
	iPoint position;


public:
	UI_Object(int x, int y);
	~UI_Object(); 

	void Draw();	
	void Drag(); 
};


#endif //GUI_OBJECT_H__