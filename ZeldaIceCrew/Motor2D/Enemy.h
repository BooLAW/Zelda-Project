#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j1App.h"
#include "EntityManager.h"
#include "Entity.h"
#include "j1Collision.h"
#include "j1Player.h"

#define ENEMY_SPRITES_PER_SPD 0.05f
#define COLLIDER_OFFSET_Y 

class Entity;

enum ENEMYTYPE {
	BlueSoldier = 0,
	__LAST
};

class BSoldier;

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
	virtual ~Enemy() {
		CleanUp();
	};


public:

	virtual bool Start();

	virtual void Spawn() {}

	virtual void Update(float dt);

	virtual bool Move();

	virtual bool Attack();

	virtual bool CleanUp() {
		if (HitBox != nullptr)
			HitBox->to_delete = true;

		return true;
	}

	virtual void Draw();

public:
	ENEMYTYPE EnemyType;

	struct EnemyStats {
		uint Hp;
		uint Speed;
		uint Power;

		bool Flying = false;
	
	} stats;

	ENEMYTYPE subtype;
	bool DmgType[DAMAGETYPE::__LAST_DMGTYPE];
	AITYPE AIType;

	Collider* HitBox;

	SDL_Rect sprites[Direction::LastDir][MAX_SPRITE_FRAMES];
	Animation animations[Direction::LastDir];

	unsigned int curr_dir;

};

class BSoldier : public Enemy {
public:
	bool Start();

};

#endif // !__ENEMY_H__