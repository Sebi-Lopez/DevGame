#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1GUI.h"
#include "GUI_Label.h"
#include "GUI_Button.h"
#include "GUI_Slider.h"
#include "GUI_Logo.h"
#include "j1FadeToBlack.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Entities.h"
#include "j1MainMenu.h"
#include "j1Collision.h"
#include "j1Settings.h"
#include "j1Credits.h"
#include "j1Audio.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PostUpdate()
{
	for (int i = 0; i < objects.Count(); i++) {
		if (objects[i] != nullptr)
			objects[i]->Update();
	}
	for (int i = 0; i < objects.Count(); i++) {
		if (objects[i] != nullptr)
			objects[i]->Draw(atlas);
	}
	return true;
}

// Called after all Updates

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}
GUI_Object* j1Gui::CreateLabel(int x, int y, p2SString text, GUI_Object* parent) {
	GUI_Object* label = new GUI_Label(x, y, text, UI_Type::LABEL, parent);
	objects.PushBack(label);
	return label;
}

GUI_Object* j1Gui::CreateButton(int x, int y, SDL_Rect firststep, SDL_Rect secondstep, SDL_Rect thirdstep, char* name, GUI_Object* parent) {
	GUI_Object* button = new GUI_Button(x, y, firststep, secondstep, thirdstep, name, UI_Type::BUTTON, parent);
	objects.PushBack(button);
	return button;
}

GUI_Object* j1Gui::CreateLogo(int x, int y, SDL_Rect& rect, GUI_Object* parent) {
	GUI_Object* logo = new GUI_Logo(x, y, rect, parent);
	objects.PushBack(logo);
	return logo;
}

GUI_Object* j1Gui::CreateSlider(int x, int y, uint initial_value, GUI_Object* parent) {
	GUI_Object* slider = new GUI_Slider(x, y, initial_value, parent);
	objects.PushBack(slider);
	return slider;
}

void j1Gui::SliderAction(GUI_Slider* slider)
{
	App->audio->MusicVolume(slider->value);
}

bool j1Gui::ButtonAction(p2SString button_name)
{
	if (button_name == "Play")
	{
		LOG("PLAY");
		if (App->game_paused == true) App->game_paused = false; 

		App->entities->active = true;
		App->collision->active = true;
		App->fade->FadeToBlack(App->menu, App->scene, 0.5f);
		
		App->gui->DestroyUI();
		
	}
	if (button_name == "Continue")
	{
		LOG("CONTINUE");
		if (App->game_paused == true) App->game_paused = false;

		App->entities->active = true;
		App->collision->active = true;
		App->fade->FadeToBlack(App->menu, App->scene, 0.5f);
		App->gui->DestroyUI();
		App->LoadGame("save_game.xml");
		
	}
	if (button_name == "Settings")
	{
		LOG("SETTINGS");
		App->fade->FadeToBlack(App->menu, App->settings, 0.5f);
		App->gui->DestroyUI();
		App->settings->active = true;
		App->settings->Start();
	}
	if (button_name == "Backsettings")
	{
		LOG("SETTINGS");
		
		App->fade->FadeToBlack(App->settings, App->menu, 0.5f);
		App->gui->DestroyUI();
		App->menu->active = true;
		App->menu->Start();
		
		
	}
	if (button_name == "Credits")
	{
		LOG("CREDITS");

		App->fade->FadeToBlack(App->menu, App->credits, 0.5f);
		App->gui->DestroyUI();
		App->credits->active = true;
		App->credits->Start();
	}
	if (button_name == "Backcredits")
	{
		LOG("SETTINGS");

		App->fade->FadeToBlack(App->credits, App->menu, 0.5f);
		App->gui->DestroyUI();
		App->menu->active = true;
		App->menu->Start();

	}
	if (button_name == "Web")
	{
		ShellExecute(NULL,"open","https://sebi-lopez.github.io/DevGame/",NULL,NULL,SW_SHOWNORMAL);
		
	}
	if (button_name == "Release")
	{
		ShellExecute(NULL, "open", "https://github.com/Sebi-Lopez/DevGame/releases", NULL, NULL, SW_SHOWNORMAL);

	}
	if (button_name == "Exit")
	{
		App->menu->exitgame = true;
	}
	if (button_name == "Resume")
	{
		App->gui->DestroyUI();
		App->entities->active = true;
		if (App->game_paused == true) App->game_paused = false; 
	}
	if (button_name == "Menu") {
		App->fade->FadeToBlack(App->scene, App->menu, 0.5f);
		App->gui->DestroyUI();
		App->menu->active = true;
		App->menu->Start();
	}
	return true;
}



// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

void j1Gui::DestroyUI()
{
	for (uint i = 0; i < objects.Count(); i++) {
		if (objects[i] != nullptr) {
			delete objects[i];
			objects[i] = nullptr;
		}
	}
	objects.Clear();
}

