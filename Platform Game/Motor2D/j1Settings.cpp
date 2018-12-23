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
#include "j1MainMenu.h"
#include "j1GUI.h"
#include"j1Settings.h"


#include "SDL_mixer\include\SDL_mixer.h"



j1Settings::j1Settings() : j1Module()
{
	name.create("scene");
}


j1Settings::~j1Settings()
{}


bool j1Settings::Awake()
{
	LOG("Loading Scene");
	bool ret = true;


	return ret;
}


bool j1Settings::Start()
{
	//Settings Background
	SDL_Rect bg = { 72,116,512,384 };
	App->gui->CreateLogo(0, 0, bg, nullptr);
	

	//settings window
	SDL_Rect window = {1275,333,190,166};
	App->gui->CreateLogo(165, 100, window, nullptr);

	//settings label
	App->gui->CreateLabel(215, 105, "Settings", nullptr);

	//Music label
	//App->gui->CreateLabel(175, 145, "Music Volume", nullptr);

	//Back button
	App->gui->CreateButton(175, 250, { 1257,216,61,28 }, { 1339,216,61,28 }, { 1424,216,61,28 }, "Backsettings", nullptr);
	App->gui->CreateLabel(182, 253, "Back", nullptr);

	// Slider
	App->gui->CreateSlider(165, 180, App->audio->GetVolume(), nullptr);

	return true;
}


bool j1Settings::PreUpdate()
{

	return true;
}


bool j1Settings::Update(float dt)
{



	return true;
}


bool j1Settings::PostUpdate()
{
	bool ret = true;

	

	return ret;
}


bool j1Settings::CleanUp()
{
	LOG("Freeing scene");


	return true;
}



