#pragma once
#ifndef __ARENA_H__
#define __ARENA_H__

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

class Arena : public Scene
{
public:

	Arena();

	// Destructor
	virtual ~Arena();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

private:

	//bool boss_music = false;

	j1Timer wave_time;
	SDL_Texture* debug_tex;
	bool ESC = false;
	Window* window;
	Label* win_title;
	Npc* test;
	Enemy* en;

};

#endif //__DUNGEON_SCENE_H__

#pragma once
