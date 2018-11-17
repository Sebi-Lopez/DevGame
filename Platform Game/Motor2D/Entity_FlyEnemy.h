#ifndef __FLYENEMY_H__
#define __FLYENEMY_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include"j1Entity.h"
#include"PugiXml/src/pugixml.hpp"
#include"PugiXml/src/pugiconfig.hpp"

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

	void SetEnemyState();

	void SetEnemyActions();


	// Collision Callback
	void OnCollision(Collider* c2);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:
	Animation fly;
	Animation flyinpath;
	Animation dead;



};


#endif // !__FLYENEMY_H__


