#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include"j1Entity.h"
#include"PugiXml/src/pugixml.hpp"
#include"PugiXml/src/pugiconfig.hpp"


#define RANGE 500

enum class E_STATE 
{
	NONE = -1,
	IDLE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	

	
};

class Entity_Enemy : public j1Entity
{
public:
	Entity_Enemy(int x, int y, pugi::xml_node& node);
	~Entity_Enemy();

	// Called before all Updates

	void Update(float dt);

	bool CleanUp();

	void CalculatePosition(float dt);

	void CalculateTime();

	void SetEnemyState();

	void SetEnemyActions();

	bool CheckPlayerOnRange(); 
	E_STATE SetDirection(const iPoint& go_to);

	// Collision Callback
	void OnCollision(Collider* c2);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:
	Animation idle;
	Animation run;
	Animation fall;
	Animation dead;

	fPoint velocity; 
	fPoint acceleration; 
	float gravity = 150;
	float run_speed = 100;
	float max_velocity = 300;


	int steps_to = 0; 
	bool to_move = false; 
	iPoint go_to;
	E_STATE e_state = E_STATE::IDLE;
};


#endif // !__FLYENEMY_H__

