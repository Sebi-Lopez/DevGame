#ifndef __FLYENEMY_H__
#define __FLYENEMY_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include"j1Entity.h"
#include"PugiXml/src/pugixml.hpp"
#include"PugiXml/src/pugiconfig.hpp"

#define RANGE 400

enum class F_STATE
{
	NONE = -1,
	IDLE,
	LEFT,
	RIGHT
};

class Entity_FlyEnemy : public j1Entity
{
public:
	Entity_FlyEnemy(int x, int y, pugi::xml_node& node);
	~Entity_FlyEnemy();

	// Called before all Updates

	void Update(float dt);

	bool CleanUp();

	void CalculatePosition(float dt);

	void SetEnemyAnimation();

	bool PlayerIsOnRange();

	void CreatePath();

	void SetDirection();


	// Collision Callback
	void OnCollision(Collider* c2);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:
	Animation idle;
	Animation fly;
	Animation dead;

	fPoint velocity;
	float run_speed = 50;

	iPoint centered;
	int steps_to = 0;
	iPoint go_to;
	F_STATE f_state = F_STATE::IDLE;
};


#endif // !__FLYENEMY_H__


