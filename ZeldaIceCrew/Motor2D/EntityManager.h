
#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_
#include "j1Module.h"
#include "p2DynArray.h"
#include "j1Timer.h"

enum ENTITYTYPE { player, item };
class Entity;
class EntityManager :public j1Module {
public:
	EntityManager();
	~EntityManager();
	bool Update(float dt);
	Entity* CreateEntity(ENTITYTYPE type);
	void DestroyEntities();
private:
	p2DynArray<Entity*> entities;
	j1Timer time;

};


class Entity {
public:
	Entity();
	Entity(ENTITYTYPE t);
	~Entity();
	ENTITYTYPE type;
	virtual void Update(float dt);

private:

};

class Player : public  Entity {
public:
	void Update(float dt);
};

class Item : public  Entity {
public:
	void Update(float dt);
};

#endif
