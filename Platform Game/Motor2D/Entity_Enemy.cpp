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
#include "SDL_mixer\include\SDL_mixer.h"

Entity_Enemy::Entity_Enemy(int x, int y, pugi::xml_node& node) :j1Entity( x, y) 
{
	animation = &idle;

	texture = App->tex->Load("textures/enemies.png");
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

bool Entity_Enemy::CleanUp() {

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


void Entity_Enemy::Update(float dt) 
{
	/*centered = App->map->WorldToMap(position.x, position.y);
	if (PlayerIsOnRange())
	{		
		CreatePath(); 
		SetDirection();
	}	
	else e_state = E_STATE::IDLE;		
	
	
	SetEnemyAnimation();
	CalculatePosition(dt);*/
}

void Entity_Enemy::CreatePath()
{
	fPoint player = App->entities->player->position;
	iPoint destination = App->map->WorldToMap(player.x, player.y);

	steps_to = App->pathfinding->CreatePath(centered, destination);
}


bool Entity_Enemy::PlayerIsOnRange()
{
	fPoint p_position = App->entities->player->position;

	return !(p_position.x < position.x - RANGE || p_position.x > position.x + RANGE);
}


void Entity_Enemy::CalculatePosition(float dt)
{
	position = position + velocity * dt;
}


void Entity_Enemy::SetDirection()
{
	
	// Takes first node on the list and makes a vector pointing it
	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
	go_to = iPoint(path->At(0)->x, path->At(0)->y);

	fPoint direction;
	direction.x = go_to.x - centered.x;
	direction.y = go_to.y - centered.y;
	velocity = direction.Normalize() * run_speed;

	if (velocity.x < 0)
		e_state = E_STATE::LEFT;

	else e_state = E_STATE::RIGHT;





	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		if (debug_draw == false) debug_draw = true;
		else debug_draw = false;
	}


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

void Entity_Enemy::SetEnemyAnimation()
{
	switch (e_state)
	{
	case E_STATE::IDLE:
		animation = &idle; 
		velocity = fPoint(0, 0);
		break; 
	case E_STATE::LEFT:
		animation = &run; 
		break;

	case E_STATE::RIGHT:
		animation = &run;
		break;
	}
}


void Entity_Enemy::OnCollision(Collider* c2)
{
	if (c2->type == COLLIDER_FLOOR)
	{
		uint distance_up = (position.y + collider->rect.h) - c2->rect.y;
		uint distance_down = (c2->rect.y + c2->rect.h) - position.y;
		uint distance_left = (position.x + collider->rect.w) - (c2->rect.x);
		uint distance_right = (c2->rect.x + c2->rect.w) - position.x;

		uint distance[4];
		distance[0] = distance_up;
		distance[1] = distance_down;
		distance[2] = distance_left;
		distance[3] = distance_right;

		uint shortest = UINT_MAX;
		int shortestDir = -1;

		for (uint i = 0; i < 4; ++i) {
			if (distance[i] < shortest) {
				shortest = distance[i];
				shortestDir = i;
			}
		}

		switch (shortestDir) {
		case -1:
			LOG("Collision not detected properly");
			break;
		case 0:
			position.y = c2->rect.y - collider->rect.h;
			velocity.y = 0.0F;
			acceleration.y = 0.0F;
			//isGrounded = true;
			break;
		case 1:
			position.y = c2->rect.y + c2->rect.h + 1;
			velocity.y = 0.0F;
			acceleration.y = gravity;
			break;
		case 2:
			position.x = c2->rect.x - collider->rect.w;
			velocity.x = 0.0F;
			break;
		case 3:
			position.x = c2->rect.x + c2->rect.w + 1;
			velocity.x = 0.0F;
			break;
		}
	}
}

bool Entity_Enemy::Load(pugi::xml_node& node)
{
	
	return true;
}

bool Entity_Enemy::Save(pugi::xml_node& node)const
{
	
	return true;
}



