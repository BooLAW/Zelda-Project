#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j1App.h"
#include "EntityManager.h"
#include "Entity.h"
#include "j1Collision.h"
#include "j1Player.h"

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
	virtual ~Enemy() {};


public:
	Enemy* CreateEnemy(ENEMYTYPE subtype);

	virtual bool Start();

	virtual void Spawn() {}

	void Update(float dt);

	virtual bool Move();

	virtual bool Attack() {
		return true;
	}

	virtual bool CleanUp() {
		if (HitBox != nullptr)
			delete HitBox;

		return true;
	}

	virtual void Draw() {
		App->render->Blit(Entity::GetTexture(), pos.x, pos.y, &animations[curr_dir].GetCurrentFrame());
	}

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

	SDL_Rect HitRect;
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
