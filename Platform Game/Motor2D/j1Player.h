#ifndef __j1Player_H__
#define __j1Player_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"


struct SDL_Texture;
struct Collider; 

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate(); 
	// Called before quitting
	bool CleanUp();

		
	void CalculatePosition(); 
	void CalculateTime();
	// Collision Callback
	void OnCollision(Collider* c1, Collider* c2);

private:
	
	Animation* current_animation;
	Animation idle;
	Animation run_forward;
	Animation run_backward;
	Animation jump;
	Animation fall;
	Animation attack;
	Animation climb;
	Animation grab;
	Animation idlesword;
	Animation hurt;
	Animation die;
	Animation slide;


	SDL_Texture* player_texture = nullptr;

	float speed_x = 60; 
	float speed_y = 100; 
	float gravity = 110; 
	fPoint velocity;
	fPoint acceleration;


	float time; 
	uint actual_time; 
	uint last_time = 0; 

public:

	fPoint position;
	
};

#endif

