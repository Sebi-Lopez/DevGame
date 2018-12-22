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
#include"j1Credits.h"

#include "SDL_mixer\include\SDL_mixer.h"



j1Credits::j1Credits() : j1Module()
{
	name.create("scene");
}


j1Credits::~j1Credits()
{}


bool j1Credits::Awake()
{
	LOG("Loading Scene");
	bool ret = true;


	return ret;
}


bool j1Credits::Start()
{
	//Background of credits
	SDL_Rect bg = { 72,561,512,384 };
	App->gui->CreateLogo(0, 0, bg, nullptr);

	//Web button
	App->gui->CreateButton(10,300, { 1027,203,129,33 }, { 1027,128,128,33 }, { 1027,164,128,30 }, "Web", nullptr);
	App->gui->CreateLabel(50,400,"Web",nullptr);

	//Last release button
	App->gui->CreateButton(350, 300, { 1027,203,129,33 }, { 1027,128,128,33 }, { 1027,164,128,30 }, "Release", nullptr);
	App->gui->CreateLabel(365, 400, "Release", nullptr);

	//Back button
	App->gui->CreateButton(10, 350, {1257,216,61,28}, {1339,216,61,28}, {1424,216,61,28},"Backcredits",nullptr);
	App->gui->CreateLabel(20,448,"Back",nullptr);

	return true;
}


bool j1Credits::PreUpdate()
{

	return true;
}


bool j1Credits::Update(float dt)
{



	return true;
}


bool j1Credits::PostUpdate()
{
	bool ret = true;

	

	return ret;
}


bool j1Credits::CleanUp()
{
	LOG("Freeing scene");


	return true;
}



