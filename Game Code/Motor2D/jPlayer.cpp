#include "j1App.h"
#include "j1Textures.h"
#include "jPlayer.h"
#include "j1Module.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1App.h"
#include "p2Log.h"


jPlayer::jPlayer()
{
	name.create("player");

	idle.PushBack({14,7,19,29});
	idle.PushBack({ 66,6,17,30 });
	idle.PushBack({ 115,6,19,30 });
	idle.PushBack({ 163,7,20,29 });
	idle.speed = 0.01f;
	idle.loop = true;

	run_forward.PushBack({67,45,20,28});
	run_forward.PushBack({116,46,20,27});
	run_forward.PushBack({166,48,20,25});
	run_forward.PushBack({127,45,23,28});
	run_forward.PushBack({266,46,20,27});
	run_forward.PushBack({316,48,20,25});
	run_forward.speed = 0.01f;
	run_forward.loop = true;

	run_backward.PushBack({ 395,375,20,28 });
	run_backward.PushBack({ 346,376,20,27});
	run_backward.PushBack({ 296,378,20,25});
	run_backward.PushBack({ 245,375,23,28});
	run_backward.PushBack({ 196,376,20,27});
	run_backward.PushBack({ 146,378,20,25});
	run_backward.speed = 0.01f;
	run_backward.loop = true;
}

jPlayer::~jPlayer()
{
}

bool jPlayer::Awake(pugi::xml_node& node)
{	
	return true;
}

bool jPlayer::Start()
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
	position.y = 10.f;
	return true;
}

bool jPlayer::PreUpdate()
{

	

	return true;
}

bool jPlayer::Update(float dt)
{
	current_animation = &idle;
	

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){		
		position.x += 0.2f;
		current_animation = &run_forward;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		position.x -= 0.2f;
		current_animation = &run_backward;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
		position.x += 0.2f;
		current_animation = &jump;
	}
	App->render->Blit(player_texture, position.x, position.y, &(current_animation->GetCurrentFrame()));
	return true;
}

bool jPlayer::CleanUp()
{
	App->tex->UnLoad(player_texture);
	return true;
}
