#ifndef UI_SLIDER_H__
#define UI_SLIDER_H__

#include "GUI_Object.h"


class UI_Slider : public GUI_Object
{
public:
	UI_Slider(int x, int y, uint initial_value, SDL_Rect slidersection, GUI_Object* parent);
	~UI_Slider();
	void Update();
	void DragSlider();
	void CalculateValue(); 


public:
	float value = min;

private:
	SDL_Rect slidersection;
	SDL_Rect slider;
	iPoint fixed_position; 
	uint min = 0;
	uint max = 0;


};


#endif //UI_SLIDER_H__