#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j1App.h"
#include "EntityManager.h"
#include "Entity.h"
#include "j1Collision.h"
#include "SceneManager.h"

#include "Item.h"

#define N_ITEMS 15

#define ENEMY_SPRITES_PER_SPD 0.05f
#define ENEMY_DIR_CHANGE_OFFSET 50

#define HIT_INM_TIME 2000

class Entity;

enum ENEMYTYPE {
	t_bluesoldier = 0,
	t_redsoldier,
	t_greensoldier,
	t_hinox,
	t_boss_ballandchain,
	__LAST_ENEMYTYPE
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
	virtual void HitPlayer();
	virtual void HitPlayer(uint dmg);

	virtual void Draw();

	virtual void Hit(uint dir, uint dmg);
	virtual void Death();
	virtual void Reward();

	void SortRewardProbs() {
		uint total = 0;

		for (int i = 0; i < N_ITEMS; i++) {
			total += reward_pool[i];
		}

		if (total != 100) {
			for (int i = 0; i < N_ITEMS; i++) {
				reward_pool[i] = (reward_pool[i] * 100) / total;
			}
		}

	}

	virtual void CleanUp();

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

	uint jump_hit = 48;

	// pathfinding related
	std::list<iPoint> path_to_follow;

	uint hit_fx;
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

class BossChainBall : public Enemy {
public:
	bool Start();
	bool Attack();
	void SetRewards();

	void Draw();

	void CleanUp();

public:
	j1Timer ball_timer;

	enum {
		no_ball_start = -2,
		no_ball = -1,
		circle_ball_start,
		circle_ball,
		attack_ball_start,
		attack_ball,
		__LAST_BALL_STATE
	}state;

	SDL_Rect ball_rect[__LAST_BALL_STATE][EnDirection::LastDir][30];
	Animation ball_anim[__LAST_BALL_STATE][EnDirection::LastDir];

	uint ball_r;
	fPoint ball_centre;
	float ball_x;
	float ball_y;
	float ball_p;
	float ball_speed;
	uint round_counter;
	Collider* ball_collider;
};

class Hinox : public Enemy {
public:
	bool Start();
	void SetRewards();

	bool Attack();
};

#endif // !__ENEMY_H__
