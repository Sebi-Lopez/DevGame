#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include"p2DynArray.h"
#define CURSOR_WIDTH 2

struct GUI_Object;
struct GUI_Slider; 
struct SDL_Texture;
struct SDL_Rect;

// TODO 1: Create your structure of classes

enum UI_Type {
	LABEL,
	LOGO,
	BUTTON,
	SLIDER,
	NON
};



// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	//bool Update(float dt);	Not needed? 

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	void SliderAction(GUI_Slider* slider);
	bool ButtonAction(p2SString button_name);

	GUI_Object* CreateLogo(int x, int y, SDL_Rect& rect, GUI_Object* parent);
	GUI_Object* CreateSlider(int x, int y, uint initial_value, bool labeled, GUI_Object* parent);
	GUI_Object* CreateLabel(int x, int y, p2SString text, GUI_Object* parent);
	GUI_Object* CreateButton(int x, int y, SDL_Rect firststep, SDL_Rect secondstep, SDL_Rect thirdstep, char* name, GUI_Object* parent);

	SDL_Texture* GetAtlas() const;
	void DestroyUI();

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2DynArray<GUI_Object*> objects;
};

#endif // __j1GUI_H__