#include "j1App.h"
#include "j1Textures.h"
#include "Entity_Enemy.h"
#include "j1Entity.h"
#include "j1Entities.h"
#include "j1Module.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1Audio.h"
#include "j1Window.h"
#include "j1Map.h"
#include "Entity_Player.h"
#include "j1PathFinding.h"
#include "Brofiler/Brofiler.h"
#include "Entity_Coin.h"

#include "SDL_mixer\include\SDL_mixer.h"

Entity_Coin::Entity_Coin(int x, int y, pugi::xml_node& node) :j1Entity(x, y)
{
	animation = &idle;

	texture = App->tex->Load("textures/coin.png");
	pugi::xml_node animations = node.child("animationcoin");

	SetAnimation(animations.child("anim"), idle);
	
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,20,22 }, COLLIDER_COIN, App->entities);
}
Entity_Coin::~Entity_Coin()
{}

bool Entity_Coin::CleanUp() {

	App->tex->UnLoad(texture);
	if (collider != nullptr)
	{
		collider->to_delete = true;
		collider = nullptr;
	}
	return true;

}


void Entity_Coin::Update(float dt)
{

}

void Entity_Coin::OnCollision(Collider* c2)
{
	if (c2->type == COLLIDER_PLAYER)
	{
		to_delete = true; 
		collider->to_delete = true;
	}
}

bool Entity_Coin::Load(pugi::xml_node& node)
{

	return true;
}

bool Entity_Coin::Save(pugi::xml_node& node)const
{

	return true;
}



