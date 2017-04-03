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

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();
public:
	bool down = false;
	bool up = false;
	bool right = false;
	bool left = false;
private:
	Collider* boss_door;

	bool boss_music = false;

	j1Timer boss_minions_spawn_time;
	bool chain_boss_defeated = false;

	Enemy* ChainBoss = nullptr;

	SDL_Texture* debug_tex;
	bool ESC = false;
	Window* window;
	Label* win_title;
};

#endif //__DUNGEON_SCENE_H__

