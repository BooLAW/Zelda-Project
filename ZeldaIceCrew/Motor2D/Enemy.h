#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j1App.h"
#include "EntityManager.h"
#include "j1Collision.h"
#include "SceneManager.h"
#include "Entity.h"

#include "Item.h"

#define N_ITEMS 31

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
	t_hinox,  // ciclop
	t_rope,
	t_geldman, //sandman
	t_GBat,
	t_boss_ballandchain,
	t_freezor, //ghost
	t_beamos, // eye
	t_boss_agahnim,
	t_boss_agahnimclone,
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

	virtual void Draw(float dt);

	virtual void Hit(uint dir, uint dmg);
	virtual void Death();
	virtual void Reward();

	virtual fPoint CheckSpaceTo(float x, float y);

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

	bool hit = false;

	uint reward_pool[N_ITEMS];

};

class BSoldier : public Enemy {
public:
	bool Start();
	//void Draw(float dt);

	SDL_Rect b_sprites[LastDir][2];
	Animation b_anim[LastDir];

};

class RSoldier : public Enemy {
public:
	bool Start();
	SDL_Rect b_sprites[LastDir][2];
	Animation b_anim[LastDir];
};

class GSoldier : public Enemy {
public:
	bool Start();
	SDL_Rect b_sprites[LastDir][2];
	Animation b_anim[LastDir];
};

class BossChainBall : public Enemy {
public:
	bool Start();
	bool Attack();
	void SetRewards();

	void Draw(float dt);

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
	SDL_Rect b_sprites[LastDir][2];
	Animation b_anim[LastDir];
};

class BlueArcher : public Enemy {
	bool Start();
	void Update(float dt);

	enum ARCHERSTATE {
		moving = 0,
		shoot,
		last_archerstate
	}state = moving;

	void Draw(float dt);

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

	void Draw(float dt);

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
	void Draw(float dt);
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
	void Draw(float dt);
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

	uint shadow_count = 0;

	Animation appear_anim, disappear_anim, attack_anim;
	SDL_Rect appear_sprites[8], attack_sprites[2];
	j1Timer timer;
};

class GreyBat : public Enemy {
public:
	bool Start();
	SDL_Rect b_sprites[LastDir][2];
	Animation b_anim[LastDir];
};

class AgahnimClones;

class BossAgahnim : public Enemy {
public:
	bool Start();
	void SetReward();
	void Draw(float dt);
	void Update(float dt);

	void Death();

	uint ball_counter = 0;

	uint clones_ded = 0;

	bool goandback = true;
	bool updown = true;
	j1Timer updowntime;
	j1Timer move_timer;
	AgahnimClones* clones[2];

	uint n_deaths;

	enum AGAHNIMPHASE {
		phase_1,
		goto_phase_2,
		phase_2,
		goto_phase_3,
		phase_3,
		phase_4
	}phase = phase_1;
	enum AGAHNIMSTATE {
		idle = 0,
		attack_charge,
		light_attack_charge,
		attack,
		disappear,
		move_start,
		move,
		appear,
	}state = idle;

	Animation appear_a, disappear_a, ticking_a, move_a, idle_a, attack_c_a, light_a_c;
	SDL_Rect attack_sprites[3], light_a_sprites[2], ticking_sprites[2], disappear_sprites[6], idle_sprites[3];
	j1Timer timer;

	const float org_spd = 2.5;

};

class AgahnimClones : public Enemy {
	bool Start();
	void SetReward();
	void Draw(float dt);
	void Update(float dt);

	uint ball_counter = 0;

	enum AGAHNIMCLONESTATE {
		idle = 0,
		attack_charge,
		attack,
		disappear,
		move_start,
		move,
		appear,
	}state = idle;

public:
	enum AGAHNIMCLONEPHASE {
		phase_2 = 0,
		phase_3
	}phase = phase_2;

private:
	Animation appear_a, disappear_a, ticking_a, move_a, idle_a, attack_c_a;
	SDL_Rect attack_sprites[3], ticking_sprites[2], disappear_sprites[6], idle_sprites[3];
	j1Timer timer;

	const float org_spd = 2.5;

};

class Beamos : public Enemy {
public:
	bool Start();
	void Draw(float dt);
	void Update(float dt);

	SDL_Rect beamos_sprites[24];

	uint n_proj = 0;

	enum BEAMOSSTATE {
		search = 0,
		shooting
	}state = search;

	j1Timer timer;

};

class TrueBlueSoldier : public Enemy {
	bool Start();
	
};

#endif // !__ENEMY_H__
