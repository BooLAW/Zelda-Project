#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "j1Module.h"
#include "j1Player.h"

#define MAX_ACTIVE_PARTICLES 100

enum PARTICLETYPE {
	p_arrow = 0,
	__LAST_PARTICLE
};

struct SDL_Texture;

struct Particle
{
	Collider* collider;
	Animation anim;
	fPoint position;
	fPoint speed;
	uint fx = 0;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect	 g_rect;

	Particle();
	Particle(const Particle& p);

	virtual void Start() {};
	virtual bool Update(float dt);
	virtual void CleanUp();
	virtual void Draw(float dt) {}; 
};

class ModuleParticles : public j1Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	Particle* CreateParticle(uint p_type);
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay = 0);
	void DestroyParticles();
	void DestroyParticle(Particle& particle);

	void OnCollision(Collider*, Collider*);

private:
	uint last_particle = 0;

public:

	std::deque<Particle*> particles;
	j1Timer time;

};

struct Arrow : public Particle {
	void Start();
};

#endif // __MODULEPARTICLES_H__