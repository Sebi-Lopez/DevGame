#ifndef GUI_SLIDER_H__
#define GUI_SLIDER_H__

#include "GUI_Object.h"


class GUI_Slider : public GUI_Object
{
public:
	GUI_Slider(int x, int y, uint initial_value, bool labeled, GUI_Object* parent);
	~GUI_Slider();
	void Update();
	void DragSlider();
	void CalculateValue();


public:
	float value = min;

private:
	SDL_Rect slidersection;
	SDL_Rect slider;
	uint min = 0;
	uint max = 0;


};


#endif //UI_SLIDER_H__