#include <iostream> 
#include <sstream> 

#include "p2Defs.h"
#include "p2Log.h"
#include "Functions.h"
#include <time.h>

#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "SceneManager.h"
#include "j1FileSystem.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "j1App.h"
#include "j1Player.h"
#include "j1Collision.h"
#include "HUD.h"
#include "ModuleParticles.h"
#include "DialogueManager.h"
#include "Video.h"
#include "ParticleManager.h"
//#include "j1Console"
#include "EntityManager.h"

// Constructor
j1App::j1App(int argc, char* args[]) : argc(argc), args(args)
{
	PERF_START(ptimer);

	input = new j1Input();
	win = new j1Window();
	render = new j1Render();
	tex = new j1Textures();
	audio = new j1Audio();
	scene_manager = new SceneManager();
	fs = new j1FileSystem();
	map = new j1Map();
	pathfinding = new j1PathFinding();
	font = new j1Fonts();
	gui = new j1Gui();
	collisions = new j1Collision();
	//console = new j1Console();
	player = new j1Player();
	entitymanager = new EntityManager();
	hud = new HUD();
	particle = new ModuleParticles();
	dialog = new DialogManager();
	video = new Video();
	particlemanager = new ParticleManager();


	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(fs);
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(map);
	AddModule(pathfinding);
	AddModule(font);
	AddModule(gui);
	AddModule(scene_manager);
	AddModule(entitymanager);
	AddModule(particlemanager);
	AddModule(collisions);
	//AddModule(console);
	AddModule(particle);
	AddModule(player);
	AddModule(hud);
	AddModule(dialog);
	AddModule(video);
	

	// render last to swap buffer
	AddModule(render);

	fullscreen = true;
	PERF_PEEK(ptimer);
}

// Destructor
j1App::~j1App()
{
	// release modules
	for (std::list<j1Module*>::iterator item = modules.begin(); item != modules.end(); item++)
		RELEASE(*item);

	modules.clear();
}

void j1App::AddModule(j1Module* module)
{
	module->Init();
	modules.push_back(module);
}

// Called before render is available
bool j1App::Awake()
{
	PERF_START(ptimer);

	srand(time(NULL));

	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	bool ret = false;
		
	config = LoadConfig(config_file);

	if(config.empty() == false)
	{
		// self-config
		ret = true;
		app_config = config.child("app");
		title.create(app_config.child("title").child_value());
		organization.create(app_config.child("organization").child_value());

		int cap = app_config.attribute("framerate_cap").as_int(-1);

		CapFps(cap);
	}

	if (ret == true)
	{
		for (std::list<j1Module*>::iterator item = modules.begin(); item != modules.end(); item++)
			ret = (*item)->Awake(config.child((*item)->name.GetString()));

	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool j1App::Start()
{
	BROFILER_CATEGORY("AddModule", Profiler::Color::Gray)

	PERF_START(ptimer);
	bool ret = true;
	std::list<j1Module*>::iterator item;
	item = modules.begin();

	while(item != modules.end() && ret == true)
	{
		ret = (*item)->Start();
		item++;
	}
	startup_time.Start();

	//Create here the UI elements

	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration
bool j1App::Update()
{
	BROFILER_CATEGORY("Update", Profiler::Color::Orange)
	
	bool ret = true;
	PrepareUpdate();

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug_mode = !debug_mode;
	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node j1App::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;

	char* buf;
	int size = App->fs->Load("config.xml", &buf);
	pugi::xml_parse_result result = config_file.load_buffer(buf, size);
	RELEASE(buf);

	if(result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");

	return ret;
}

// ---------------------------------------------
void j1App::PrepareUpdate()
{
	BROFILER_CATEGORY("Preupdate", Profiler::Color::Brown)

	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	frame_time.Start();
}

// ---------------------------------------------
void j1App::FinishUpdate()
{
	BROFILER_CATEGORY("FinishUpdate", Profiler::Color::Magenta)

	if(want_to_save == true)
		SavegameNow();

	if(want_to_load == true)
		LoadGameNow();

	// Framerate calculations --

	if(last_sec_frame_time.Read() > 1000)
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
	sprintf_s(title, 256, "Av.FPS: %.2f Last Frame Ms: %u Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %lu ",
			  avg_fps, last_frame_ms, frames_on_last_update, dt, seconds_since_startup, frame_count);
	App->win->SetTitle(title);

	if(capped_ms > 0 && last_frame_ms < capped_ms)
	{
		j1PerfTimer t;
		SDL_Delay(capped_ms - last_frame_ms);
		LOG("We waited for %d milliseconds and got back in %f", capped_ms - last_frame_ms, t.ReadMs());
	}
	//!_Framerate calculations
}

// Call modules before each loop iteration
bool j1App::PreUpdate()
{
	bool ret = true;
	j1Module* pModule = NULL;

	for (std::list<j1Module*>::iterator item = modules.begin(); item != modules.end() && ret == true; item++)
	{
		pModule = (*item);

		if (pModule->active == false) {
			continue;
		}

		ret = (*item)->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool j1App::DoUpdate()
{
	bool ret = true;
	j1Module* pModule = NULL;

	for (std::list<j1Module*>::iterator item = modules.begin(); item != modules.end() && ret == true; item++)
	{
		pModule = (*item);

		if (pModule->active == false) {
			continue;
		}

		ret = (*item)->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool j1App::PostUpdate()
{
	bool ret = true;
	j1Module* pModule = NULL;

	for (std::list<j1Module*>::iterator item = modules.begin(); item != modules.end() && ret == true; item++)
	{
		pModule = (*item);

		if (pModule->active == false) {
			continue;
		}

		ret = (*item)->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool j1App::CleanUp()
{
	PERF_START(ptimer);
	bool ret = true;

	for (std::list<j1Module*>::reverse_iterator item = modules.rbegin(); item != modules.rend(); item++)
		ret = (*item)->CleanUp();


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
float j1App::GetDT() const
{
	return dt;
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
	want_to_load = true;
	load_game.create("%s%s", fs->GetSaveDirectory(), file);
}

// ---------------------------------------
void j1App::SaveGame(const char* file) const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?
	want_to_save = true;
	save_game.create("%s%s", fs->GetSaveDirectory(), file);
}

// ---------------------------------------
void j1App::GetSaveGames(std::list<p2SString>& list_to_fill) const
{
	// need to add functionality to file_system module for this to work
}
void j1App::LoadXML(const char * path, pugi::xml_document & doc)
{
	char* buf = NULL;
	int size = App->fs->Load(path, &buf);
	pugi::xml_parse_result result = doc.load_buffer(buf, size);

	if (buf == NULL)
		LOG("Error loading '%s', probably wrong XML file name", path);
	else
		LOG("Succes loading '%s'", path);

	RELEASE(buf);
}

void j1App::UnloadXML(pugi::xml_document & doc)
{
	doc.reset();
}
void j1App::CapFps(float fps)
{
	if (fps > 0)
		capped_ms = (1000 / fps);
}
bool j1App::LoadGameNow()
{
	bool ret = false;

	char* buffer;
	uint size = fs->Load(load_game.GetString(), &buffer);

	if(size > 0)
	{
		pugi::xml_document data;
		pugi::xml_node root;

		pugi::xml_parse_result result = data.load_buffer(buffer, size);
		RELEASE(buffer);

		if(result != NULL)
		{
			LOG("Loading new Game State from %s...", load_game.GetString());

			root = data.child("game_state");

			std::list<j1Module*>::iterator item = modules.begin();
			ret = true;

			while(item != modules.end() && ret == true)
			{
				ret = (*item)->Load(root.child((*item)->name.GetString()));
				item++;
			}

			data.reset();
			if(ret == true)
				LOG("...finished loading");
			else
				LOG("...loading process interrupted with error on module %s",(*item)->name.GetString());
		}
		else
			LOG("Could not parse game state xml file %s. pugi error: %s", load_game.GetString(), result.description());
	}
	else
		LOG("Could not load game state xml file %s", load_game.GetString());

	want_to_load = false;
	return ret;
}

bool j1App::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", save_game.GetString());

	// xml object were we will store all data
	pugi::xml_document data;
	pugi::xml_node root;
	
	root = data.append_child("game_state");

	std::list<j1Module*>::const_iterator item = modules.begin();

	while(item != modules.end() && ret == true)
	{
		ret = (*item)->Save(root.append_child((*item)->name.GetString()));
		item++;
	}

	if(ret == true)
	{
		std::stringstream stream;
		data.save(stream);
		data.save_file(save_game.GetString());

		// we are done, so write data to disk
		fs->Save(save_game.GetString(), stream.str().c_str(), stream.str().length());
		LOG("... finished saving %s", save_game.GetString());
	}
	else
		LOG("Save process halted from an error in module %s", (*item)->name.GetString());

	data.reset();
	want_to_save = false;
	return ret;
}
void j1App::OpenWebPage(char * url)
{
	ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWMAXIMIZED);
}

bool j1App::IsPaused() const
{
	return paused;
}

void j1App::Pause()
{
	paused = true;
}

void j1App::UnPause()
{
	paused = false;
}

