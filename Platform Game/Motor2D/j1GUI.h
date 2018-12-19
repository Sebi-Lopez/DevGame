#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include"p2DynArray.h"
#include"Animation.h"
#define CURSOR_WIDTH 2

class UI_Object;
struct SDL_Texture;
struct SDL_Rect;
// TODO 1: Create your structure of classes

enum class UI_Type {
	LABEL,
	LOGO,
	BUTTON,
	SLIDER,
	NONE
};

// ---------------------------------------------------
class j1GUI : public j1Module
{
public:

	j1GUI();

	// Destructor
	virtual ~j1GUI();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool Update();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	UI_Object* CreateLogo(int x, int y, SDL_Rect* rect, Animation* animation, UI_Object* parent);
	UI_Object* CreateSlider(int x, int y, UI_Object* parent);
	UI_Object* CreateLabel(int x, int y, p2SString text, UI_Object* parent);
	UI_Object* CreateButton(int x, int y, SDL_Rect* firststep, SDL_Rect* secondstep, SDL_Rect* thirdstep, UI_Object* parent);

	const SDL_Texture* GetAtlas() const;
	void DestroyUI();

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2DynArray<UI_Object*> objects;
};

#endif // __j1GUI_H__
