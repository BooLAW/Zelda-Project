#ifndef __ROOM_H__
#define __ROOM_H__

#include "j1Player.h"
#include "Scene.h"
#include "NPC.h"

class Item;
class Enemy;
class Block;
class Doorway;
class Npc;
enum NPC_TYPE;
class Scene;
class Npc;
#define ROOM_W 1024
#define ROOM_H 576

class Room {
public:
	virtual void Start();

	void Update(float dt);
	void CleanUp();

	bool isInside(SDL_Rect r);

	bool NoEnemies();

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
	Doorway* AddDungeonDoorway(uint dir);
	Doorway* AddSceneDoorway(Scene* target, uint dir, float x, float y);
	Doorway* AddCamDoorway(float target_x, float target_y, uint dir, float x, float y);
	Npc* AddNpc(NPC_TYPE type, float x, float y,int id);

	void EnemyActive(bool flag);

	Scene* GetParentScene();
	void SetParentScene(Scene* scene);

public:
	bool active = false;

	iPoint coords;
	SDL_Rect room_rect;

	SDL_Rect cam_boundaries;
	bool boss_room = false;
	std::list<Enemy*> enemies;
	std::list<Item*> items;
	std::list<Block*> blocks;
	std::list<Doorway*> doorways;
	std::list<Npc*> npcs;

protected:
	Scene* parent;

};;

#endif //!__ROOM_H__