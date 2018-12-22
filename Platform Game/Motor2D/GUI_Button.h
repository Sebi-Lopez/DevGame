#ifndef GUI_BUTTON_H__
#define GUI_BUTTON_H__

#include "GUI_Object.h"
#include "GUI_Label.h"

struct SDL_Rect;
class GUI_Button : public GUI_Object
{
private:
	SDL_Rect mouseout;
	SDL_Rect mousein;
	SDL_Rect mouseclick;
	GUI_Label* text = nullptr;
	p2SString button_name;
	bool interacted = false;
	bool to_interact = false;
public:
	GUI_Button(int x, int y, SDL_Rect out, SDL_Rect in, SDL_Rect pressed, char* name, UI_Type type, GUI_Object* parent);
	~GUI_Button();
	void Update();
};


#endif //UI_BUTTON_H__
