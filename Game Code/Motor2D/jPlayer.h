#ifndef __jPlayer_H__
#define __jPlayer_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"


class SDL_Texture;

class jPlayer : public j1Module 
{
public:
	jPlayer(); 
	~jPlayer(); 

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update(float dt);

	// Called before quitting
	bool CleanUp();


private: 
	fPoint position;
	Animation* current_animation; 
	Animation idle; 
	Animation run_forward; 
	Animation run_backward; 
	Animation jump; 
	Animation fall; 

	SDL_Texture* player_texture = nullptr; 
};

#endif