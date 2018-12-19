#ifndef UI_BUTTON_H__
#define UI_BUTTON_H__

#include "GUI_Object.h"
#include "UI_Label.h"
struct SDL_Rect;
class UI_Button : public GUI_Object
{
private:
	SDL_Rect* mouseout;
	SDL_Rect* mousein;
	SDL_Rect* mouseclick;
	UI_Label* text = nullptr;

public:
	UI_Button(int x, int y, SDL_Rect* out, SDL_Rect* in, SDL_Rect* pressed, UI_Type type, GUI_Object* parent);
	~UI_Button();
	void SetAnimation(int clickstate);
	void SetText(UI_Label* text);
	void ButtonState();
};


#endif //UI_BUTTON_H__
