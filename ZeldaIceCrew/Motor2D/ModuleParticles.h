#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "j1Module.h"
#include "j1Player.h"

#define MAX_FRAMES_PARTICLES 16
#define ARROW_SPEED 6.0f

#define MAX_PARTICLES 100

#define SHADOW_SPD 2
#define BOUNCEB_SPD 3
#define STD_PROJ_SPD 3

enum PARTICLETYPE {
	p_arrow = 0,
	p_enarrow,
	p_shadow,
	p_bounceback,
	p_std,
	p_agahnim_ball,
	p_agahnim_lightning,
	p_agahnim_4balls,
	p_block_bush,
	p_block_pot,
	p_block_skull,
	__LAST_PARTICLE
};

struct SDL_Texture;

struct Particle
{
	Collider* collider;
	SDL_Rect HitBox;
	Animation anim[Direction::LastDir];
	Direction curr_dir;
	fPoint position;
	fPoint speed;
	uint fx = 0;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	uint damage = 0;

	SDL_Texture* graphics = nullptr;
	SDL_Rect	 g_rect[Direction::LastDir][MAX_FRAMES_PARTICLES];

	Particle();

	virtual void Start() {};
	virtual bool Update(float dt);
	virtual bool stdUpdate(float dt);
	virtual void CleanUp();
	virtual void Draw(float dt);

	virtual int CheckSpace(float new_x, float new_y);

};

class ModuleParticles : public j1Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	Particle* CreateParticle(uint p_type, int x, int y, uint dir);
	void AddParticle(Particle* particle, COLLIDER_TYPE collider_type, Uint32 life, Uint32 dmg = 0, Uint32 delay = 0);
	void DestroyParticles();
	void DestroyParticle(Particle* particle);

	void OnCollision(Collider*, Collider*);

private:
	uint last_particle = 0;

public:

	std::deque<Particle*> particles;
	j1Timer time;

};

struct Arrow : public Particle {
	
	bool hit = false;

	void Start();
	bool Update(float dt);

};

struct Enemy_Arrow : public Particle {
	bool hit = false;

	void Start();
	bool Update(float dt);
};

struct Shadow_Projectile : public Particle {
	bool hit = false;

	uint shot_dir;

	void Start();
	bool Update(float dt);
};

struct BounceBack : public Particle {
	bool hit = false;
	void Start();
	bool Update(float dt);

	fPoint target;

	enum BOUNCESTATE {
		go = 0,
		back
	}state = go;
};

struct StdEnemyProjectile : public Particle {
	bool hit = false;
	void Start();
	bool Update(float dt);

	fPoint target;

};

struct AgahnimBall : public Particle {
	bool hit = false;
	void Start();
	bool Update(float dt);

	fPoint target;

	struct MiniAgBalls {
		SDL_Rect rect;
		fPoint pos;
	}miniagballs[2];

	enum BOUNCESTATE {
		go = 0,
		back
	}state = go;
};

struct AgahnimBasic : public Particle {
	bool hit = false;
	void Start();
	bool Update(float dt);   
	fPoint target;
};

struct Block_Bush : public Particle {
	bool hit = false;

	void Start();
	bool Update(float dt);
};

struct Block_Pot : public Particle {
	bool hit = false;

	void Start();
	bool Update(float dt);
};

struct Block_Skull : public Particle {
	bool hit = false;

	void Start();
	bool Update(float dt);
};

#endif // __MODULEPARTICLES_H__