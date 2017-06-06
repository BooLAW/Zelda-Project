#pragma once
#ifndef __DUNGEON_SCENE_H__
#define __DUNGEON_SCENE_H__

#include "j1Module.h"
#include "EntityManager.h"
#include <vector>
#include "Scene.h"

struct SDL_Texture;
//UI forward declarations
class Image;
class Label;
class Text_Box;
class Button;
class Window;
class Selector;
class Windowed_Image;

class DungeonScene : public Scene
{
public:

	DungeonScene();

	// Destructor
	virtual ~DungeonScene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	//bool CleanUp();
public:
	
	uint round;
	uint change_round = 0;

private:

	uint round_counter = 0;

	j1Timer wave_time;
	j1Timer starting_time;

	bool starting;

	j1Timer round_timer;

	uint to_round = 0;


	iPoint spawn1;
	iPoint spawn2;
	iPoint spawn3;
	iPoint spawn4;

	SDL_Texture* debug_tex;
	bool ESC = false;
	Window* window;
	Label* win_title;
	Npc* test;
	Enemy* en;
	
	
};

#endif //__DUNGEON_SCENE_H__

