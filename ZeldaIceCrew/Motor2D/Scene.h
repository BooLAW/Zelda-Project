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

	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) {
		return stdUpdate(dt);
	}
	virtual bool stdUpdate(float dt);
	virtual bool PostUpdate() {
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			return false;
		return true;
	};
	virtual bool CleanUp();
	virtual bool stdCleanUp();

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
	Doorway* AddDoorway(uint subtype, int coord_x, int coord_y, uint dir, int x, int y);
	Doorway* AddDungeonDoorway(uint dir, int coord_x, int coord_y);
	Enemy* AddEnemy(int subtype, int coord_x, int coord_y, float x, float y);
	Room* AddRoom(int coord_x, int coord_y, int w = 1024, int h = 576);
	virtual bool IsEnemy(Enemy* en);

	virtual void AllEnemyActive(bool flag);

protected:

	bool change_scene = false;


public:
	bool follow_cam = true;
	std::list<Room*> rooms;

	char* music_path;

};

#endif