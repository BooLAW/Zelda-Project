
#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_
#include "j1Module.h"
#include <deque>
#include "j1Timer.h"
#include "Point.h"
#include "j1Collision.h"
#include "j1Render.h"

#include "Log.h"

#include "Entity.h"

#include "Bomb.h"
#include "Item.h"
#include "Block.h"
#include "Drop.h"
#include "Enemy.h"

class Entity;
class j1Player;
struct SDL_Texture;
struct SDL_Rect;

class Bomb;
class Item;
class Enemy;
class Block;
class Drop;

class EntityManager : public j1Module {
public:
	EntityManager();
	~EntityManager();
	
	bool CleanUp() {
		DestroyEntities();
		return true;
	}

	bool Update(float dt);
	void PushEntity(Entity* ent);
	void DestroyEntities();
	void DestroyEnity(Entity* ent);
	
	void OnCollision(Collider* c1, Collider* c2);

public:
	Enemy* CreateEnemy(uint subtype);

private:
	std::deque<Entity*> entities;
	j1Timer time;
	
};


//class Bush : public  Entity {
//public:
//	Bush();
//	Bush(ENTITYTYPE _t, SDL_Texture* _tex, SDL_Rect _rect, iPoint _pos);
//	void Update(float dt);
//	void OnCollision(Collider* c1, Collider* c2);
//public:
//	bool slashed = false;
//	bool is_coll;
//	Collider* collider = nullptr;
//
//};

#endif
