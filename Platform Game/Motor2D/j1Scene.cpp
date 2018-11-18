#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Scene.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "Entity_Player.h"
#include "j1Entities.h"
#include "j1Entity.h"
#include "Entity_Enemy.h"
#include "Brofiler/Brofiler.h"

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
	firstUpdate = true;
	if (!isFading && map == 0) {
		map = 1;

		App->entities->SpawnEntities1();
		if (App->map->Load("FirstMap.tmx") == true)
		{
			int w, h;
			uchar* data = NULL;
			if (App->map->CreateWalkabilityMap(w, h, &data))
				App->pathfinding->SetMap(w, h, data);

			RELEASE_ARRAY(data);

		}
	}
	

	App->audio->PlayMusic(App->audio->music2.GetString());
	App->audio->MusicVolume(App->audio->volume);
	

	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->map->WorldToMap(x, y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			LOG("Origin-> x: %i y: %i ||| Destination-> x: %i y: %i", origin.x, origin.y, p.x, p.y);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (firstUpdate == true && isFading == true) {
		App->render->camera.x = 0;
		App->render->camera.y = -190;
	}
	if (firstUpdate == true && isFading==true && !App->fade->IsFading()) {
		if (isSecondMap == true) {
			App->entities->SpawnEntities2();
		}
		else {
			App->entities->SpawnEntities1();
		}
		firstUpdate = false;
		isFading = false;
	}
	
	
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


	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN) {
		volumechange = true;
		App->audio->VolumeChange(volumechange);
	}

	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN) {
		volumechange = false;
		App->audio->VolumeChange(volumechange);
	}
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		map = 1;
		SceneChange(map);
		
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		SceneChange(map);
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		map = 2;
		SceneChange(map);
	}

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
	

	return true;
}

bool j1Scene::SceneChange(int map)
{
	
	isFading = true;
	if (map == 1) 
	{
		
		App->map->CleanUp();
		App->entities->ClearEntities();
		App->fade->FadeToBlack(this, this, 0.5f);
		App->map->Load("FirstMap.tmx");
		isSecondMap = false;
		
	}
	if (map == 2)
	{
		
		App->map->CleanUp();
		App->entities->ClearEntities();
		App->fade->FadeToBlack(this, this, 0.5f);
		App->map->Load("SecondMap.tmx");
		isSecondMap = true;
	}

	return true;
}



