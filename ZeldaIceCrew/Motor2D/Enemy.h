#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j1App.h"
#include "EntityManager.h"
#include "j1Collision.h"
#include "SceneManager.h"
#include "Entity.h"

#include "Item.h"

#define N_ITEMS 15

#define ENEMY_SPRITES_PER_SPD 0.05f
#define ENEMY_DIR_CHANGE_OFFSET 50

#define HIT_INM_TIME 2000

#define ENEMY_STD_OFFSET_Y 24

#define ROPE_JMP 5

class Entity;

enum ENEMYTYPE {
	t_bluesoldier = 0,
	t_bluearcher,
	t_redsoldier,
	t_greensoldier,
	t_hinox,
	t_rope,
	t_geldman,
	t_freezor,
	t_GBat,
	t_beamos,
	t_boss_ballandchain,
	t_boss_agahnim,
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
		none,
		__LAST_DMGTYPE
	};

	enum AITYPE {
		path = 0,
		chase,
		distance,
		special,
		no_move,
		__LAST_AITYPE
	};

public:
	Enemy() {};
	Enemy(uint subtype);
	virtual ~Enemy() {
		//CleanUp();
	};


public:

	virtual bool Start();
	virtual void SetRewards();

	virtual void Spawn() {}

	virtual uint GetPlayerDirection();

	virtual void stdUpdate(float dt);
	virtual void Update(float dt) { stdUpdate(dt); };

	virtual bool Move();

	virtual bool Attack();
	virtual void HitPlayer();
	virtual void HitPlayer(uint dmg);

	virtual void SetAnimation(SDL_Rect spr[LastDir][2]);

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

	iPoint target;

	ENEMYTYPE subtype;
	bool DmgType[__LAST_DMGTYPE];
	AITYPE AIType;

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
};

class BlueArcher : public Enemy {
	bool Start();
	void Update(float dt);

	enum ARCHERSTATE {
		moving = 0,
		shoot,
		last_archerstate
	}state = moving;

	void Draw();

	Animation shoot_anim;

	SDL_Rect BArcher_Shoot[EnDirection::LastDir][8];

	j1Timer react_time;
	j1Timer shoot_time;

	uint range = 5;
	uint range_limit = 2;

	bool first_shot = true;

};

class Rope : public Enemy {
	bool Start();

	void Update(float dt);

	void Draw();

	enum ROPESTATE{
		moving = 0,
		no_move,
		last_ropestate
	}state = no_move;

	fPoint aux_pos;

	Animation nm_anim;

	SDL_Rect RopeSprites_m[EnDirection::LastDir][2];
	SDL_Rect RopeSprites_nm[EnDirection::LastDir][2];

	j1Timer walk_timer;

};

class Geldman : public Enemy {
	bool Start();
	void Draw();
	void Update(float dt);

	const int time_moving = 3500;

	SDL_Rect appear_sprites[8], move_sprites[8];
	Animation appear_anim, disappear_anim, move_anim;

	enum GELDMANSTATE {
		appear = 0,
		appear_start,
		disappear_start,
		disappear,
		move
	}state = appear_start;

	j1Timer move_time;

};

class Freezor : public Enemy {
	bool Start();
	void Draw();
	void Update(float dt);
	const int time_attack = 3500;

	j1Timer attack_timer;

	enum FREEZORSTATE {
		appear = 0,
		appear_start,
		attack,
		disappear,
		disappear_start
	}state = appear_start;

	Animation appear_anim, disappear_anim, attack_anim;
	SDL_Rect appear_sprites[8], attack_sprites[2];
	j1Timer timer;
};

class GreyBat : public Enemy {
public:
	bool Start();
};

class BossAgahnim : public Enemy {
public:
	bool Start();
	void SetReward();
	void Draw();
	void Update(float dt);
	const int time_attack = 3500;//CHANGE

	j1Timer attack_timer;
	enum AGAHNIMSTATE {
		appear = 0,
		appear_start,
		attack,
		hit,
		disappear,
		disappear_start
	}state = appear_start;

	Animation appear_anim, disappear_anim, attack_anim, hit_anim;
	SDL_Rect appear_sprites[8], attack_sprites[2], disappear_sprites[6];
	j1Timer timer;
};

class Beamos : public Enemy {
public:
	bool Start();
	void Draw();
	void Update(float dt);

	SDL_Rect beamos_sprites[24];

	enum BEAMOSSTATE {
		search = 0,
		shooting
	}state = search;

	j1Timer timer;

};

#endif // !__ENEMY_H__
