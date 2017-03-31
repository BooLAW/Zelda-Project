
#include "ModuleParticles.h"
#include "j1Collision.h"
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
			DestroyParticle(particles[i]);
	}
	return true;
}

Particle * ModuleParticles::CreateParticle(uint p_type, int x, int y, uint dir)
{
	
	Particle* ret = nullptr;
	
	if (particles.size() < MAX_PARTICLES) {

		switch (p_type) {
		case p_arrow:
			ret = new Arrow();
			break;
		default:
			LOG("Unknown Particle Type");
			break;
		}

		if (ret != nullptr) {
			ret->position.x = x;
			ret->position.y = y;
			ret->curr_dir = (Direction)dir;
			ret->Start();
			particles.push_back(ret);
		}
	}
	else {
		LOG("NO MORE PARTICLE SPACE");
	}

	return ret;
}

void ModuleParticles::AddParticle(Particle* particle, COLLIDER_TYPE collider_type, Uint32 life, Uint32 delay)
{
	particle->born = SDL_GetTicks() + delay;
	particle->life = life;
	if (collider_type != COLLIDER_NONE)
		particle->collider = App->collisions->AddCollider({ (int)particle->position.x, (int)particle->position.y, particle->HitBox.w, particle->HitBox.h }, collider_type, this);

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

void ModuleParticles::DestroyParticle(Particle* particle)
{
	if (particle != nullptr) {
		particle->CleanUp();
		std::deque<Particle*>::iterator aux = std::find(particles.begin(), particles.end(), particle);
		particles.erase(aux);
	}
}

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}


bool Particle::Update(float dt)
{
	return stdUpdate(dt);
}

bool Particle::stdUpdate(float dt)
{
	bool ret = true;


	if(life > 0 || life == -1)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim[curr_dir].Finished())
			ret = false;


	position.x += speed.x;
	position.y += speed.y;

	collider->SetPos(position.x, position.y);
	
	App->render->Blit(graphics, position.x, position.y, &anim[curr_dir].GetCurrentFrame());

	return ret;
}

void Particle::CleanUp()
{
	if (graphics != nullptr)
		App->tex->UnLoad(graphics);

	collider->to_delete = true;

}


void ModuleParticles::OnCollision(Collider* c1, Collider* c2) {
	LOG("\nparticle col\n");
	
}

void Arrow::Start()
{
	graphics = App->tex->Load("Sprites/Particles/Particles.png");
	g_rect[Up] = { 2, 2, 34, 34 };
	g_rect[Down] = { 38, 2, 34, 34 };
	g_rect[Right] = { 74, 2, 34, 34 };
	g_rect[Left] = { 110, 2, 34, 34 };
	
	switch (curr_dir) {
	case Up:
		speed = { 0, -ARROW_SPEED };
		break;
	case Down:
		speed = { 0, ARROW_SPEED };
		break;
	case Left:
		speed = { -ARROW_SPEED, 0 };
		break;
	case Right:
		speed = { ARROW_SPEED, 0 };
		break;
	}

	for (int k = 0; k < LastDir; k++) {
		anim[k].PushBack(g_rect[k]);
	}

	HitBox = { (int)position.x, (int)position.y, g_rect[0].w, g_rect[0].h };
	App->particle->AddParticle(this, COLLIDER_ARROW, 1500, NULL);

}

bool Arrow::Update(float dt)
{

	HitBox = { (int)position.x, (int)position.y, g_rect[curr_dir].w, g_rect[curr_dir].h };

	std::list<Enemy*>*ents = &App->scene_manager->GetCurrentScene()->enemies;
	
	for (std::list<Enemy*>::iterator it = ents->begin(); it != ents->end(); it++) {
		if (collider->CheckCollision(it._Ptr->_Myval->HitBox->rect)) {
				hit = true;
				LOG("ENEMY HIT");
				App->particle->DestroyParticle(this);
				it._Ptr->_Myval->Hit(curr_dir, App->player->power);
			}
		}


	return stdUpdate(dt);
}
