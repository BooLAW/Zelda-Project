
#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_
#include "j1Module.h"
#include <deque>
#include "j1Timer.h"
#include "Point.h"
#include "j1Collision.h"
#include "j1Render.h"

#include "j1Player.h"

#include "Log.h"

#include "Entity.h"
#include "NPC.h"

#include "Bomb.h"
#include "Item.h"
#include "Block.h"
#include "Enemy.h"
#include "Doorway.h"
#include <map>
#include <deque>



class Entity;
class j1Player;
struct SDL_Texture;
struct SDL_Rect;

class Doorway;

class Bomb;
class Item;
class Enemy;
class Block;
class Drop;
class Npc;

class EntityManager : public j1Module {
public:
	EntityManager();
	~EntityManager();
	
	bool CleanUp();
	bool Start();
	bool Awake(pugi::xml_node & config);
	bool PreUpdate();
	bool Update(float dt);
	void PushEntity(Entity* ent);
	void DestroyEntities();
	void DestroyEnity(Entity* ent);
	
	std::deque<Entity*>* GetEntities() { return &entities; };

	void OnCollision(Collider* c1, Collider* c2);


	uint fromEntoPlDir(uint EnDir);


public:
	Enemy* CreateEnemy(uint subtype);
	Item* CreateItem(uint subtype);
	Block* CreateBlock(uint subtype);
	Npc * CreateNPC(NPC_TYPE type, float x, float y, int id);
private:
	
	std::deque<Entity*> entities;
	std::map<ENTITYTYPE, std::string> dir;
	j1Timer time;
	SDL_Texture* npc_tex;
	
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
