#ifndef UI_LABEL_H__
#define UI_LABEL_H__

#include "GUI_Object.h"

class UI_Label : public GUI_Object
{
public: 
	UI_Label(int x, int y, p2SString text, UI_Type type, GUI_Object* parent);
	~UI_Label();
public:
	p2SString text;
};


#endif //UI_LABEL_H__
