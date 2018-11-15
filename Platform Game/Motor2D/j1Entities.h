#ifndef _ModuleEntities_H_
#define _ModuleEntities_H_

#include "j1Module.h"
#include "p2DynArray.h"

class Entity_Player;


enum EntityType {
	PLAYER,
	NONE,
};

class j1Entity;
class Player;

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
	pugi::xml_node entitynode;


};

#endif
