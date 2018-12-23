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

#include "j1GUI.h"

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
	
	App->render->camera.x = 0;
	App->render->camera.y = -190;
	if (isSecondMap == false) {
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
	else
	{
		App->entities->SpawnEntities2();
	}
		
	
	
	
	App->audio->PlayMusic(App->audio->music2.GetString());
	App->audio->MusicVolume(App->audio->GetVolume());

	score_text = App->gui->CreateLabel(390, 5, "Score: ", nullptr);
	
	char score_tx[sizeof App->entities->player->score];
	sprintf_s(score_tx, "%d", App->entities->player->score);

	score_label = App->gui->CreateLabel(470, 5, score_tx, nullptr);
	score_label->SetText(score_tx);	
	score_text->SetText("Score: ");

	SDL_Rect heart = { 929,499, 16, 13 };
	for (uint i = 0; i < App->entities->player_lifes; i++)
	{
		hearts.PushBack(App->gui->CreateLogo(18*i, 10, heart, nullptr));
	}

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
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		if (App->game_paused == false)
		{
			App->game_paused = true;
			//window
			SDL_Rect window = { 1275,333,190,166 };
			menu_objects.PushBack(App->gui->CreateLogo(165, 100, window, nullptr));
			//Resume button
			menu_objects.PushBack(App->gui->CreateButton(195, 110, { 1027,203,129,33 }, { 1027,128,128,33 }, { 1027,164,128,30 }, "Resume", nullptr));
			menu_objects.PushBack(App->gui->CreateLabel(220, 115, "Resume", nullptr));
			//Exit Button
			menu_objects.PushBack(App->gui->CreateButton(195, 160, { 1027,203,129,33 }, { 1027,128,128,33 }, { 1027,164,128,30 }, "Menu", nullptr));
			menu_objects.PushBack(App->gui->CreateLabel(230, 165, "Menu", nullptr));

			// Slider
			menu_objects.PushBack(App->gui->CreateSlider(165, 215, App->audio->GetVolume(), true, nullptr));
		}
		else
		{
			App->game_paused = false;
			for (uint i = 0; i < menu_objects.Count(); i++)
			{
				App->gui->DestroyElement(*menu_objects.At(i));
			}
		}		
	}


	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame("save_game.xml");

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

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	
	for (uint i = 0; i < hearts.Count(); i++)
	{
		App->gui->DestroyElement(*hearts.At(i));
	}
	App->gui->DestroyElement(score_label);
	App->gui->DestroyElement(score_text);

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



