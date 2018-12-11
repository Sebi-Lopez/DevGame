#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "GUI_Object.h"
#define CURSOR_WIDTH 2

struct UI_Object;

// TODO 1: Create your structure of classes

enum class UI_Type {
	LABEL,
	LOGO,
	BUTTON,
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
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	UI_Object* CreateUIObject(UI_Type type, int x, int y);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2List<UI_Object>* objects;
};

#endif // __j1GUI_H__