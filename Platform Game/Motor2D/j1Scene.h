#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "GUI_Button.h"
#include "GUI_Label.h"
#include "j1Timer.h"
class GUI_Label;
class GUI_Object;
class GUI_Button;
struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

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

	bool SceneChange(int map);



public:
	bool volumechange = false;
	int map = 0;
	bool isFading=false;
	bool firstUpdate = true;
	bool isSecondMap = false;
	GUI_Button* button;
	GUI_Label* score_label = nullptr; 
	GUI_Label* score_text = nullptr;
	p2DynArray<GUI_Object*> menu_objects; 
	p2DynArray<GUI_Object*> hearts; 
};

#endif // __j1SCENE_H__