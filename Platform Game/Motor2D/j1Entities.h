#ifndef _ModuleEntities_H_
#define _ModuleEntities_H_

#include "j1Module.h"
#include "p2DynArray.h"
#define MAX_ENTITIES 200

class j1Entity;
class Entity_Player;
class Entity_Enemy;
class Entity_FlyEnemy;
class Entity_Coin;
class Player;
class Enemy;
class FlyEnemy;
class Coin;

enum EntityType {
	PLAYER,
	ENEMY,
	FLYENEMY,
	COIN,
	NONE,
};



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
	void ClearEntities();
	bool SpawnEntities1();
	bool SpawnEntities2();


	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

public:
	uint player_lifes = 3; 


public: 

	p2DynArray<j1Entity*> entities;
	Entity_Player* player;
	Entity_Enemy* enemy;
	Entity_FlyEnemy* flyenemy;
	Entity_Coin* coin;
	pugi::xml_node entitynode;

	//map1 enemies
	fPoint enemypos1;
	fPoint enemypos2;
	fPoint enemypos3;
	fPoint flyenemypos1;
	fPoint flyenemypos2;
	fPoint flyenemypos3;
	//map2 enemies
	fPoint flyenemypos1map2;
	fPoint flyenemypos2map2;
	fPoint flyenemypos3map2;
	fPoint enemypos1map2;
	fPoint enemypos2map2;
	fPoint enemypos3map2;
	fPoint enemypos4map2;
	fPoint coin1;
	fPoint coin2;
	fPoint coin3;
	fPoint coin4;
	fPoint coin5;
	fPoint coin1map2;
	fPoint coin2map2;
	fPoint coin3map2;
	fPoint coin4map2;
	fPoint coin5map2;

};

#endif
