#ifndef UI_LABEL_H__
#define UI_LABEL_H__

#include "GUI_Object.h"

class UI_Label : public GUI_Object
{
public: 
	UI_Label(int x, int y, p2SString text, GUI_Object* parent);
	~UI_Label();
	void SetText();
public:
	p2SString text;
};


#endif //UI_LABEL_H__
