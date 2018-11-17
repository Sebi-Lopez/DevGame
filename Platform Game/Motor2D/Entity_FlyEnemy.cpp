#include "j1App.h"
#include "j1Textures.h"
#include "Entity_FlyEnemy.h"
#include "j1Entity.h"
#include"j1Entities.h"
#include "j1Module.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "j1App.h"
#include "p2Log.h"
#include"j1Audio.h"
#include"j1Window.h"
#include"j1Map.h"
#include "SDL_mixer\include\SDL_mixer.h"

Entity_FlyEnemy::Entity_FlyEnemy(int x, int y, pugi::xml_node& node) :j1Entity(x, y)
{
	animation = &fly;

	sprites = App->tex->Load("textures/flyenemy.png");
	pugi::xml_node animations = node.child("animationsflyenemy");

	SetAnimation(animations.child("flyanimation").child("anim"), fly);
	fly.speed = animations.child("flyanimation").attribute("speed").as_float();
	fly.loop = animations.child("flyanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("flyinpathanimation").child("anim"), flyinpath);
	flyinpath.speed = animations.child("flyinpathanimation").attribute("speed").as_float();
	flyinpath.loop = animations.child("flyinpathanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("deadanimation").child("anim"), dead);
	dead.speed = animations.child("deadanimation").attribute("speed").as_float();
	dead.loop = animations.child("deadanimation").attribute("loop").as_bool();


	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,13,21 }, COLLIDER_ENEMY, App->entities);
}
Entity_FlyEnemy::~Entity_FlyEnemy()
{}

void Entity_FlyEnemy::Update(float dt) {

}

bool Entity_FlyEnemy::CleanUp() {

	App->tex->UnLoad(sprites);
	sprites = nullptr;
	animation = nullptr;
	if (collider != nullptr)
	{
		collider->to_delete = true;
		collider = nullptr;
	}
	return true;

}

void Entity_FlyEnemy::CalculatePosition()
{}

void Entity_FlyEnemy::CalculateTime()
{}

void Entity_FlyEnemy::SetEnemyState()
{}

void Entity_FlyEnemy::SetEnemyActions()
{}
void Entity_FlyEnemy::OnCollision(Collider* c2)
{}

bool Entity_FlyEnemy::Load(pugi::xml_node& node)
{

	return true;
}

bool Entity_FlyEnemy::Save(pugi::xml_node& node)const
{

	return true;
}



