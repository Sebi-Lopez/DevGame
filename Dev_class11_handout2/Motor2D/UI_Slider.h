#ifndef UI_SLIDER_H__
#define UI_SLIDER_H__

#include "GUI_Object.h"


class UI_Slider : public GUI_Object
{
public:
	UI_Slider(int x, int y, GUI_Object* parent);
	~UI_Slider();
	void Update();
	void DragSlider();

private:
	SDL_Rect slidersection;
	SDL_Rect slider;
	

};


#endif //UI_SLIDER_H__