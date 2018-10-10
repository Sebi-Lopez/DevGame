#include "j1App.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Module.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1App.h"
#include "p2Log.h"

#define PLAYER_SPEED 1.f

j1Player::j1Player()
{
	name.create("player");

	idle.PushBack({ 14,7,19,29 });
	idle.PushBack({ 66,6,17,30 });
	idle.PushBack({ 115,6,19,30 });
	idle.PushBack({ 163,7,20,29 });
	idle.speed = 0.15f;
	idle.loop = true;

	run_forward.PushBack({ 67,45,20,28 });
	run_forward.PushBack({ 116,46,20,27 });
	run_forward.PushBack({ 166,48,20,25 });
	run_forward.PushBack({ 217,45,23,28 });
	run_forward.PushBack({ 266,46,20,27 });
	run_forward.PushBack({ 316,48,20,25 });
	run_forward.speed = 0.15f;
	run_forward.loop = true;

	jump.PushBack({ 317, 340, 23, 29 });
	jump.PushBack({ 18, 377, 22, 29 });
	jump.PushBack({ 68, 377, 22, 29 });
	jump.speed = 0.15f;
	jump.loop = false;

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


	position.x = 10.f;
	position.y = 300.f;
	return true;
}

bool j1Player::PreUpdate()
{



	return true;
}

bool j1Player::Update(float dt)
{
	current_animation = &idle;


	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		position.x += PLAYER_SPEED;
		current_animation = &run_forward;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		position.x -= PLAYER_SPEED;
		current_animation = &run_backward;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
		position.y -= PLAYER_SPEED;
		current_animation = &jump;
	}
	App->render->Blit(player_texture, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return true;
}

bool j1Player::CleanUp()
{
	App->tex->UnLoad(player_texture);
	return true;
}

bool j1Player::BlitImage() {

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		App->render->Blit(player_texture, position.x, position.y, &(current_animation->GetCurrentFrame()), SDL_FLIP_HORIZONTAL);
	}
	else {
		App->render->Blit(player_texture, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}
	return true;
}
