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

	SetAnimation(node.child("animations").child("doublejanimation").child("anim"), double_jump);
	double_jump.speed = node.child("animations").child("doublejanimation").attribute("speed").as_float();
	double_jump.loop = node.child("animations").child("doublejanimation").attribute("loop").as_bool();

	position.x = node.child("initial_attributes").attribute("x").as_float();
	position.y = node.child("initial_attributes").attribute("y").as_float();
	velocity.x = node.child("initial_attributes").attribute("velx").as_float();
	velocity.y = node.child("initial_attributes").attribute("vely").as_float();
	acceleration.x = node.child("initial_attributes").attribute("accx").as_float();
	gravity = node.child("initial_attributes").attribute("gravity").as_float();
	acceleration.y = gravity;

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


	SetPlayerState(); 
	CalculateTime();			
	SetPlayerActions();
	CalculatePosition();

	return true;
}

bool j1Player::Update(float dt)
{	

	return true;
}

bool j1Player::PostUpdate()
{	
	App->render->Blit(player_texture, (int)position.x, (int)position.y, &(current_animation->GetCurrentFrame()), 1.0F, flip);
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

		
			//reject = Reject::REJECT_UP
		/*if (position.y + c1->rect.h < c2->rect.y)
		{
			reject = Reject::REJECT_UP;
		}
		else if (position.y > c2->rect.y + c2->rect.h)
		{
			reject = Reject::REJECT_DOWN;
		}
		else if (position.x + c1->rect.w < c2->rect.x)
		{
			reject = Reject::REJECT_LEFT;
		}
		else if (position.x > c2->rect.x + c2->rect.w)
		{
			reject = Reject::REJECT_RIGHT;
		}

		switch (reject)
		{
		case Reject::REJECT_UP:
			position.y = c2->rect.y - c1->rect.h;
			acceleration.y = 0;
			isGrounded = true; 
			break;

		case Reject::REJECT_DOWN:
			break;

		case Reject::REJECT_LEFT:
			position.x = c2->rect.x - c1->rect.w;	
			velocity.x = 0;
			break;

		case Reject::REJECT_RIGHT:
			position.x = c2->rect.x + c2->rect.w;
			velocity.x = 0;
			break;
		}*/
		player_collider->SetPos(position.x, position.y);
		/*switch (direction)
		{
		case Direction::GOING_DOWN:
			position.y = c2->rect.y - c1->rect.h;
			acceleration.y = 0;
			isGrounded = true;
			break;

		case Direction::GOING_UP:
			break;

		case Direction::GOING_RIGHT:
			position.x = c2->rect.x - c1->rect.w;
			break;

		case Direction::GOING_LEFT:
			position.x = c2->rect.x + c2->rect.w;
			break;
		}
			*/
	}
}

void j1Player::SetAnimation(pugi::xml_node& node, Animation& anim) {

	for (; node; node = node.next_sibling("anim")) {
		SDL_Rect components;
		components.x = node.attribute("x").as_uint();
		components.y = node.attribute("y").as_uint();
		components.w = node.attribute("w").as_uint();
		components.h = node.attribute("h").as_uint();
		anim.PushBack(components);
	}
}

bool j1Player::Save(pugi::xml_node& node) const{
	pugi::xml_node posave = node.append_child("player");

	posave.append_attribute("x") = position.x;
	posave.append_attribute("y") = position.y;

	return true;
}

