#ifndef __j1Player_H__
#define __j1Player_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"


struct SDL_Texture;
struct Collider; 

class j1Player : public j1Module
{
	enum class Reject
	{
		REJECT_LEFT,
		REJECT_RIGHT,
		REJECT_UP,
		REJECT_DOWN
	};
	enum class STATE 
	{
		IDLE = 1,
		RUNNING_FORWARD,
		RUNNING_BACKWARD,
		JUMPING,
		JUMPING_FORWARD,
		JUMPING_BACKWARD,
		DOUBLE_JUMP,
		DOUBLE_JUMP_FORWARD,
		DOUBLE_JUMP_BACKWARD,
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

	STATE State = STATE::FALLING;

	// Animations 
	Animation* current_animation = nullptr;
	Animation idle;
	Animation run;
	Animation jump;
	Animation double_jump;		// NOTICE ME -- I must be not LOOPABLE
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
	float fly_speed = 40;
	float jump_speed = 150; 
	float gravity = 250; 
	Reject reject = Reject::REJECT_UP;
	fPoint velocity;
	fPoint acceleration;
	bool isGrounded = false; 
	bool hasJumped = false;
	bool hasDoubleJumped = false; 
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

