#ifndef __j1SCENE_2_H__
#define __j1SCENE_2_H__

#include "j1Module.h"

struct SDL_Texture;

class j1Scene_2 : public j1Module
{
public:

	j1Scene_2();

	// Destructor
	virtual ~j1Scene_2();

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



private:
};

#endif // __j1SCENE_H__