#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "p2Log.h"
#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "PugiXml\src\pugixml.hpp"
#include "Brofiler\Brofiler.h"
//
// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1FileSystem;
class SceneManager;
class j1Map;
class j1PathFinding;
class j1Fonts;
class j1Gui;
class j1Collision;
class HUD;
class ParticleManager;
//class j1Console;			
class j1Player;
class EntityManager;
class ModuleParticles;
class DialogManager;
class Video;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	float GetDT() const;

	void LoadGame(const char* file);
	void SaveGame(const char* file) const;
	void GetSaveGames(std::list<p2SString>& list_to_fill) const;

	// Load an XML file
	void LoadXML(const char* path, pugi::xml_document& doc);
	void UnloadXML(pugi::xml_document& doc);

	void CapFps(float fps);
	void EndSDL();

	void OpenWebPage(char* url);
	bool IsPaused()const;
	void Pause();
	void UnPause();
private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;

	// Frame rate calculations uptade
	void FrameRateCalculations();
public:

	// Modules
	j1Window*			win = NULL;
	j1Input*			input = NULL;
	j1Render*			render = NULL;
	j1Textures*			tex = NULL;
	j1Audio*			audio = NULL;
	SceneManager*		scene_manager = NULL;
	j1FileSystem*		fs = NULL;
	j1Map*				map = NULL;
	j1PathFinding*		pathfinding = NULL;
	j1Fonts*			font = NULL;
	j1Gui*				gui = NULL;
	//j1Console*			console = NULL;
	j1Collision*			collisions = NULL;
	j1Player*			player = NULL;
	EntityManager*      entitymanager = NULL;
	ParticleManager*	particlemanager = NULL;
	HUD*				hud = NULL;
	ModuleParticles*	particle = NULL;
	DialogManager*       dialog = NULL;
	Video*				video = NULL;

	bool			    debug_mode = false;
	bool fullscreen = true;

	std::list<j1Module*>	modules;
private:

	bool				paused=false;
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	mutable bool		want_to_save = false;
	bool				want_to_load = false;
	p2SString			load_game;
	mutable p2SString	save_game;

	j1PerfTimer			ptimer;

public:
	uint64				frame_count = 0;

	bool				first_open = false;

private:
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float				dt = 0.0f;
	int					capped_ms = -1;

public:
	bool				debug = false;

};

extern j1App* App; 

#endif