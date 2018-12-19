#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "UI_Label.h"
//#include "UI_Button.h"
//#include "UI_Slider.h"

j1GUI::j1GUI() : j1Module()
{
	name.create("gui");
}

// Destructor
j1GUI::~j1GUI()
{}

// Called before render is available
bool j1GUI::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1GUI::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1GUI::Update()
{
	for (uint i = 0; i < objects.Count(); i++)
	{
		if (objects[i] != nullptr)
			objects[i]->Update();
	}


	for (uint i = 0; i < objects.Count(); i++)
	{
		if (objects[i] != nullptr)
			objects[i]->Draw(atlas);
	}
	return true;
}

// Called after all Updates
bool j1GUI::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1GUI::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}
UI_Object* j1GUI::CreateLabel(int x, int y, p2SString text, UI_Object* parent) {
	UI_Object* label = new UI_Label(x, y, text, UI_Type::LABEL, parent);
	objects.PushBack(label);
	return label;
}
//
//GUI_Object* j1GUI::CreateButton(int x, int y, SDL_Rect* firststep, SDL_Rect* secondstep, SDL_Rect* thirdstep, GUI_Object* parent) {
//	GUI_Object* button = new UI_Button(x, y, firststep, secondstep, thirdstep, UI_Type::BUTTON, parent);
//	objects.PushBack(button);
//	return button;
//}
//
//GUI_Object* j1GUI::CreateSlider(int x, int y, GUI_Object* parent) {
//	GUI_Object* slider = new UI_Slider(x, y, UI_Type::SLIDER, parent);
//	objects.PushBack(slider);
//	return slider;
//}

//GUI_Object* j1Gui::CreateLogo(int x, int y, p2SString text, GUI_Object* parent) {
//	GUI_Object* logo = new UI_Logo(x, y, text, UI_Type::LABEL, parent);
//	objects.PushBack(logo);
//	return logo;
//}

// const getter for atlas
const SDL_Texture* j1GUI::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

void j1GUI::DestroyUI()
{
	for (uint i = 0; i < objects.Count(); i++) {
		if (objects[i] != nullptr) {
			delete objects[i];
			objects[i] = nullptr;
		}
	}
	objects.Clear();
}

