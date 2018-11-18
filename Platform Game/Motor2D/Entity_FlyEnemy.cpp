#include "j1App.h"
#include "j1Textures.h"
#include "Entity_FlyEnemy.h"
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
#include "SDL_mixer\include\SDL_mixer.h"

Entity_FlyEnemy::Entity_FlyEnemy(int x, int y, pugi::xml_node& node) :j1Entity(x, y)
{
	animation = &idle;

	texture = App->tex->Load("textures/flyenemy.png");
	pugi::xml_node animations = node.child("animationsflyenemy");

	SetAnimation(animations.child("flyanimation").child("anim"), idle);
	idle.speed = animations.child("flyanimation").attribute("speed").as_float();
	idle.loop = animations.child("flyanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("flyinpathanimation").child("anim"), fly);
	fly.speed = animations.child("flyinpathanimation").attribute("speed").as_float();
	fly.loop = animations.child("flyinpathanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("deadanimation").child("anim"), dead);
	dead.speed = animations.child("deadanimation").attribute("speed").as_float();
	dead.loop = animations.child("deadanimation").attribute("loop").as_bool();


	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,13,21 }, COLLIDER_ENEMY, App->entities);
}
Entity_FlyEnemy::~Entity_FlyEnemy()
{}

bool Entity_FlyEnemy::CleanUp() {

	App->tex->UnLoad(texture);
	texture = nullptr;
	animation = nullptr;
	if (collider != nullptr)
	{
		collider->to_delete = true;
		collider = nullptr;
	}
	return true;
}


void Entity_FlyEnemy::Update(float dt) 
{
	centered = App->map->WorldToMap(position.x, position.y);
	if (PlayerIsOnRange())
	{
		BROFILER_CATEGORY("PathFinding Flyer Enemy", Profiler::Color::Sienna);

		CreatePath();
		SetDirection();
	}
	else f_state = F_STATE::IDLE;


	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		if (debug_draw == false) debug_draw = true;
		else debug_draw = false;
	}


	SetEnemyAnimation();
	CalculatePosition(dt);

}

void Entity_FlyEnemy::CalculatePosition(float dt)
{
	position = position + velocity * dt;
}

void Entity_FlyEnemy::SetEnemyAnimation()
{
	switch (f_state)
	{
	case F_STATE::IDLE:
		animation = &idle;
		velocity = fPoint(0, 0);
		break;
	case F_STATE::LEFT:
		animation = &fly;
		break;

	case F_STATE::RIGHT:
		animation = &fly;
		break;
	}
}

bool Entity_FlyEnemy::PlayerIsOnRange()
{
	fPoint p_position = App->entities->player->position;

	return !(p_position.x < position.x - RANGE || p_position.x > position.x + RANGE);
}

void Entity_FlyEnemy::CreatePath()
{
	fPoint player = App->entities->player->position;
	iPoint destination = App->map->WorldToMap(player.x, player.y);

	steps_to = App->pathfinding->CreatePath(centered, destination);
}

void Entity_FlyEnemy::SetDirection()
{
	if (steps_to > 0 && centered != go_to) {
		const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
		go_to = iPoint(path->At(0)->x, path->At(0)->y);

		fPoint direction;
		direction.x = go_to.x - centered.x;
		direction.y = go_to.y - centered.y;
		velocity = direction.Normalize() * run_speed;

		if (velocity.x < 0)
			f_state = F_STATE::LEFT;

		else f_state = F_STATE::RIGHT;

		if (debug_draw)
		{
			for (uint i = 0; i < path->Count(); ++i)
			{
				iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				SDL_Rect r;
				r.x = pos.x;
				r.y = pos.y;
				r.w = App->map->data.tile_width;
				r.h = App->map->data.tile_height;
				App->render->DrawQuad(r, 255, 0, 0, 100, true, true);
			}
		}
	}
}


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



