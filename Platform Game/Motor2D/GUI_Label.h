#ifndef GUI_LABEL_H__
#define GUI_LABEL_H__

#include "GUI_Object.h"

class GUI_Label : public GUI_Object
{
public:
	GUI_Label(int x, int y, p2SString text, UI_Type type, GUI_Object* parent);
	~GUI_Label();
public:
	p2SString text;
};


#endif //UI_LABEL_H__
