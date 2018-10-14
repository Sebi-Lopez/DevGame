#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene_2.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "j1Player.h"



j1Scene_2::j1Scene_2() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene_2::~j1Scene_2()
{}

// Called before render is available
bool j1Scene_2::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene_2::Start()
{

	App->map->Load("SecondMap.tmx");
	App->audio->PlayMusic(App->audio->music2.GetString());
	App->player->IsSecondMap = true;
	App->player->Activate();	
	App->map->Activate();
	App->collision->Activate();
	App->audio->Activate();

	App->render->camera.x = 0;
	App->render->camera.y = -120;

	return true;
}

// Called each loop iteration
bool j1Scene_2::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene_2::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 10;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 10;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 10;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 10;

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		App->fade->FadeToBlack((j1Module*)this, (j1Module*)App->scene);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->fade->FadeToBlack((j1Module*)this, (j1Module*)this);


	App->map->Draw();

	
	return true;
}

// Called each loop iteration
bool j1Scene_2::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene_2::CleanUp()
{
	LOG("Freeing scene");

	App->player->Deactivate();
	App->collision->Deactivate();
	App->map->Reset();
	App->audio->Deactivate();
	return true;
}
