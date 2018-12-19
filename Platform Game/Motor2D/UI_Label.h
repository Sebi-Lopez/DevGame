#ifndef UI_LABEL_H__
#define UI_LABEL_H__

#include "UI_Object.h"

class UI_Label : public UI_Object
{
public:
	UI_Label(int x, int y, p2SString text, UI_Type type, UI_Object* parent);
	~UI_Label();
	void Draw();
public:
	p2SString text;
};


#endif //UI_LABEL_H__

