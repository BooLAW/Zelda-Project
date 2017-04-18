#ifndef __ROOM_H__
#define __ROOM_H__

#include "j1App.h"
#include "j1Player.h"
#include "Scene.h"

class Item;
class Enemy;
class Block;
class Doorway;

class Room {
public:
	virtual void Start() {
		room_rect.w = ROOM_W;
		room_rect.h = ROOM_H;
	};

	void Update(float dt);
	void CleanUp();

	bool isInside(SDL_Rect r) {
		if (r.x > room_rect.x && r.x < room_rect.x + room_rect.w)
			if (r.y > room_rect.y && r.y < room_rect.y + room_rect.h)
				return true;

		return false;
	};

	bool PlayerInside() {
		return isInside(App->player->mov_coll->rect);
	};

	bool findEnemy(Enemy* en) {
		bool ret = false;

		if (en != nullptr) {
			for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
				if ((*it) == en)
					ret = true;
			}
		}

		return ret;
	}

	Item* AddItem(uint subtype, float x, float y);
	Enemy* AddEnemy(uint subtype, float x, float y);
	Block* AddBlock(uint subtype, float x, float y);
	Doorway* AddDoorway(uint subtype, uint dir, float x, float y);


public:
	bool active = false;

	iPoint coords;
	SDL_Rect room_rect;

	SDL_Rect cam_boundaries;

	std::list<Enemy*> enemies;
	std::list<Item*> items;
	std::list<Block*> blocks;
	std::list<Doorway*> doorways;

};

#endif //!__ROOM_H__