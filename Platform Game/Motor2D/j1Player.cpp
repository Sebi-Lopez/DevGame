#include "j1App.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Module.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1App.h"
#include "p2Log.h"

j1Player::j1Player()
{
	name.create("player");

	idle.PushBack({ 14,7,19,29 });
	idle.PushBack({ 66,6,17,30 });
	idle.PushBack({ 115,6,19,30 });
	idle.PushBack({ 163,7,20,29 });
	idle.speed = 0.18f;
	idle.loop = true;

	run_forward.PushBack({ 67,45,20,28 });
	run_forward.PushBack({ 116,46,20,27 });
	run_forward.PushBack({ 166,48,20,25 });
	run_forward.PushBack({ 217,45,23,28 });
	run_forward.PushBack({ 266,46,20,27 });
	run_forward.PushBack({ 316,48,20,25 });
	run_forward.speed = 0.15f;
	run_forward.loop = true;

	run_backward.PushBack({376,375,20,28});
	run_backward.PushBack({327,376,20,27});
	run_backward.PushBack({277,378,20,25});
	run_backward.PushBack({223,375,23,28});
	run_backward.PushBack({177,376,20,27});
	run_backward.PushBack({127,378,20,25});
	run_backward.speed = 0.15f;
	run_backward.loop = true;

	attack.PushBack({7,263,27,22});
	attack.PushBack({58,238,25,20});
	attack.PushBack({115,222,33,36});
	attack.PushBack({165,222,27,36});
	attack.PushBack({215,226,19,32});
	attack.PushBack({265,232,18,26});
	attack.PushBack({315,231,18,27});
	attack.PushBack({13,268,20,27});
	attack.PushBack({60,266,38,29});
	attack.PushBack({102,274,32,21});
	attack.PushBack({152,273,31,22});
	attack.PushBack({219,269,20,26});
	attack.PushBack({270,269,20,26});
	attack.PushBack({302,272,48,23});
	attack.PushBack({3,313,31,19});
	attack.PushBack({50,312,34,20});
	attack.PushBack({100,312,34,20});
	attack.speed = 0.01f;
	attack.loop = false;

	jump.PushBack({ 317, 340, 23, 29 });
	jump.PushBack({ 18, 377, 22, 29 });
	jump.PushBack({ 68, 377, 22, 29 });
	jump.speed = 0.15f;
	jump.loop = false;

	grab.PushBack({});
	grab.PushBack({});
	grab.PushBack({});
	grab.PushBack({});

	climb.PushBack({});
	climb.PushBack({});
	climb.PushBack({});
	climb.PushBack({});
	climb.PushBack({});

	idlesword.PushBack({});
	idlesword.PushBack({});
	idlesword.PushBack({});
	idlesword.PushBack({});


	hurt.PushBack({});
	hurt.PushBack({});
	hurt.PushBack({});

	die.PushBack({});
	die.PushBack({});
	die.PushBack({});
	die.PushBack({});
	die.PushBack({});
	die.PushBack({});
	die.PushBack({});

	slide.PushBack({});
	slide.PushBack({});
	slide.PushBack({});
	slide.PushBack({});
	slide.PushBack({});

}

j1Player::~j1Player()
{
}

bool j1Player::Awake(pugi::xml_node& node)
{
	return true;
}

bool j1Player::Start()
{
	bool ret = true;
	player_texture = App->tex->Load("textures/character.png");
	if (player_texture != nullptr)
	{
		LOG("Player Texture Loaded Succesfully");
	}
	else
	{
		LOG("There was an error loading Player texture.");
	}


	last_time = actual_time = SDL_GetTicks();

	position.x = 10.f;
	position.y = 300.f;

	velocity.x = 0;
	velocity.y = 0;
	acceleration.x = 0;
	acceleration.y = 0;

	return true;
}

bool j1Player::PreUpdate()
{

	current_animation = &idle;


	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE) {
		velocity.x = speed_x;
		current_animation = &run_forward;
		flip = false;
	}

	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE) {
		velocity.x = -speed_x;
		current_animation = &run_forward;
		flip = true; 
	}
	else
	{
		velocity.x = 0;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		velocity.y =  - speed_y;
		acceleration.y = gravity;
		current_animation = &jump;
	}
	else if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN) {
		
		current_animation = &attack;
	}

	return true;
}

bool j1Player::Update(float dt)
{
	
	CalculateTime();
	CalculatePosition();
	App->render->Blit(player_texture, position.x, position.y, &(current_animation->GetCurrentFrame()), 1.0f, flip);

	return true;
}

bool j1Player::PostUpdate()
{
	return true;
}

bool j1Player::CleanUp()
{
	App->tex->UnLoad(player_texture);
	return true;
}

void j1Player::CalculatePosition()
{
	velocity = velocity + acceleration * time;
	position = position + velocity * time;
}

void j1Player::CalculateTime()
{
	actual_time = SDL_GetTicks();
	time = actual_time - last_time;
	time /= 1000;
	last_time = actual_time;
}

void j1Player::OnCollision(Collider * c1, Collider * c2)
{

}


