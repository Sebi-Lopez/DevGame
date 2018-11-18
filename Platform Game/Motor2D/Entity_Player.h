#ifndef __j1Player_H__
#define __j1Player_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include"j1Entity.h"
#include"PugiXml/src/pugixml.hpp"
#include"PugiXml/src/pugiconfig.hpp"



struct Collider;



	enum class NextTo
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		MAX
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
		DEAD,
		WIN,
		GOD,
		NONE
	};
class Entity_Player : public j1Entity
{
public:
	Entity_Player(int x, int y, pugi::xml_node& node);
	~Entity_Player();

	// Called before all Updates
	
	void Update(float dt);

	bool CleanUp();

	void CalculatePosition(float dt);

	void CalculateTime();

	void SetPlayerState();

	void SetPlayerActions();


	// Collision Callback
	void OnCollision(Collider* c2);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
private:

	STATE State = STATE::FALLING;

	// Animations 
	
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
	float run_speed;
	float fly_speed;
	float jump_speed;
	float god_speed;
	float gravity;
	float max_velocity;
	fPoint velocity;
	fPoint acceleration;
	bool isGrounded = false;
	bool hasJumped = false;
	bool hasDoubleJumped = false;

	// Collider variables
	

	// Time variables
	float time;
	uint actual_time;
	uint last_time = 0;

	// Graphic variables

	
	bool attacked = false;
	bool loadpos = false;

public:

	//fPoint position;
	bool isSecondMap = false;
	bool flip = false;

};

#endif

