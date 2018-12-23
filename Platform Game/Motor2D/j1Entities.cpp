#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Entities.h"
#include "j1Entity.h"
#include "j1FadeToBlack.h"
#include"Entity_Player.h"
#include"Entity_Enemy.h"
#include"Entity_FlyEnemy.h"
#include"Entity_Coin.h"


j1Entities::j1Entities() : j1Module()
{
	name.create("entities");

}

j1Entities::~j1Entities()
{}


bool j1Entities::Awake(pugi::xml_node& config)
{
	entitynode = config;
	
	//map 1 enemies
	enemypos1.x = config.child("animationsenemy").child("map1").child("enemypos1").child("value").attribute("x").as_float();
	enemypos1.y = config.child("animationsenemy").child("map1").child("enemypos1").child("value").attribute("y").as_float();

	enemypos2.x = config.child("animationsenemy").child("map1").child("enemypos2").child("value").attribute("x").as_float();
	enemypos2.y = config.child("animationsenemy").child("map1").child("enemypos2").child("value").attribute("y").as_float();

	enemypos3.x = config.child("animationsenemy").child("map1").child("enemypos3").child("value").attribute("x").as_float();
	enemypos3.y = config.child("animationsenemy").child("map1").child("enemypos3").child("value").attribute("y").as_float();

	flyenemypos1.x = config.child("animationsflyenemy").child("map1").child("flyenemypos1").child("value").attribute("x").as_float();
	flyenemypos1.y = config.child("animationsflyenemy").child("map1").child("flyenemypos1").child("value").attribute("y").as_float();

	flyenemypos2.x = config.child("animationsflyenemy").child("map1").child("flyenemypos2").child("value").attribute("x").as_float();
	flyenemypos2.y = config.child("animationsflyenemy").child("map1").child("flyenemypos2").child("value").attribute("y").as_float();

	flyenemypos3.x = config.child("animationsflyenemy").child("map1").child("flyenemypos3").child("value").attribute("x").as_float();
	flyenemypos3.y = config.child("animationsflyenemy").child("map1").child("flyenemypos3").child("value").attribute("y").as_float();



	//map 2 enemies
	enemypos1map2.x = config.child("animationsenemy").child("map2").child("enemypos1").child("value").attribute("x").as_float();
	enemypos1map2.y = config.child("animationsenemy").child("map2").child("enemypos1").child("value").attribute("y").as_float();

	enemypos2map2.x = config.child("animationsenemy").child("map2").child("enemypos2").child("value").attribute("x").as_float();
	enemypos2map2.y = config.child("animationsenemy").child("map2").child("enemypos2").child("value").attribute("y").as_float();

	enemypos3map2.x = config.child("animationsenemy").child("map2").child("enemypos3").child("value").attribute("x").as_float();
	enemypos3map2.y = config.child("animationsenemy").child("map2").child("enemypos3").child("value").attribute("y").as_float();

	flyenemypos1map2.x = config.child("animationsflyenemy").child("map2").child("flyenemypos1").child("value").attribute("x").as_float();
	flyenemypos1map2.y = config.child("animationsflyenemy").child("map2").child("flyenemypos1").child("value").attribute("y").as_float();

	flyenemypos2map2.x = config.child("animationsflyenemy").child("map2").child("flyenemypos2").child("value").attribute("x").as_float();
	flyenemypos2map2.y = config.child("animationsflyenemy").child("map2").child("flyenemypos2").child("value").attribute("y").as_float();

	flyenemypos3map2.x = config.child("animationsflyenemy").child("map2").child("flyenemypos3").child("value").attribute("x").as_float();
	flyenemypos3map2.y = config.child("animationsflyenemy").child("map2").child("flyenemypos3").child("value").attribute("y").as_float();

	coin1.x = config.child("animationcoin").child("map1").child("coin1").child("value").attribute("x").as_float();
	coin1.y = config.child("animationcoin").child("map1").child("coin1").child("value").attribute("y").as_float();

	coin2.x = config.child("animationcoin").child("map1").child("coin2").child("value").attribute("x").as_float();
	coin2.y = config.child("animationcoin").child("map1").child("coin2").child("value").attribute("y").as_float();

	coin3.x = config.child("animationcoin").child("map1").child("coin3").child("value").attribute("x").as_float();
	coin3.y = config.child("animationcoin").child("map1").child("coin3").child("value").attribute("y").as_float();

	coin4.x = config.child("animationcoin").child("map1").child("coin4").child("value").attribute("x").as_float();
	coin4.y = config.child("animationcoin").child("map1").child("coin4").child("value").attribute("y").as_float();

	coin5.x = config.child("animationcoin").child("map1").child("coin5").child("value").attribute("x").as_float();
	coin5.y = config.child("animationcoin").child("map1").child("coin5").child("value").attribute("y").as_float();

	coin1map2.x = config.child("animationcoin").child("map2").child("coin1").child("value").attribute("x").as_float();
	coin1map2.y = config.child("animationcoin").child("map2").child("coin1").child("value").attribute("y").as_float();

	coin2map2.x = config.child("animationcoin").child("map2").child("coin2").child("value").attribute("x").as_float();
	coin2map2.y = config.child("animationcoin").child("map2").child("coin2").child("value").attribute("y").as_float();

	coin3map2.x = config.child("animationcoin").child("map2").child("coin3").child("value").attribute("x").as_float();
	coin3map2.y = config.child("animationcoin").child("map2").child("coin3").child("value").attribute("y").as_float();

	coin4map2.x = config.child("animationcoin").child("map2").child("coin4").child("value").attribute("x").as_float();
	coin4map2.y = config.child("animationcoin").child("map2").child("coin4").child("value").attribute("y").as_float();

	coin5map2.x = config.child("animationcoin").child("map2").child("coin5").child("value").attribute("x").as_float();
	coin5map2.y = config.child("animationcoin").child("map2").child("coin5").child("value").attribute("y").as_float();
	return true;
}

bool j1Entities::Start()
{
	
	return true;
}

bool j1Entities::PreUpdate()
{
	bool ret = true;

	for (uint i = 0; i < entities.Count(); i++)
	{
		if (entities[i]->to_delete == true)
		{
			delete entities[i];
			entities[i] = nullptr;
			entities.Pop(entities[i]);
		}
	}


	return ret;
}

bool j1Entities::Update(float dt)
{
	if (App->game_paused == false)
	{
		for (uint i = 0; i < entities.Count();i++)
		{
			if (entities.At(i) != nullptr)
				entities[i]->Update(dt);
		}
	
	}

	for (uint i = 0; i < entities.Count(); i++)
	{
		if (entities[i] != nullptr)
			entities[i]->Draw();
	}
	
	return true;
}

bool j1Entities::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool j1Entities::CleanUp()
{
	ClearEntities();
	return true;
}

bool j1Entities::CreateEntities(EntityType type, int x, int y)
{
	bool ret = false;
	switch (type)
	{
	case EntityType::PLAYER: {
		player = new Entity_Player(x, y,entitynode);
		entities.PushBack(player);
		ret = true;
		break;
	}
	case EntityType::ENEMY: {
		enemy = new Entity_Enemy(x, y, entitynode);
		entities.PushBack(enemy);
		ret = true;
		break;
	}
	case EntityType::FLYENEMY: {
		flyenemy = new Entity_FlyEnemy(x, y, entitynode);
		entities.PushBack(flyenemy);
		ret = true;
		break;
	}
	case EntityType::COIN: {
		coin = new Entity_Coin(x, y, entitynode);
		entities.PushBack(coin);
		ret = true;
		break;
	}
	}

	return ret;
}

bool j1Entities::SpawnEntities1() {

	CreateEntities(PLAYER, App->map->spawnpos.x, App->map->spawnpos.y);
	CreateEntities(ENEMY, App->entities->enemypos1.x, App->entities->enemypos1.y);
	CreateEntities(ENEMY, App->entities->enemypos2.x, App->entities->enemypos2.y);
	CreateEntities(ENEMY, App->entities->enemypos3.x, App->entities->enemypos3.y);
	CreateEntities(FLYENEMY, App->entities->flyenemypos1.x, App->entities->flyenemypos1.y);
	CreateEntities(FLYENEMY, App->entities->flyenemypos2.x, App->entities->flyenemypos2.y);
	CreateEntities(FLYENEMY, App->entities->flyenemypos3.x, App->entities->flyenemypos3.y);
	CreateEntities(COIN, coin1.x, coin1.y);
	CreateEntities(COIN, coin2.x, coin2.y);
	CreateEntities(COIN, coin3.x, coin3.y);
	CreateEntities(COIN, coin4.x, coin4.y);
	CreateEntities(COIN, coin5.x, coin5.y);

	
	return true;
}

bool j1Entities::SpawnEntities2()
{
	CreateEntities(PLAYER, App->map->spawnpos.x, App->map->spawnpos.y);
	CreateEntities(ENEMY, App->entities->enemypos1map2.x, App->entities->enemypos1map2.y);
	CreateEntities(ENEMY, App->entities->enemypos2map2.x, App->entities->enemypos2map2.y);
	CreateEntities(ENEMY, App->entities->enemypos3map2.x, App->entities->enemypos3map2.y);
	CreateEntities(FLYENEMY, App->entities->flyenemypos1map2.x, App->entities->flyenemypos1map2.y);
	CreateEntities(FLYENEMY, App->entities->flyenemypos2map2.x, App->entities->flyenemypos2map2.y);
	CreateEntities(FLYENEMY, App->entities->flyenemypos3map2.x, App->entities->flyenemypos3map2.y);
	CreateEntities(COIN, coin1map2.x, coin1map2.y);
	CreateEntities(COIN, coin2map2.x, coin2map2.y);
	CreateEntities(COIN, coin3map2.x, coin3map2.y);
	CreateEntities(COIN, coin4map2.x, coin4map2.y);
	CreateEntities(COIN, coin5map2.x, coin5map2.y);
	return true;
}

void j1Entities::ClearEntities()
{
	for (uint i = 0; i < entities.Count(); i++)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->collider != nullptr) 
			{
				entities[i]->collider->to_delete = true;
			}
			delete entities[i];
			entities[i] = nullptr;
		}
	}
	entities.Clear();

}

void j1Entities::OnCollision(Collider* c1, Collider* c2)
{

	for (int i = 0; i < entities.Count(); i++)
	{
		if (entities[i]->GetCollider() == c1)
			entities[i]->OnCollision(c2);
	}

}


bool j1Entities::Load(pugi::xml_node& data)
{
	bool ret = true;



	for (int i = 0; i < entities.Count(); i++)
	{
		if (entities[i]->entitytype == PLAYER)
		{
			pugi::xml_node player_stats = data.child("player");
			entities[i]->Load(player_stats);
		}
		/*if (entities[i]->entitytype == ENEMY)
		{
			pugi::xml_node enemy_stats = data.child("enemy");
			entities[i]->Load(enemy_stats);
		}
		if (entities[i]->entitytype == FLYENEMY)
		{
			pugi::xml_node flyenemy_stats = data.child("flyenemy");
			entities[i]->Load(flyenemy_stats);
		}*/
	}


	return ret;
}

bool j1Entities::Save(pugi::xml_node& data)const
{
	bool ret = true;


	for (int i = 0; i < entities.Count(); i++)
	{
		if (entities[i]->entitytype == PLAYER)
		{
			pugi::xml_node player_stats = data.append_child("player");
			entities[i]->Save(player_stats);
		}
		if (entities[i]->entitytype == ENEMY)
		{
			pugi::xml_node enemy_stats = data.append_child("enemy");
			entities[i]->Save(enemy_stats);
		}
		if (entities[i]->entitytype == FLYENEMY)
		{
			pugi::xml_node flyenemy_stats = data.append_child("flyenemy");
			entities[i]->Save(flyenemy_stats);
		}
	}

	return ret;
}


