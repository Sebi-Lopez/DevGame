#ifndef __j1Player_H__
#define __j1Player_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"


struct SDL_Texture;
struct Collider; 

class j1Player : public j1Module
{
	enum class STATE {
		IDLE = 1,
		RUNNING_FORWARD,
		RUNNING_BACKWARD,
		JUMPING,
		JUMPING_FORWARD,
		JUMPING_BACKWARD,
		FALLING,
		FALLING_FORWARD,
		FALLING_BACKWARD,
		NONE
	};
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

	void SetAnimation(pugi::xml_node& node, Animation& anim);
	void CalculatePosition(); 
	void CalculateTime();

	void SetPlayerState();
	void SetPlayerActions(); 

	// Collision Callback
	void OnCollision(Collider* c1, Collider* c2);

private:

	// Animations 
	Animation* current_animation = nullptr;
	Animation idle;
	Animation run;
	Animation jump;
	Animation fall;
	Animation attack;
	Animation climb;
	Animation grab;
	Animation idlesword;
	Animation hurt;
	Animation die;
	Animation slide;
	Animation crouch;

	// Position variables
	float run_speed = 60; 
	float jump_speed = 100; 
	float gravity = 110; 
	fPoint velocity;
	fPoint acceleration;
	fPoint future_position; 
	
	// Collider variables
	
	Collider* player_collider = nullptr; 

	// Time variables
	float time; 
	uint actual_time; 
	uint last_time = 0; 

	// Graphic variables
	SDL_Texture* player_texture = nullptr;	
	bool flip = false;
	bool attacked = false;

public:

	fPoint position;
	
};

#endif

