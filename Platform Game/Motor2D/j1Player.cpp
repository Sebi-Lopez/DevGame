#include "j1App.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Module.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Collision.h"
#include "j1App.h"
#include "p2Log.h"

j1Player::j1Player()
{
	name.create("player");

	idle.PushBack({ 14,7,19,29 });
	idle.PushBack({ 66,6,17,30 });
	idle.PushBack({ 115,6,19,30 });
	idle.PushBack({ 163,7,20,29 });
	idle.speed = 0.2f;
	idle.loop = true;

	run_forward.PushBack({ 67,45,20,28 });
	run_forward.PushBack({ 116,46,20,27 });
	run_forward.PushBack({ 166,48,20,25 });
	run_forward.PushBack({ 217,45,23,28 });
	run_forward.PushBack({ 266,46,20,27 });
	run_forward.PushBack({ 316,48,20,25 });
	run_forward.speed = 0.2f;
	run_forward.loop = true;

	

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

	grab.PushBack({72,151,12,34});
	grab.PushBack({122,151,13,34});
	grab.PushBack({170,151,15,34});
	grab.PushBack({221,151,14,34});
	grab.speed = 0.15f;
	grab.loop = true;

	climb.PushBack({271,154,16,29});
	climb.PushBack({321,155,15,26});
	climb.PushBack({20,193,15,24});
	climb.PushBack({71,191,14,24});
	climb.PushBack({121,191,15,24});
	climb.speed = 0.2f;
	climb.loop = false;

	idlesword.PushBack({160,194,23,27});
	idlesword.PushBack({210,194,23,27});
	idlesword.PushBack({259,193,25,28});
	idlesword.PushBack({309,193,25,28});
	idlesword.speed = 0.15f;
	idlesword.loop = true;


	hurt.PushBack({166,308,21,24});
	hurt.PushBack({217,308,18,24});
	hurt.PushBack({265,308,19,24});
	hurt.speed = 0.2f;
	hurt.loop = false;

	die.PushBack({316,308,21,24});
	die.PushBack({17,345,18,24});
	die.PushBack({65,345,19,24});
	die.PushBack({116,347,20,22});
	die.PushBack({168,351,17,18});
	die.PushBack({221,352,14,17});
	die.PushBack({269,351,17,18});
	die.speed = 0.2f;
	die.loop = false;

	slide.PushBack({155,132,34,15});
	slide.PushBack({205,132,34,15});
	slide.PushBack({255,131,34,16});
	slide.PushBack({309,130,30,17});
	slide.PushBack({14,167,23,17});
	slide.speed = 0.2f;
	slide.loop = false;

	/*crouch.PushBack({216,15,19,21});
	crouch.PushBack({265,14,20,22});
	crouch.PushBack({315,15,19,21});
	crouch.PushBack({17,54,17,21});

	fall.PushBack({68,112,17,31});
	fall.PushBack({118,113,17,30});*/

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


	player_collider = App->collision->AddCollider({ (int)position.x, (int)position.y,19,29 }, COLLIDER_PLAYER,nullptr);
	return true;
}

bool j1Player::PreUpdate()
{

	current_animation = &idle;


	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE) {
		flip = false; 
		velocity.x = speed_x;
		current_animation = &run_forward;
		attacked = false;
		
	}
	
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE) {
		flip = true; 
		velocity.x = -speed_x;
		current_animation = &run_forward;
		attacked = false;
	}
	else
	{
		velocity.x = 0;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
		velocity.y =  - speed_y;
		current_animation = &jump;
	}
	else if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN) {
		
		current_animation = &attack;
		attacked = true;
	}
	else if (attacked == true) {
		current_animation = &idlesword;
		//attacked = false;
	}
	

	
	return true;
}

bool j1Player::Update(float dt)
{
	
	CalculateTime();
	CalculatePosition();
	App->render->Blit(player_texture, position.x, position.y, &(current_animation->GetCurrentFrame()), 1.0f, flip);
	player_collider->SetPos(position.x, position.y);
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
	future_position = position + velocity * (time + 0.1);
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
	if (c2->type == COLLIDER_FLOOR)
		velocity.y = 0; 
}

bool j1Player::SetAnimation(pugi::xml_node& node, Animation& anim) {
	return true; 
}


