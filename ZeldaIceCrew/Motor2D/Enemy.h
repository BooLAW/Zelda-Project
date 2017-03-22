#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j1App.h"
#include "EntityManager.h"
#include "Entity.h"
#include "j1Collision.h"

class Entity;

enum ENEMYTYPE {
	BSoldier = 0,
	__LAST
};

class Enemy : public Entity {
protected:
	enum DAMAGETYPE {
		melee = 0,
		projectile,
		__LAST_DMGTYPE
	};

	enum AITYPE {
		path = 0,
		chase,
		distance,
		no_move,
		__LAST_AITYPE
	};

public:
	Enemy() {};
	Enemy(uint subtype);
	virtual ~Enemy() {};


public:
	Enemy* CreateEnemy(ENEMYTYPE type);

	virtual bool Start();

	virtual void Spawn() {}

	virtual bool Update();

	virtual bool Move();

	virtual bool Attack();

	virtual bool CleanUp() {
		return true;
	}

public:
	ENEMYTYPE EnemyType;

	struct EnemyStats {
		uint Hp;
		uint Speed;
		uint Power;

		bool Flying = false;
	
	} stats;

	bool DmgType[DAMAGETYPE::__LAST_DMGTYPE];
	AITYPE AIType;

	Collider* HitBox;

};

#endif // !__ENEMY_H__
