#ifndef _SCENE_
#define _SCENE_

#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "PugiXml\src\pugixml.hpp"

#include "Doorway.h"
#include "EntityManager.h"

#include "Room.h"

#include <string>
//#include <list>

#define ROOM_CHANGE_X 175.0f
#define ROOM_CHANGE_Y 175.0f

enum scene_id {
	null,
	village,
	dungeon,
	intro
};
class Item;
class Enemy;
class Block;
class Doorway;

class Room;

class Scene
{
public:
	Scene() {};

	virtual ~Scene() {};

	virtual bool Start() { return stdStart(); };
	virtual bool stdStart();
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt);
	virtual bool stdUpdate(float dt);
	virtual bool PostUpdate() {
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			return false;
		return true;
	};
	virtual bool CleanUp();
	virtual bool stdCleanUp();
	virtual void Clear();

	Room* GetRoom(int x, int y);

	bool IsInside(SDL_Rect r1, SDL_Rect r2) {
		if (r1.x > r2.x && r1.x < r2.x + r2.w)
			if (r1.y > r2.y && r1.y < r2.y + r2.h)
				return true;

		return false;
	}

	Room* GetCurrentRoom();

	virtual void DestroyItem(Item* ent);
	virtual void DestroyEnemy(Enemy* ent);
	virtual void DestroyBlock(Block* ent);
	virtual void DestroyDoorway(Doorway* ent);

	virtual void DestroyRoom(Room* ent);

	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}

	Item* AddItem(uint subtype, int coord_x, int coord_y, float x, float y);
	Block* AddBlock(uint subtype, int coord_x, int coord_y, float x, float y);
	Doorway* AddSceneDoorway(Scene* target, int coord_x, int coord_y, uint dir, float x, float y);
	Doorway* AddDungeonDoorway(uint dir, int coord_x, int coord_y);
	Doorway* AddCamDoorway(float target_x, float target_y, int coord_x, int coord_y, uint dir, float x, float y);
	Enemy* AddEnemy(int subtype, int coord_x, int coord_y, float x, float y);
	Room* AddRoom(int coord_x, int coord_y, int w = 1024, int h = 576);
  
	bool Scene::Load_new_map(int id);
	pugi::xml_node LoadConfig(pugi::xml_document& config_file) const;
	
	virtual bool IsEnemy(Enemy* en);

	virtual void ShowCoords();

	virtual void AllEnemyActive(bool flag);

protected:

	bool change_scene = false;

	

public:
	bool follow_cam = true;
	fPoint pl_start_pos;
	std::list<Room*> rooms;

	char* music_path;
  
	scene_id curr_id;// enum to use in the load_new_map scene function

};

#endif