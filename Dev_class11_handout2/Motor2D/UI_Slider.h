#ifndef UI_SLIDER_H__
#define UI_SLIDER_H__

#include "GUI_Object.h"

class UI_Slider : public GUI_Object
{
public:
	UI_Slider(int x, int y, UI_Type type, GUI_Object* parent);
	~UI_Slider();

};


#endif //UI_SLIDER_H__