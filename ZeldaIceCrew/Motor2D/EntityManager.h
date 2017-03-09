
#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_
#include "j1Module.h"
#include <deque>
#include "j1Timer.h"
#include "Point.h"
#include "j1Collision.h"

class j1Player;
struct SDL_Texture;
struct SDL_Rect;
enum ENTITYTYPE { player, item,bush };
class Entity;
class EntityManager :public j1Module {
public:
	EntityManager();
	~EntityManager();
	bool Update(float dt);
	Entity* CreateEntity(ENTITYTYPE type, SDL_Texture* _tex, SDL_Rect* _rect, iPoint _pos);
	void DestroyEntities();
	void OnCollision(Collider* c1, Collider* c2);
private:
	std::deque<Entity*> entities;
	j1Timer time;
	
};


class Entity {
public:
	Entity();
	Entity(ENTITYTYPE _t, SDL_Texture* _tex, SDL_Rect* _rect,iPoint _pos);
	virtual ~Entity();
	virtual void Update(float dt);
	virtual bool Draw();
public:
	struct {
		int x;
		int y;
	} pos;
	SDL_Texture* tex;
	SDL_Rect* rect;
	ENTITYTYPE type;

private:

};

class Item : public  Entity {
public:
	void Update(float dt);
};

class Bush : public  Entity {
public:
	Bush();
	Bush(ENTITYTYPE _t, SDL_Texture* _tex, SDL_Rect* _rect, iPoint _pos);
	void Update(float dt);
	void OnCollision(Collider* c1, Collider* c2);
public:
	bool slashed = false;
	bool is_coll;
	Collider* collider = nullptr;

};

#endif
