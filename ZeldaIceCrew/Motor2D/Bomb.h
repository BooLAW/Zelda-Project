#ifndef __BOMB_H__
#define __BOMB_H__

#include "EntityManager.h"
#include "Entity.h"

class Entity;

class Bomb : public Entity {
public:
	Bomb() {};
	virtual ~Bomb() {};


public:
	Bomb* CreateBomb();

};

#endif // !__BOMB_H__
