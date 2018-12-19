#ifndef UI_BUTTON_H__
#define UI_BUTTON_H__

#include "UI_Object.h"
#include "UI_Label.h"
struct SDL_Rect;
class UI_Button : public UI_Object
{
private:
	SDL_Rect* firststep;
	SDL_Rect* secondstep;
	SDL_Rect* thirstep;
	UI_Label* text = nullptr;

public:
	UI_Button(int x, int y, SDL_Rect* rect, SDL_Rect* rect2, SDL_Rect* rect3, UI_Type type, UI_Object* parent);
	~UI_Button();

	void Update();

};


#endif //UI_BUTTON_H__

