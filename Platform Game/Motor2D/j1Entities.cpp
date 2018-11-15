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


j1Entities::j1Entities() : j1Module()
{
	name.create("entities");

}

j1Entities::~j1Entities()
{}


bool j1Entities::Awake(pugi::xml_node& config)
{
	entitynode = config;
	
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
	
	for (uint i = 0; i < entities.count(); i++)
	{
		if (entities.At(i) != nullptr)
			entities.At(i)->data->Update(dt);
	}
	
	
	for (uint i = 0; i < entities.count(); i++)
	{
		if (entities.At(i) != nullptr)
			entities.At(i)->data->Draw();
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
	
	return true;
}

bool j1Entities::CreateEntities(EntityType type, int x, int y)
{
	bool ret = false;
	switch (type)
	{
	case EntityType::PLAYER: {
		player = new Entity_Player(x, y,entitynode);
		entities.add(player);
		ret = true;
		break;
	}
	}

	return true;
}


void j1Entities::OnCollision(Collider* c1, Collider* c2)
{

	for (int i = 0; i < entities.count(); i++)
	{
		if (entities.At(i)->data->GetCollider() == c1)
			entities.At(i)->data->OnCollision(c2);
	}

}


bool j1Entities::Load(pugi::xml_node& data)
{
	bool ret = true;



	for (int i = 0; i < entities.count(); i++)
	{
		if (entities.At(i)->data->entitytype == PLAYER)
		{
			pugi::xml_node player_stats = data.child("player");
			entities.At(i)->data->Load(player_stats);
		}

	}


	return ret;
}

bool j1Entities::Save(pugi::xml_node& data)const
{
	bool ret = true;


	for (int i = 0; i < entities.count(); i++)
	{
		if (entities.At(i)->data->entitytype == PLAYER)
		{
			pugi::xml_node player_stats = data.append_child("player");
			entities.At(i)->data->Save(player_stats);
		}
	}

	return ret;
}
