#include <iostream> 
#include <sstream> 

#include "p2Defs.h"
#include "p2Log.h"

#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1PathFinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "j1Entities.h"
#include "j1App.h"
#include "Brofiler/Brofiler.h"
#include "j1GUI.h"
#include "j1Fonts.h"
#include "j1MainMenu.h"
#include"j1Settings.h"
#include"j1Credits.h"

// Constructor
j1App::j1App(int argc, char* args[]) : argc(argc), args(args)
{
	PERF_START(ptimer);

	input = new j1Input();
	win = new j1Window();
	render = new j1Render();
	tex = new j1Textures();
	audio = new j1Audio();
	scene = new j1Scene();
	menu = new j1MainMenu();
	settings = new j1Settings();
	credits = new j1Credits();
	pathfinding = new j1PathFinding();
	map = new j1Map();
	collision = new j1Collision(); 
	fade = new j1FadeToBlack();
	entities = new j1Entities();
	gui = new j1Gui();
	fonts = new j1Fonts();


	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(map, false);
	AddModule(scene, false);
	AddModule(menu);
	AddModule(settings, false);
	AddModule(credits, false);
	AddModule(pathfinding, false);
	AddModule(entities, false);
	AddModule(collision, false);
	AddModule(fade);
	AddModule(gui);
	AddModule(fonts);


	// render last to swap buffer
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
j1App::~j1App()
{
	// release modules
	p2List_item<j1Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void j1App::AddModule(j1Module* module, bool active)
{
	if(active) module->Init();		// Now it only initiates the ones that are active

	modules.add(module);
}

// Called before render is available
bool j1App::Awake()
{
	PERF_START(ptimer);

	

	bool ret = false;
		
	config = LoadConfig(config_file);

	if(config.empty() == false)
	{
		// self-config
		ret = true;
		vsync_on = config.child("renderer").child("vsync").attribute("value").as_bool();
		app_config = config.child("app");
		title.create(app_config.child("title").child_value());
		organization.create(app_config.child("organization").child_value());
		framerate_cap = app_config.child("framerate_cap").attribute("frame_rate").as_int();
		if (framerate_cap == 30)
		{
			capped = true;
			frame_capstr = "On";
		}
		else
		{
			frame_capstr = "Off";
			capped = false; 
		}

		if (vsync_on)
		{
			vsyncstr = "On";
		}
		else vsyncstr = "Off";
	}

	if(ret == true)
	{
		p2List_item<j1Module*>* item;
		item = modules.start;

		while(item != NULL && ret == true)
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool j1App::Start()
{
	PERF_START(ptimer);

	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		if(item->data->active)				// Only Starts Modules that are active
			ret = item->data->Start();
		item = item->next;
	}
	startup_time.Start();

	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration
bool j1App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if (ret == true)
	{
		BROFILER_CATEGORY("PreUpdateLogic", Profiler::Color::Sienna);
		ret = PreUpdate();
	}

	if (ret == true)
	{
		BROFILER_CATEGORY("UpdateLogic", Profiler::Color::LimeGreen);

		ret = DoUpdate();
	}

	if (ret == true)
	{
		BROFILER_CATEGORY("PostUpdateLogic", Profiler::Color::Purple);
		ret = PostUpdate();
	}
	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node j1App::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;
	pugi::xml_parse_result result = config_file.load_file("config.xml");

	if(result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");

	return ret;
}

// ---------------------------------------------
void j1App::PrepareUpdate()
{	
	frame_count++;
	last_sec_frame_count++;

	if (game_paused)
	{
		dt = 0; 
	}
	else 
	{
		dt = frame_time.ReadSec();
		if (dt > 1)
		{
			dt = 1 / (float)framerate_cap;
		}
	}	
	LOG("DT: %f", dt);
	frame_time.Start();
}

// ---------------------------------------------
void j1App::FinishUpdate()
{

	if(want_to_save == true)
		SavegameNow();

	if(want_to_load == true)
		LoadGameNow();

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN) 
	{
		if (capped)
		{
			capped = false; 		
			frame_capstr = "Off";

		}
		else
		{
			capped = true; 
			framerate_cap = 30; 		
			frame_capstr = "On";
		}
		LOG("Framerate_cap: %i", framerate_cap);
	}


	

	//  Frame Rate Calculations
	

	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	float avg_fps = float(frame_count) / startup_time.ReadSec();
	float seconds_since_startup = startup_time.ReadSec();
	uint32 last_frame_ms = frame_time.Read();
	uint32 frames_on_last_update = prev_last_sec_frame_count;

	




	static char title[256];
	sprintf_s(title, 256, "FPS: %i, Av.FPS: %.2f Last Frame Ms: %02u / Frame Cap: %s Vsync: %s /Time since startup: %.3f Frame Count: %lu / Frame Cap: %i",
		frames_on_last_update, avg_fps, last_frame_ms, frame_capstr.GetString() , vsyncstr.GetString(), seconds_since_startup, frame_count, framerate_cap);
	App->win->SetTitle(title);

	float frame_rate_ms = 1 / (float)framerate_cap * 1000; 

	if (last_frame_ms < frame_rate_ms && frame_capstr == "On") 
	{
		BROFILER_CATEGORY("Delay for frame cap", Profiler::Color::MediumSlateBlue);

		SDL_Delay(frame_rate_ms - last_frame_ms);
	}

}

// Call modules before each loop iteration
bool j1App::PreUpdate()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;
	j1Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool j1App::DoUpdate()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;
	j1Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool j1App::PostUpdate()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	j1Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool j1App::CleanUp()
{
	PERF_START(ptimer);

	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	PERF_PEEK(ptimer);

	return ret;
}

// ---------------------------------------
int j1App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* j1App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* j1App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* j1App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
void j1App::LoadGame(const char* file)
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list
	want_to_load = true;
	//load_game.create("%s%s", fs->GetSaveDirectory(), file);
}

// ---------------------------------------
void j1App::SaveGame(const char* file) const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?

	want_to_save = true;
	//save_game.create(file);
}

// ---------------------------------------
void j1App::GetSaveGames(p2List<p2SString>& list_to_fill) const
{
	// need to add functionality to file_system module for this to work
}

float j1App::Getdt()
{
	return dt; 
}

bool j1App::LoadGameNow()
{
	bool ret = false;

	pugi::xml_document data;
	pugi::xml_node root;

	pugi::xml_parse_result result = data.load_file("save_game.xml");

	if (result != NULL)
	{
		LOG("Loading new Game State from %s...", load_game.GetString());

		root = data.child("game_state");

		p2List_item<j1Module*>* item = modules.start;
		ret = true;

		while (item != NULL && ret == true)
		{
			ret = item->data->Load(root.child(item->data->name.GetString()));
			item = item->next;
		}

		data.reset();
		if (ret == true)
			LOG("...finished loading");
		else
			LOG("...loading process interrupted with error on module %s", (item != NULL) ? item->data->name.GetString() : "unknown");
	}
	else
		LOG("Could not parse game state xml file %s. pugi error: %s", load_game.GetString(), result.description());

	want_to_load = false;
	return ret;
}

bool j1App::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", "save_game.xml");

	// xml object where we will store all data
	pugi::xml_document data;
	pugi::xml_node root;

	root = data.append_child("game_state");

	p2List_item<j1Module*>* item = modules.start;

	while (item != NULL && ret == true)
	{
		ret = item->data->Save(root.append_child(item->data->name.GetString()));
		item = item->next;
	}

	if (ret == true)
	{
		data.save_file("save_game.xml");
		LOG("... finished saving", );
	}
	else
		LOG("Save process halted from an error in module %s", (item != NULL) ? item->data->name.GetString() : "unknown");

	data.reset();
	want_to_save = false;
	return ret;
}