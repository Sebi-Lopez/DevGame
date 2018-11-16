#ifndef _ModuleEntities_H_
#define _ModuleEntities_H_

#include "j1Module.h"
#include "p2DynArray.h"

class Entity_Player;
class Entity_Enemy;
class ENtity_FlyEnemy;


enum EntityType {
	PLAYER,
	ENEMY,
	FLYENEMY,
	NONE,
};

class j1Entity;
class Player;
class Enemy;
class FlyEnemy;

class j1Entities : public j1Module
{
public:
	j1Entities();
	~j1Entities();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool CreateEntities(EntityType type, int x, int y);

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);


	p2List<j1Entity*> entities;
	Entity_Player* player;
	Entity_Enemy* enemy;
	Entity_FlyEnemy* flyenemy;
	pugi::xml_node entitynode;


};

#endif
