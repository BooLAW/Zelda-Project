#ifndef __ROOM_H__
#define __ROOM_H__

#include "j1Player.h"
#include "Scene.h"

class Item;
class Enemy;
class Block;
class Doorway;

class Scene;

#define ROOM_W 1024
#define ROOM_H 576

class Room {
public:
	virtual void Start();

	void Update(float dt);
	void CleanUp();

	bool isInside(SDL_Rect r);

	bool PlayerInside();

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

	void EnemyActive(bool flag);

	Scene* GetParentScene();
	void SetParentScene(Scene* scene);

public:
	bool active = false;

	iPoint coords;
	SDL_Rect room_rect;

	SDL_Rect cam_boundaries;

	std::list<Enemy*> enemies;
	std::list<Item*> items;
	std::list<Block*> blocks;
	std::list<Doorway*> doorways;

protected:
	Scene* parent;

};;

#endif //!__ROOM_H__