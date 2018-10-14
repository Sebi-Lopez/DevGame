#include "j1App.h"
#include "j1Textures.h"
#include "j1Player.h"
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

j1Player::j1Player()
{
	name.create("player");

}

j1Player::~j1Player()
{
}

bool j1Player::Awake(pugi::xml_node& node)
{
	pugi::xml_node animations = node.child("animations");
	SetAnimation(animations.child("idleanimation").child("anim"),idle);
	idle.speed = animations.child("idleanimation").attribute("speed").as_float();
	idle.loop = animations.child("idleanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("runanimation").child("anim"), run);
	run.speed = animations.child("runanimation").attribute("speed").as_float();
	run.loop = animations.child("runanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("jumpanimation").child("anim"), jump);
	jump.speed = animations.child("jumpanimation").attribute("speed").as_float();
	jump.loop = animations.child("jumpanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("fallanimation").child("anim"), fall);
	fall.speed = animations.child("fallanimation").attribute("speed").as_float();
	fall.loop = animations.child("fallanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("attackanimation").child("anim"), attack);
	attack.speed = animations.child("attackanimation").attribute("speed").as_float();
	attack.loop = animations.child("attackanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("climbanimation").child("anim"), climb);
	climb.speed = animations.child("climbanimation").attribute("speed").as_float();
	climb.loop = animations.child("climbanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("grabanimation").child("anim"), grab);
	grab.speed = animations.child("grabanimation").attribute("speed").as_float();
	grab.loop = animations.child("grabanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("idlesword").child("anim"), idlesword);
	idlesword.speed = animations.child("idlesword").attribute("speed").as_float();
	idlesword.loop = animations.child("idlesword").attribute("loop").as_bool();

	SetAnimation(animations.child("hurtanimation").child("anim"), hurt);
	hurt.speed = animations.child("hurtanimation").attribute("speed").as_float();
	hurt.loop = animations.child("hurtanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("dieanimation").child("anim"), die);
	die.speed = animations.child("dieanimation").attribute("speed").as_float();
	die.loop = animations.child("dieanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("slideanimation").child("anim"), slide);
	slide.speed = animations.child("slideanimation").attribute("speed").as_float();
	slide.loop = animations.child("slideanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("crouchanimation").child("anim"), crouch);
	crouch.speed = animations.child("crouchanimation").attribute("speed").as_float();
	crouch.loop = animations.child("crouchanimation").attribute("loop").as_bool();

	SetAnimation(animations.child("doublejanimation").child("anim"), double_jump);
	double_jump.speed = animations.child("doublejanimation").attribute("speed").as_float();
	double_jump.loop = animations.child("doublejanimation").attribute("loop").as_bool();

	//condicio de si es primer mapa o segon i carregar la posicio corresponents
	
	velocity.x = node.child("initial_attributes").attribute("velx").as_float();
	velocity.y = node.child("initial_attributes").attribute("vely").as_float();
	acceleration.x = node.child("initial_attributes").attribute("accx").as_float();
	gravity = node.child("initial_attributes").attribute("gravity").as_float();
	acceleration.y = gravity;
	run_speed = node.child("initial_attributes").attribute("runspeed").as_float();
	fly_speed = node.child("initial_attributes").attribute("flyspeed").as_float();
	jump_speed = node.child("initial_attributes").attribute("jumpspeed").as_float();
	god_speed = node.child("initial_attributes").attribute("godspeed").as_float();
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

	App->audio->LoadFx(App->audio->fxjump.GetString());
	last_time = actual_time = SDL_GetTicks();

	current_animation = &fall;
	State = STATE::FALLING;

	player_collider = App->collision->AddCollider({ (int)position.x, (int)position.y,19,29 }, COLLIDER_PLAYER, this);
	return true;
}

bool j1Player::PreUpdate()
{

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE) {
		flip = false;		
	}
	
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE) {
		flip = true; 
	}	

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (State != STATE::GOD)
		{
			State = STATE::GOD;
		}
		else
		{
			State = STATE::FALLING;
			player_collider->type = COLLIDER_TYPE::COLLIDER_PLAYER;
			acceleration.y = gravity;
		}

	}
	if (State != STATE::GOD) {
		SetPlayerState();
		SetPlayerActions();
	}
	else {
		player_collider->type = COLLIDER_TYPE::COLLIDER_NONE;
		acceleration.y = 0;
		velocity.y = 0;
		velocity.x = 0;
		current_animation = &idle;
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			position.x -= god_speed;

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			position.x += god_speed;

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			position.y -= god_speed;

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			position.y += god_speed;
	}

	CalculateTime();	
	CalculatePosition();

	return true;
}

bool j1Player::Update(float dt)

{
	App->render->Blit(player_texture, (int)position.x, (int)position.y, &(current_animation->GetCurrentFrame()), 1.0f, flip);

	return true;
}

bool j1Player::PostUpdate()

{
		
	return true;
}

bool j1Player::CleanUp()
{
	App->tex->UnLoad(player_texture);
	current_animation = nullptr; 
	if (player_collider != nullptr)
	{
		player_collider->to_delete = true;
		player_collider = nullptr;
	}
	player_texture = nullptr;
	return true;
}

void j1Player::CalculatePosition()
{
	velocity = velocity + acceleration * time;
	position = position + velocity * time + acceleration*time*time * 0.5F;
	player_collider->SetPos(position.x, position.y);

}

void j1Player::CalculateTime()
{
	actual_time = SDL_GetTicks();
	time = actual_time - last_time;
	time /= 1000;			
	last_time = actual_time;
}

void j1Player::SetPlayerState()
{

	// Input cases 

	bool pressed_right = (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT);
	bool pressed_left = (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT);
	bool released_right = (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP);
	bool released_left = (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP);
	bool pressed_space = (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN);

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
		if (double_jump.Finished())
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
		if (double_jump.Finished())
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
		if (double_jump.Finished())
		{
			State = STATE::FALLING;
		}
		break;
	}
}

void j1Player::SetPlayerActions()
{
	switch (State)
	{
	case STATE::IDLE:
		velocity.x = 0; 
		current_animation = &idle;
		hasJumped = false; 
		hasDoubleJumped = false;
		break;

	case STATE::RUNNING_FORWARD:
		velocity.x = run_speed; 
		current_animation = &run;
		break; 

	case STATE::RUNNING_BACKWARD:
		velocity.x = -run_speed;
		current_animation = &run;
		break;

	case STATE::JUMPING:		
		velocity.x = 0;
		current_animation = &jump;
		if (!hasJumped) 
		{

			App->audio->PlayFx(1);
			velocity.y = -jump_speed;			
			acceleration.y = gravity;		
			hasJumped = true;		
			isGrounded = false;
		}
		break;

	case STATE::JUMPING_FORWARD:
		velocity.x = fly_speed;
		break;

	case STATE::JUMPING_BACKWARD:
		velocity.x = -fly_speed;
		break;


	case STATE::FALLING:		
		velocity.x = 0;
		current_animation = &fall;
		double_jump.Reset();
		break;

	case STATE::FALLING_FORWARD:
		velocity.x = fly_speed;
		break;

	case STATE::FALLING_BACKWARD:
		velocity.x = -fly_speed;
		break;

	case STATE::DOUBLE_JUMP:
		velocity.x = 0;
		current_animation = &double_jump;
		if (!hasDoubleJumped)
		{
			App->audio->PlayFx(1);
			velocity.y = -jump_speed;
			acceleration.y = gravity;
			hasDoubleJumped = true;
			isGrounded = false;
		}
		break;

	case STATE::DOUBLE_JUMP_FORWARD:
		velocity.x = fly_speed;
		break;

	case STATE::DOUBLE_JUMP_BACKWARD:
		velocity.x = -fly_speed;
		break;

	case STATE::DEAD:
		App->fade->FadeToBlack((j1Module*)App->scene, (j1Module*)App->scene);
		break;

	case STATE::WIN:
		App->fade->FadeToBlack((j1Module*)App->scene, (j1Module*)App->scene_2);
		break;
	}
}

void j1Player::OnCollision(Collider * c1, Collider * c2)
{
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_FLOOR) 
	{
		if (velocity.y >= 0) {
			position.y = c2->rect.y - c1->rect.h;
			acceleration.y = 0;
			isGrounded = true;
		}
		
		
		player_collider->SetPos(position.x, position.y);
	}

	if (c2->type == COLLIDER_DEAD)
		State = STATE::DEAD;
	 
	if (c2->type == COLLIDER_END)
		State = STATE::WIN;
}

void j1Player::SetAnimation(pugi::xml_node& node, Animation& anim) {
	SDL_Rect components;
	for (; node; node = node.next_sibling("anim")) {
		components.x = node.attribute("x").as_uint();
		components.y = node.attribute("y").as_uint();
		components.w = node.attribute("w").as_uint();
		components.h = node.attribute("h").as_uint();
		anim.PushBack(components);
	}
	
	
}

bool j1Player::Load(pugi::xml_node& node)
{
	pugi::xml_node load = node.child("playerattributes");
	position.x = load.attribute("x").as_float();
	position.y = load.attribute("y").as_float();
	
	
	p2SString state=load.attribute("state").as_string();
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

bool j1Player::Save(pugi::xml_node& node) const{
	pugi::xml_node save = node.append_child("playerattributes");

	save.append_attribute("x") = position.x;
	save.append_attribute("y") = position.y;
	
	
	
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

