#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j1App.h"
#include "EntityManager.h"
#include "Entity.h"
#include "j1Collision.h"

#include "Item.h"

#define N_ITEMS 11

#define ENEMY_SPRITES_PER_SPD 0.05f
#define ENEMY_DIR_CHANGE_OFFSET 50

#define JUMP_WHEN_HIT 2

class Entity;

enum ENEMYTYPE {
	BlueSoldier = 0,
	RedSoldier,
	GreenSoldier,
	__LAST
};

class BSoldier;

class Enemy : public Entity {
protected:
	enum EnDirection {
		Up = 0,
		Down,
		Right,
		Left,
		LastDir
	};

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
	virtual void SetRewards();

	virtual void Spawn() {}

	virtual void Update(float dt);

	virtual bool Move();

	virtual bool Attack();

	virtual void Draw();

	virtual void Hit();
	virtual void Death();
	virtual void Reward();

	virtual void CleanUp() {
		if (tex != nullptr)
			App->tex->UnLoad(tex);

		if(HitBox != nullptr)
			HitBox->to_delete = true;

		path_to_follow.clear();

	}

public:
	ENEMYTYPE EnemyType;

	struct EnemyStats {
		int		Hp;
		float	Speed;
		uint	Power;

		bool Flying = false;
	
	} stats;

	ENEMYTYPE subtype;
	bool DmgType[__LAST_DMGTYPE];
	AITYPE AIType;

	Collider* HitBox;

	SDL_Rect sprites[EnDirection::LastDir][8];
	Animation animations[EnDirection::LastDir];

	unsigned int curr_dir;

	// pathfinding related
	std::list<iPoint> path_to_follow;

	bool hit = false;

	uint reward_pool[N_ITEMS];

};

class BSoldier : public Enemy {
public:
	bool Start();

};

class RSoldier : public Enemy {
public:
	bool Start();

};

class GSoldier : public Enemy {
public:
	bool Start();

};

#endif // !__ENEMY_H__
