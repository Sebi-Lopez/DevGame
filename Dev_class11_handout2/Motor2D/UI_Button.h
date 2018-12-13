#ifndef UI_BUTTON_H__
#define UI_BUTTON_H__

#include "GUI_Object.h"
#include "UI_Label.h"
struct SDL_Rect;
class UI_Button : public GUI_Object
{
private:
	SDL_Rect* firststep;
	SDL_Rect* secondstep;
	SDL_Rect* thirstep;
	UI_Label* text = nullptr;

public:
	UI_Button(int x, int y, SDL_Rect* rect, SDL_Rect* rect2, SDL_Rect* rect3, UI_Type type, GUI_Object* parent);
	~UI_Button();
	void setAnimation(int state);
	void SetText(UI_Label* text);
};


#endif //UI_BUTTON_H__
