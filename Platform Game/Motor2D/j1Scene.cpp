#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "j1Player.h"
#include "SDL_mixer\include\SDL_mixer.h"



j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{

	
	App->map->Load("FirstMap.tmx");

	App->audio->PlayMusic(App->audio->music1.GetString());
	App->audio->MusicVolume(App->audio->volume);

	App->player->Activate();
	App->collision->Activate();
	App->map->Activate();
	App->audio->Activate();

	App->render->camera.x = 0;
	App->render->camera.y = -120;
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	
	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 10;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 10;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 10;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 10;


	else if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN) {
		volumechange = true;
		App->audio->VolumeChange(volumechange);
	}

	else if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN) {
		volumechange = false;
		App->audio->VolumeChange(volumechange);
	}
	

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		App->fade->FadeToBlack((j1Module*) this, (j1Module*)App->scene_2);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->fade->FadeToBlack((j1Module*)this, (j1Module*)this);



	App->map->Draw();

	
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	


	App->player->Deactivate();
	App->collision->Deactivate();
	App->map->Reset();
	App->audio->Deactivate();


	return true;
}
