#ifndef __j1SETTINGS_H__
#define __j1SETTINGS_H__

#include "j1Module.h"
#include"GUI_Button.h"
#include"GUI_Label.h"
#include"GUI_Logo.h"

class GUI_Label;
class GUI_Button;
class GUI_Logo;
struct SDL_Texture;

class j1Settings : public j1Module
{
public:

	j1Settings();

	// Destructor
	virtual ~j1Settings();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();





public:


};

#endif // __j1SETTINGS_H__

