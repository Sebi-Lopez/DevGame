#include "j1App.h"
#include "j1Textures.h"
#include "Entity_Enemy.h"
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

Entity_Enemy::Entity_Enemy(int x, int y, pugi::xml_node& node) :j1Entity( x, y) 
{
	animation = &idle;

	sprites = App->tex->Load("textures/enemies.png");
	pugi::xml_node animations = node.child("animationsenemy");

	SetAnimation(animations.child("idleanimation").child("anim"), idle);
	idle.speed = animations.child("idleanimation").attribute("speed").as_float();
	idle.loop = animations.child("idleanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("runanimation").child("anim"), run);
	run.speed = animations.child("runanimation").attribute("speed").as_float();
	run.loop = animations.child("runanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("falleanimation").child("anim"), fall);
	fall.speed = animations.child("fallanimation").attribute("speed").as_float();
	fall.loop = animations.child("fallanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("deadanimation").child("anim"), dead);
	dead.speed = animations.child("deadanimation").attribute("speed").as_float();
	dead.loop = animations.child("deadanimation").attribute("loop").as_bool();


	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,15,22 }, COLLIDER_ENEMY, App->entities);
}
Entity_Enemy::~Entity_Enemy()
{}

void Entity_Enemy::Update(float dt) {

}

bool Entity_Enemy::CleanUp() {

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

void Entity_Enemy::CalculatePosition()
{}

void Entity_Enemy::CalculateTime()
{}

void Entity_Enemy::SetEnemyState()
{}

void Entity_Enemy::SetEnemyActions()
{}
void Entity_Enemy::OnCollision(Collider* c2)
{}

bool Entity_Enemy::Load(pugi::xml_node& node)
{
	
	return true;
}

bool Entity_Enemy::Save(pugi::xml_node& node)const
{
	
	return true;
}



