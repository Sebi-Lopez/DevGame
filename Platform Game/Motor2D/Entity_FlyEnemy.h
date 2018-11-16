#ifndef __j1FlyEnemy_H__
#define __j1FlyEnemy_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include"j1Entity.h"
#include"PugiXml/src/pugixml.hpp"
#include"PugiXml/src/pugiconfig.hpp"


struct SDL_Texture;
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
	FLYING_FORWARD,
	FLYING_BACKWARD,
	DEAD,
	NONE
};
class Entity_FlyEnemy : public j1Entity
{
public:
	Entity_FlyEnemy(int x, int y, pugi::xml_node& node);
	~Entity_FlyEnemy();

	// Called before all Updates

	void Update(float dt);

	bool CleanUp();

	void CalculatePosition();

	void CalculateTime();

	void SetPlayerState();

	void SetPlayerActions();


	// Collision Callback
	void OnCollision(Collider* c2);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	void SetAnimation(pugi::xml_node& node, Animation& anim);
private:

	STATE State = STATE::IDLE;

	// Animations 

	Animation fly;
	Animation flyinpath;
	Animation die;

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

};

#endif



