#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "EntityManager.h"
#include "Entity.h"

class Entity;

enum ENEMYTYPE {
	BSoldier = 0,
	__LAST
};

class Enemy : public Entity {
public:
	Enemy() {};
	Enemy(uint subtype);
	virtual ~Enemy() {};



public:


};

#endif // !__ENEMY_H__
