#ifndef __COIN_H__
#define __COIN_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include"j1Entity.h"
#include"PugiXml/src/pugixml.hpp"
#include"PugiXml/src/pugiconfig.hpp"



class Entity_Coin : public j1Entity
{
public:
	Entity_Coin(int x, int y, pugi::xml_node& node);
	~Entity_Coin();

	// Called before all Updates

	void Update(float dt);

	bool CleanUp();


	// Collision Callback
	//void OnCollision(Collider* c2);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	void OnCollision(Collider* c2);


public:
	Animation idle;
	
};


#endif // !__COIN_H__


