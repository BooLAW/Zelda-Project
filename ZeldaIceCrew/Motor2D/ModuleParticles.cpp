
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
}

ModuleParticles::~ModuleParticles()
{}

bool ModuleParticles::Start()
{
	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	
	DestroyParticles();

	return true;
}

bool ModuleParticles::Update(float dt)
{
	for (uint i = 0; i < particles.size(); i++) {
		if (particles[i]->Update(dt) == false)
			DestroyParticle(*particles[i]);
	}
	return true;
}

Particle * ModuleParticles::CreateParticle(uint p_type)
{
	Particle* ret = nullptr;

	switch (p_type) {
	case p_arrow:
		//ret = new Particle();
		break;
	default:
		LOG("Unknown Particle Type");
		break;
	}

	if (ret != nullptr) {
		ret->Start();
		particles.push_back(ret);
	}

	return ret;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	if (collider_type != COLLIDER_NONE)
		p->collider = App->collisions->AddCollider({ (int)p->position.x, (int)p->position.y, p->g_rect.w, p->g_rect.h }, collider_type, this);

}

void ModuleParticles::DestroyParticles()
{
	for (uint i = 0; i < particles.size(); i++) {
		if (particles[i] != nullptr) {
			particles[i]->CleanUp();
			RELEASE(particles[i]);
		} 
	}
}

void ModuleParticles::DestroyParticle(Particle & particle)
{

	particle.CleanUp();
	
	std::deque<Particle*>::iterator aux = std::find(particles.begin(), particles.end(), &particle);
	
	particles.erase(aux);


}

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}


bool Particle::Update(float dt)
{
	bool ret = true;

	if(life > 0 || life == -1)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	collider->SetPos(position.x, position.y);

	LOG("Particles update end");
	return ret;
}

void Particle::CleanUp()
{
	if (graphics != nullptr)
		App->tex->UnLoad(graphics);
}


void ModuleParticles::OnCollision(Collider* c1, Collider* c2) {
	LOG("\nparticle col\n");

	
}

void Arrow::Start()
{

}
