#include "j1App.h"
#include "j1Textures.h"
#include "jPlayer.h"
#include "j1Module.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1App.h"
#include "p2Log.h"


jPlayer::jPlayer()
{
	name.create("player");

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
	
	
	position.x = 100; 
	position.y = 200;
	return true;
}

bool jPlayer::PreUpdate()
{
	SDL_Rect r { 100,100,100,100 };
	App->render->Blit(player_texture, 0, 0);

	return true;
}

bool jPlayer::Update()
{

	return true;
}

bool jPlayer::CleanUp()
{
	App->tex->UnLoad(player_texture);
	return true;
}
