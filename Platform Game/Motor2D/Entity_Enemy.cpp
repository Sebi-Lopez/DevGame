#include "j1App.h"
#include "j1Textures.h"
#include "Entity_Player.h"
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

Entity_Enemy::Entity_Enemy(int x, int y, pugi::xml_node& node) : j1Entity(x, y)
{
	
	animation = &idle;
	State = STATE::IDLE;

	sprites = App->tex->Load("textures/enemies.png");
	pugi::xml_node animations = node.child("animationsenemy");
	SetAnimation(animations.child("idleanimation").child("anim"), idle);

	SetAnimation(animations.child("runanimation").child("anim"), run);
	run.speed = animations.child("runanimation").attribute("speed").as_float();
	run.loop = animations.child("runanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("fallanimation").child("anim"), fall);
	fall.speed = animations.child("fallanimation").attribute("speed").as_float();
	fall.loop = animations.child("fallanimation").attribute("loop").as_bool();


	SetAnimation(animations.child("deadanimation").child("anim"), die);
	die.speed = animations.child("deadanimation").attribute("speed").as_float();
	die.loop = animations.child("deadanimation").attribute("loop").as_bool();

	velocity.x = 0.0f;
	velocity.y = 0.0f;
	max_velocity = 300;

	acceleration.x = node.child("initial_attributes").attribute("accx").as_float();
	gravity = node.child("initial_attributes").attribute("gravity").as_float();
	acceleration.y = gravity;
	run_speed = node.child("initial_attributes").attribute("runspeed").as_float();
	fly_speed = node.child("initial_attributes").attribute("flyspeed").as_float();
	jump_speed = node.child("initial_attributes").attribute("jumpspeed").as_float();
	god_speed = node.child("initial_attributes").attribute("godspeed").as_float();

	if (sprites != nullptr)
	{
		LOG("Player Texture Loaded Succesfully");
	}
	else
	{
		LOG("There was an error loading Player texture.");

	}

	App->audio->LoadFx(App->audio->fxjump.GetString());
	last_time = actual_time = SDL_GetTicks();

	


	acceleration.y = gravity;



	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,15,22 }, COLLIDER_ENEMY, App->entities);
}

Entity_Enemy::~Entity_Enemy()
{
}


void Entity_Enemy::Update(float dt)
{

	

	SetPlayerState();
	SetPlayerActions();

	isGrounded = false;

	CalculateTime();
	CalculatePosition();
}


bool Entity_Enemy::CleanUp()
{
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
{
	velocity = velocity + acceleration * time;
	if (velocity.y > max_velocity) {
		velocity.y = max_velocity;
	}
	position = position + velocity * time;
	//collider->SetPos(position.x, position.y);
}

void Entity_Enemy::CalculateTime()
{
	actual_time = SDL_GetTicks();
	time = actual_time - last_time;
	time /= 1000;
	last_time = actual_time;
}

void Entity_Enemy::SetPlayerState()
{

	// Input cases 

	bool pressed_right = (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT);
	bool pressed_left = (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT);
	bool released_right = (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP);
	bool released_left = (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP);
	bool pressed_space = (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN);

	if (pressed_right && !pressed_left)
		flip = false;

	if (pressed_left && !pressed_right)
		flip = true;

	// Peak point of the parabol
	bool going_down = (velocity.y >= 0);

	switch (State)
	{
		// ON GROUND CASES

	case STATE::IDLE:
		if (pressed_right && !pressed_left)
		{
			State = STATE::RUNNING_FORWARD;
		}
		if (pressed_left && !pressed_right)
		{
			State = STATE::RUNNING_BACKWARD;
		}
		if (pressed_space)
		{
			State = STATE::JUMPING;
		}
		break;

	case STATE::RUNNING_FORWARD:
		if (released_right || pressed_left)
		{
			State = STATE::IDLE;
		}
		if (pressed_space)
		{
			State = STATE::JUMPING;
		}
		if (!isGrounded)
		{
			State = STATE::FALLING;
		}
		break;

	case STATE::RUNNING_BACKWARD:
		if (released_left || pressed_right)
		{
			State = STATE::IDLE;
		}
		if (pressed_space)
		{
			State = STATE::JUMPING;
		}
		if (!isGrounded)
		{
			State = STATE::FALLING;
		}
		break;


		// JUMPING CASES

	case STATE::JUMPING:

		if (pressed_right && !pressed_left)
		{
			State = STATE::JUMPING_FORWARD;
		}
		if (pressed_left && !pressed_right)
		{
			State = STATE::JUMPING_BACKWARD;
		}
		if (going_down)
		{
			State = STATE::FALLING;
		}
		if (pressed_space && !hasDoubleJumped)
		{
			State = STATE::DOUBLE_JUMP;
		}
		break;

	case STATE::JUMPING_FORWARD:
		if (released_right || pressed_left)
		{
			State = STATE::JUMPING;
		}
		if (going_down)
		{
			State = STATE::FALLING;
		}
		if (pressed_space && !hasDoubleJumped)
		{
			State = STATE::DOUBLE_JUMP;
		}

		break;

	case STATE::JUMPING_BACKWARD:
		if (released_left || pressed_right)
		{
			State = STATE::JUMPING;
		}
		if (going_down)
		{
			State = STATE::FALLING;
		}
		if (pressed_space && !hasDoubleJumped)
		{
			State = STATE::DOUBLE_JUMP;
		}
		break;


		// FALLING CASES

	case STATE::FALLING:
		if (pressed_right && !pressed_left)
		{
			State = STATE::FALLING_FORWARD;
		}
		if (pressed_left && !pressed_right)
		{
			State = STATE::FALLING_BACKWARD;
		}
		if (isGrounded)
		{
			State = STATE::IDLE;
		}
		if (pressed_space && !hasDoubleJumped)
		{
			State = STATE::DOUBLE_JUMP;
		}
		break;

	case STATE::FALLING_FORWARD:
		if (released_right || pressed_left)
		{
			State = STATE::FALLING;
		}
		if (isGrounded)
		{
			State = STATE::IDLE;
		}

		if (pressed_space && !hasDoubleJumped)
		{
			State = STATE::DOUBLE_JUMP;
		}
		break;

	case STATE::FALLING_BACKWARD:
		if (released_left || pressed_right)
		{
			State = STATE::FALLING;
		}
		if (isGrounded)
		{
			State = STATE::IDLE;
		}

		if (pressed_space && !hasDoubleJumped)
		{
			State = STATE::DOUBLE_JUMP;
		}
		break;


		// DOUBLE JUMP CASES

	case STATE::DOUBLE_JUMP:
		if (pressed_right && !pressed_left)
		{

			State = STATE::DOUBLE_JUMP_FORWARD;
		}
		if (pressed_left && !pressed_right)
		{
			State = STATE::DOUBLE_JUMP_BACKWARD;
		}
		if (going_down)
		{
			State = STATE::FALLING;
		}
		
		break;

	case STATE::DOUBLE_JUMP_FORWARD:
		if (released_right || pressed_left)
		{
			State = STATE::DOUBLE_JUMP;
		}
		if (going_down)
		{
			State = STATE::FALLING;
		}
		
		break;

	case STATE::DOUBLE_JUMP_BACKWARD:
		if (released_left || pressed_right)
		{
			State = STATE::DOUBLE_JUMP;
		}
		if (going_down)
		{
			State = STATE::FALLING;
		}
		
		break;
	}
}

void Entity_Enemy::SetPlayerActions()
{
	switch (State)
	{
	case STATE::IDLE:
		velocity.x = 0;
		animation = &idle;
		hasJumped = false;
		hasDoubleJumped = false;
		break;

	case STATE::RUNNING_FORWARD:
		velocity.x = run_speed;
		animation = &run;
		break;

	case STATE::RUNNING_BACKWARD:
		velocity.x = -run_speed;
		animation = &run;
		break;

	case STATE::FALLING:
		velocity.x = 0;
		acceleration.y = gravity;
		animation = &fall;
		break;

	case STATE::FALLING_FORWARD:
		velocity.x = fly_speed;
		break;

	case STATE::FALLING_BACKWARD:
		velocity.x = -fly_speed;
		break;


	case STATE::DEAD:
		
		break;

	}
}

void Entity_Enemy::OnCollision(Collider * c2)
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
			isGrounded = true;
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

	if (c2->type == COLLIDER_DEAD)
		State = STATE::DEAD;

	if (c2->type == COLLIDER_END)
		State = STATE::WIN;

}

void Entity_Enemy::SetAnimation(pugi::xml_node& node, Animation& anim) {
	SDL_Rect components;
	for (; node; node = node.next_sibling("anim")) {
		components.x = node.attribute("x").as_uint();
		components.y = node.attribute("y").as_uint();
		components.w = node.attribute("w").as_uint();
		components.h = node.attribute("h").as_uint();
		anim.PushBack(components);
	}
}

bool Entity_Player::Load(pugi::xml_node& node)
{
	pugi::xml_node load = node.child("enemyattributes");
	loadpos = true;
	bool wasSecondMap = load.child("map").attribute("value").as_bool();


	if (wasSecondMap == true)
	{

		if (isSecondMap == true) {
			App->fade->FadeToBlack((j1Module*)App->scene_2, (j1Module*)App->scene_2);
			position.x = load.attribute("x").as_float();
			position.y = load.attribute("y").as_float();

		}
		else {
			App->fade->FadeToBlack((j1Module*)App->scene, (j1Module*)App->scene_2);
			position.x = load.attribute("x").as_float();
			position.y = load.attribute("y").as_float();

		}
	}

	else
	{

		if (isSecondMap == true) {
			App->fade->FadeToBlack((j1Module*)App->scene_2, (j1Module*)App->scene);
			position.x = load.attribute("x").as_float();
			position.y = load.attribute("y").as_float();

		}
		else {
			App->fade->FadeToBlack((j1Module*)App->scene, (j1Module*)App->scene);
			position.x = load.attribute("x").as_float();
			position.y = load.attribute("y").as_float();

		}
	}

	p2SString state = load.attribute("state").as_string();
	if (state == "IDLE") {
		State = STATE::IDLE;
	}
	else if (state == "RUNNING_FORWARD") {
		State = STATE::RUNNING_FORWARD;
	}
	else if (state == "RUNNING_BACKWARD") {
		State = STATE::RUNNING_BACKWARD;
	}
	else if (state == "JUMPING") {
		State = STATE::JUMPING;
	}
	else if (state == "JUMPING_FORWARD") {
		State = STATE::JUMPING_FORWARD;
	}
	else if (state == "JUMPING_BACKWARD") {
		State = STATE::JUMPING_BACKWARD;
	}
	else if (state == "DOUBLE_JUMP") {
		State = STATE::DOUBLE_JUMP;
	}
	else if (state == "DOUBLE_JUMP_FORWARD") {
		State = STATE::DOUBLE_JUMP_FORWARD;
	}
	else if (state == "DOUBLE_JUMP_BACKWARD") {
		State = STATE::DOUBLE_JUMP_BACKWARD;
	}
	else if (state == "FALLING") {
		State = STATE::FALLING;
	}
	else if (state == "FALLING_FORWARD") {
		State = STATE::FALLING_FORWARD;
	}
	else if (state == "FALLING_BACKWARD") {
		State = STATE::FALLING_BACKWARD;
	}
	return true;

}

bool Entity_Enemy::Save(pugi::xml_node& node) const {
	pugi::xml_node save = node.append_child("enemyattributes");

	save.append_attribute("x") = position.x;
	save.append_attribute("y") = position.y;


	save.append_child("map").append_attribute("value") = isSecondMap;




	p2SString state;
	if (State == STATE::IDLE) {
		state = "IDLE";
	}
	else if (State == STATE::RUNNING_FORWARD) {
		state = "RUNNING_FORWARD";
	}
	else if (State == STATE::RUNNING_BACKWARD) {
		state = "RUNNING_BACKWARD";
	}
	else if (State == STATE::JUMPING) {
		state = "JUMPING";
	}
	else if (State == STATE::JUMPING_FORWARD) {
		state = "JUMPING_FORWARD";
	}
	else if (State == STATE::JUMPING_BACKWARD) {
		state = "JUMPING_BACKWARD";
	}
	else if (State == STATE::DOUBLE_JUMP) {
		state = "DOUBLE_JUMP";
	}
	else if (State == STATE::DOUBLE_JUMP_FORWARD) {
		state = "DOUBLE_JUMP_FORWARD";
	}
	else if (State == STATE::DOUBLE_JUMP_BACKWARD) {
		state = "DOUBLE_JUMP_BACKWARD";
	}
	else if (State == STATE::FALLING) {
		state = "FALLING";
	}
	else if (State == STATE::FALLING_FORWARD) {
		state = "FALLING_FORWARD";
	}
	else if (State == STATE::FALLING_BACKWARD) {
		state = "FALLING_BACKWARD";
	}


	save.append_attribute("state") = state.GetString();

	return true;
}



