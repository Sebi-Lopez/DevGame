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

	

}

j1Player::~j1Player()
{
}

bool j1Player::Awake(pugi::xml_node& node)
{
	SetAnimation(node.child("animations").child("idleanimation").child("anim"), idle);
	idle.speed = node.child("animations").child("idleanimation").attribute("speed").as_float();
	idle.loop = node.child("animations").child("idleanimation").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("runanimation").child("anim"), run);
	run.speed = node.child("animations").child("runanimation").attribute("speed").as_float();
	run.loop = node.child("animations").child("runanimation").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("jumpanimation").child("anim"), jump);
	jump.speed = node.child("animations").child("jumpanimation").attribute("speed").as_float();
	jump.loop = node.child("animations").child("jumpanimation").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("fallanimation").child("anim"), fall);
	fall.speed = node.child("animations").child("fallanimation").attribute("speed").as_float();
	fall.loop = node.child("animations").child("fallanimation").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("attackanimation").child("anim"), attack);
	attack.speed = node.child("animations").child("attackanimation").attribute("speed").as_float();
	attack.loop = node.child("animations").child("attackanimation").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("climbanimation").child("anim"), climb);
	climb.speed = node.child("animations").child("climbanimation").attribute("speed").as_float();
	climb.loop = node.child("animations").child("climbanimation").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("grabanimation").child("anim"), grab);
	grab.speed = node.child("animations").child("grabanimation").attribute("speed").as_float();
	grab.loop = node.child("animations").child("grabanimation").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("idlesword").child("anim"), idlesword);
	idlesword.speed = node.child("animations").child("idlesword").attribute("speed").as_float();
	idlesword.loop = node.child("animations").child("idlesword").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("hurtanimation").child("anim"), hurt);
	hurt.speed = node.child("animations").child("hurtanimation").attribute("speed").as_float();
	hurt.loop = node.child("animations").child("hurtanimation").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("dieanimation").child("anim"), die);
	die.speed = node.child("animations").child("dieanimation").attribute("speed").as_float();
	die.loop = node.child("animations").child("dieanimation").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("slideanimation").child("anim"), slide);
	slide.speed = node.child("animations").child("slideanimation").attribute("speed").as_float();
	slide.loop = node.child("animations").child("slideanimation").attribute("loop").as_bool();

	SetAnimation(node.child("animations").child("crouchanimation").child("anim"), crouch);
	crouch.speed = node.child("animations").child("crouchanimation").attribute("speed").as_float();
	crouch.loop = node.child("animations").child("crouchanimation").attribute("loop").as_bool();

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
		flip = false; 
		velocity.x = speed_x;
		current_animation = &run;
		attacked = false;
		
	}
	
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE) {
		flip = true; 
		velocity.x = -speed_x;
		current_animation = &run;
		attacked=false;
		 
	}
	else
	{
		velocity.x = 0;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
		velocity.y =  - speed_y;
		acceleration.y = gravity;
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
	if (App->input->GetKey(SDL_SCANCODE_RSHIFT) == KEY_REPEAT)
		current_animation = &crouch;
	
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

bool j1Player::SetAnimation(pugi::xml_node& node, Animation& anim) {

	for (; node; node = node.next_sibling("anim")) {
		SDL_Rect components;
		components.x = node.attribute("x").as_uint();
		components.y = node.attribute("y").as_uint();
		components.w = node.attribute("w").as_uint();
		components.h = node.attribute("h").as_uint();
		anim.PushBack(components);
	}
	return true;
}


