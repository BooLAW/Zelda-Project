#ifndef _SCENE_
#define _SCENE_

#include "j1App.h"
#include "j1Render.h"
#include "PugiXml\src\pugixml.hpp"

#include "EntityManager.h"

#include <string>
#include <list>

class Item;
class Enemy;

class Scene
{
public:
	Scene() {};

	virtual ~Scene() {};

	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp();

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

protected:

	bool change_scene = false;

public:
	SDL_Rect camera_limit = App->render->camera;

	std::list<Enemy*> enemies;
	std::list<Item*> items;

};

#endif