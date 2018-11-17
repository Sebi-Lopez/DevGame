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


j1Entities::j1Entities() : j1Module()
{
	name.create("entities");

}

j1Entities::~j1Entities()
{}


bool j1Entities::Awake(pugi::xml_node& config)
{
	entitynode = config;
	
	enemypos1.x = config.child("animationsenemy").child("enemypos1").child("value").attribute("x").as_float();
	enemypos1.y = config.child("animationsenemy").child("enemypos1").child("value").attribute("y").as_float();

	enemypos2.x = config.child("animationsenemy").child("enemypos2").child("value").attribute("x").as_float();
	enemypos2.y = config.child("animationsenemy").child("enemypos2").child("value").attribute("y").as_float();

	enemypos3.x = config.child("animationsenemy").child("enemypos3").child("value").attribute("x").as_float();
	enemypos3.y = config.child("animationsenemy").child("enemypos3").child("value").attribute("y").as_float();

	flyenemypos1.x = config.child("animationsflyenemy").child("flyenemypos1").child("value").attribute("x").as_float();
	flyenemypos1.y = config.child("animationsflyenemy").child("flyenemypos1").child("value").attribute("y").as_float();

	flyenemypos2.x = config.child("animationsflyenemy").child("flyenemypos2").child("value").attribute("x").as_float();
	flyenemypos2.y = config.child("animationsflyenemy").child("flyenemypos2").child("value").attribute("y").as_float();

	return true;
}

bool j1Entities::Start()
{
	
	return true;
}

bool j1Entities::PreUpdate()
{
	bool ret = true;

	return ret;
}

bool j1Entities::Update(float dt)
{
	
	for (uint i = 0; i < entities.Count();i++)
	{
		if (entities.At(i) != nullptr)
			entities[i]->Update(dt);
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
	}

	return ret;
}

bool j1Entities::SpawnEntities1() {
	
	App->entities->CreateEntities(ENEMY, App->entities->enemypos1.x, App->entities->enemypos1.y);
	App->entities->CreateEntities(ENEMY, App->entities->enemypos2.x, App->entities->enemypos2.y);
	App->entities->CreateEntities(ENEMY, App->entities->enemypos3.x, App->entities->enemypos3.y);
	App->entities->CreateEntities(FLYENEMY, App->entities->flyenemypos1.x, App->entities->flyenemypos1.y);
	App->entities->CreateEntities(FLYENEMY, App->entities->flyenemypos2.x, App->entities->flyenemypos2.y);
	
	return true;
}

bool j1Entities::SpawnEntities2()
{

	return true;
}

void j1Entities::ClearEntities()
{
	for (int i = 0; i < entities.Count(); i++)
	{
		if (entities[i] != nullptr) {
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
		if (entities[i]->entitytype == ENEMY)
		{
			pugi::xml_node enemy_stats = data.child("enemy");
			entities[i]->Load(enemy_stats);
		}
		if (entities[i]->entitytype == FLYENEMY)
		{
			pugi::xml_node flyenemy_stats = data.child("flyenemy");
			entities[i]->Load(flyenemy_stats);
		}
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
