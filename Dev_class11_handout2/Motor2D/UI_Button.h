#ifndef UI_BUTTON_H__
#define UI_BUTTON_H__

#include "GUI_Object.h"
#include "UI_Label.h"

struct SDL_Rect;
class UI_Button : public GUI_Object
{
private:
	SDL_Rect mouseout;
	SDL_Rect mousein;
	SDL_Rect mouseclick;
	UI_Label* text = nullptr;
	p2SString button_name; 
	bool interacted = false; 
	bool to_interact = false; 
public:

	UI_Button(int x, int y, SDL_Rect out, SDL_Rect in, SDL_Rect pressed, char* name, UI_Type type, GUI_Object* parent);

	~UI_Button();
	void SetText(UI_Label* text);
	void Update();
};


#endif //UI_BUTTON_H__
