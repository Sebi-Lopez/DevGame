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


#include "SDL_mixer\include\SDL_mixer.h"



j1MainMenu::j1MainMenu() : j1Module()
{
	name.create("scene");
}


j1MainMenu::~j1MainMenu()
{}


bool j1MainMenu::Awake()
{
	LOG("Loading Scene");
	bool ret = true;


	return ret;
}


bool j1MainMenu::Start()
{
	//Main menu Background
	SDL_Rect bg = {72,116,512,384};
	App->gui->CreateLogo(0,0,bg,nullptr);
	//Jungle Jumper Title
	SDL_Rect titlerect = { 1310,100,190,48 };
	App->gui->CreateLogo(160, 80, titlerect,nullptr);
	App->gui->CreateLabel(170,185,"Jungle Jumper",nullptr);
	//Play button
	App->gui->CreateButton(185, 150, { 1027,203,129,33 }, {1027,128,128,33}, {1027,164,128,30},"Play",nullptr);
	App->gui->CreateLabel(220,250,"Play",nullptr);
	//Continue Button
	App->gui->CreateButton(185, 200, { 1027,203,129,33 }, { 1027,128,128,33 }, { 1027,164,128,30 }, "Continue", nullptr);
	App->gui->CreateLabel(200,300,"Continue",nullptr);
	//Settings Button
	App->gui->CreateButton(185, 250, { 1027,203,129,33 }, { 1027,128,128,33 }, { 1027,164,128,30 }, "Settings", nullptr);
	App->gui->CreateLabel(200, 350, "Settings", nullptr);
	//Credits Button
	App->gui->CreateButton(30, 320, { 1027,203,129,33 }, { 1027,128,128,33 }, { 1027,164,128,30 }, "Credits", nullptr);
	App->gui->CreateLabel(50, 420, "Credits", nullptr);
	//Exit Button
	App->gui->CreateButton(450, 320, { 1041,301,32,32 }, { 1080,301,32,32 }, { 1118,302,32,31 }, "Exit", nullptr);
	


	App->audio->PlayMusic(App->audio->music2.GetString());
	App->audio->MusicVolume(App->audio->volume);


	return true;
}


bool j1MainMenu::PreUpdate()
{
	
	return true;
}


bool j1MainMenu::Update(float dt)
{
	

	
	return true;
}


bool j1MainMenu::PostUpdate()
{
	bool ret = true;

	if (exitgame == true) {
		ret = false;
	}

	return ret;
}


bool j1MainMenu::CleanUp()
{
	LOG("Freeing scene");
	

	return true;
}



