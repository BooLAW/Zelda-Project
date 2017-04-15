#ifndef _SCENE_
#define _SCENE_

#include "j1App.h"
#include "j1Render.h"
#include "PugiXml\src\pugixml.hpp"

#include "Doorway.h"
#include "EntityManager.h"

#include <string>
#include <list>

#define ROOM_W 1024
#define ROOM_H 576

#define ROOM_CHANGE_X 175.0f
#define ROOM_CHANGE_Y 175.0f

class Item;
class Enemy;
class Block;
class Doorway;

class Scene
{
public:
	Scene() {};

	virtual ~Scene() {};

	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual void DoorUpdate(float dt);
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp();

	bool IsInside(SDL_Rect r1, SDL_Rect r2) {
		if (r1.x + r1.w > r2.x && r1.x < r2.x + r2.w)
			if (r1.y + r1.h > r2.y && r1.y < r2.y + r2.h)
				return true;

		return false;
	}

	virtual void DestroyItem(Item* ent) {
		if (ent != nullptr) {
			for (std::list<Item*>::iterator it = items.begin(); it != items.end(); it++) {
				if(it._Ptr->_Myval == ent)
					items.erase(it);
			}
		}
	};
	virtual void DestroyEnemy(Enemy* ent) {
		if (ent != nullptr) {
			for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
				if (it._Ptr->_Myval == ent)
					enemies.erase(it);
			}
		}
	};

	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}

	
	Item* AddItem(uint subtype, float x, float y);
	Block* AddBlock(uint subtype, float x, float y);
	Doorway* AddDoorway(uint subtype, uint dir, int x, int y);
	Enemy* AddEnemy(int subtype, float x, float y);
	virtual bool IsEnemy(Enemy* en);

protected:

	bool change_scene = false;


public:
	SDL_Rect camera_limit = App->render->camera;

	bool follow_cam = true;

	std::list<Enemy*> enemies;
	std::list<Item*> items;
	std::list<Block*> blocks;
	std::list<Doorway*> doorways;


};

#endif