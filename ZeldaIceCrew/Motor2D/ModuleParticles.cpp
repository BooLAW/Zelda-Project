
#include "ModuleParticles.h"
#include "j1Collision.h"
#include "j1Map.h"
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
		if(particles[i] != nullptr)
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
		case p_enarrow:
			ret = new Enemy_Arrow();
			break;
		case p_shadow:
			ret = new Shadow_Projectile();
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

void ModuleParticles::AddParticle(Particle* particle, COLLIDER_TYPE collider_type, Uint32 life, Uint32 dmg, Uint32 delay)
{
	particle->born = SDL_GetTicks() + delay;
	particle->damage = dmg;
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
	particles.clear();
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

	if(collider != nullptr)
	collider->SetPos(position.x, position.y);
	
	App->render->toDraw(graphics, position.y + anim[curr_dir].GetCurrentFrame().h, position.x, position.y, &anim[curr_dir].GetCurrentFrame());

	return ret;
}

void Particle::CleanUp()
{
	if (graphics != nullptr)
		App->tex->UnLoad(graphics);

	if(collider != nullptr)
		collider->to_delete = true;

}

int Particle::CheckSpace(float new_x, float new_y)
{
	int ret = true;

	// TileCheck
	ret = App->map->TileCheck(new_x, new_y);
	// 0 walkable
	//1 wall
	// 2 hole

	SDL_Rect r = collider->rect;
	r.x = new_x;
	r.y = new_y;

	return ret;
}


void ModuleParticles::OnCollision(Collider* c1, Collider* c2) {
	LOG("\nparticle col\n");
	
}

void Arrow::Start()
{
	graphics = App->tex->Load("Sprites/Particles/Particles.png");
	g_rect[Up][0] = { 2, 2, 34, 34 };
	g_rect[Down][0] = { 38, 2, 34, 34 };
	g_rect[Right][0] = { 74, 2, 34, 34 };
	g_rect[Left][0] = { 110, 2, 34, 34 };
	
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
		anim[k].PushBack(g_rect[k][0]);
	}

	HitBox = { (int)position.x, (int)position.y, g_rect[0][0].w, g_rect[0][0].h };
	App->particle->AddParticle(this, COLLIDER_ARROW, 1500, App->player->power, NULL);

};

bool Arrow::Update(float dt)
{

	stdUpdate(dt);

	switch (curr_dir) {
	case Up:
		HitBox = { (int)position.x + 8, (int)position.y, 8, 8 };
		break;
	case Down:
		HitBox = { (int)position.x + 8, (int)position.y + 30, 8, 8 };
		break;
	case Left:
		HitBox = { (int)position.x, (int)position.y + 16, 8, 8 };
		break;
	case Right:
		HitBox = { (int)position.x + 30, (int)position.y + 16, 8, 8 };
		break;
	}

	collider->rect = HitBox;

	collider->SetPos(HitBox.x, HitBox.y);

	Collider* aux = collider;

	for (std::list<Enemy*>::iterator it = App->scene_manager->GetCurrentScene()->GetCurrentRoom()->enemies.begin(); it != App->scene_manager->GetCurrentScene()->GetCurrentRoom()->enemies.end(); it++)
	{
		if (it._Ptr->_Myval != nullptr && it._Ptr->_Myval->HitBox != nullptr && collider != nullptr)
		{
			Collider* aux = collider;
		
			if (aux->CheckCollision(it._Ptr->_Myval->HitBox->rect) && hit == false) 
			{
				hit = true;
				LOG("ENEMY HIT");
				App->particle->DestroyParticle(this);
				it._Ptr->_Myval->Hit(curr_dir, damage);
			}
		}
	}
	//BLOCK INTERACTION
	for (std::list<Block*>::iterator it = App->scene_manager->GetCurrentScene()->GetCurrentRoom()->blocks.begin(); it != App->scene_manager->GetCurrentScene()->GetCurrentRoom()->blocks.end(); it++)
	{
		if (it._Ptr->_Myval != nullptr && it._Ptr->_Myval->HitBox != nullptr && collider != nullptr)
		{
			Collider* aux = collider;
			if (aux->CheckCollision(it._Ptr->_Myval->HitBox->rect) && hit == false)
			{
				hit = true;
				LOG("BLOCK HIT");
				App->particle->DestroyParticle(this);
			}
		}
	}
	//TILED INTERACTION
	if (this->CheckSpace(position.x, position.y)==1)
	{
		LOG("ARROW HIT");
		App->particle->DestroyParticle(this);
	}
	

	return stdUpdate(dt);
}

void Enemy_Arrow::Start()
{
	graphics = App->tex->Load("Sprites/Particles/Particles.png");
	g_rect[Up][0] = { 2, 2, 34, 34 };
	g_rect[Down][0] = { 38, 2, 34, 34 };
	g_rect[Right][0] = { 74, 2, 34, 34 };
	g_rect[Left][0] = { 110, 2, 34, 34 };

	switch (curr_dir) {
	case Up:
		speed = { 0, -ARROW_SPEED };
		break;
	case Down:
		speed = { 0, +ARROW_SPEED };
		break;
	case Left:
		speed = { -ARROW_SPEED, 0 };
		break;
	case Right:
		speed = { +ARROW_SPEED, 0 };
		break;
	}

	for (int k = 0; k < LastDir; k++) {
		anim[k].PushBack(g_rect[k][0]);
	}

	HitBox = { (int)position.x, (int)position.y, g_rect[0][0].w, g_rect[0][0].h };
	App->particle->AddParticle(this, COLLIDER_ARROW, 2000, 1, NULL);

}

bool Enemy_Arrow::Update(float dt)
{
	stdUpdate(dt);

	switch (curr_dir) {
	case Up:
		HitBox = { (int)position.x + 8, (int)position.y, 8, 8 };
		break;
	case Down:
		HitBox = { (int)position.x + 8, (int)position.y + 30, 8, 8 };
		break;
	case Left:
		HitBox = { (int)position.x, (int)position.y + 16, 8, 8 };
		break;
	case Right:
		HitBox = { (int)position.x + 30, (int)position.y + 16, 8, 8 };
		break;
	}

	collider->rect = HitBox;

	collider->SetPos(HitBox.x, HitBox.y);

	Collider* aux = collider;

	if (aux->CheckCollision(App->player->link_coll->rect) && hit == false)
	{
		hit = true;
		LOG("Player HIT");
		App->player->HitPlayer(damage);
		App->particle->DestroyParticle(this);
	}

	//BLOCK INTERACTION
	for (std::list<Block*>::iterator it = App->scene_manager->GetCurrentScene()->GetCurrentRoom()->blocks.begin(); it != App->scene_manager->GetCurrentScene()->GetCurrentRoom()->blocks.end(); it++)
	{
		if (it._Ptr->_Myval != nullptr && it._Ptr->_Myval->HitBox != nullptr && collider != nullptr)
		{
			Collider* aux = collider;
			if (aux->CheckCollision(it._Ptr->_Myval->HitBox->rect) && hit == false)
			{
				hit = true;
				LOG("BLOCK HIT");
				App->particle->DestroyParticle(this);
			}
		}
	}
	//TILED INTERACTION
	if (this->CheckSpace(position.x, position.y) == 1)
	{
		LOG("ARROW HIT");
		App->particle->DestroyParticle(this);
	}


	return true;
}

void Shadow_Projectile::Start()
{
	graphics = App->tex->Load("Sprites/Particles/Particles.png");
	g_rect[Up][0] = { 2, 2, 34, 34 };
	g_rect[Up][1] = { 2, 2, 34, 34 };
	g_rect[Down][0] = { 38, 2, 34, 34 };
	g_rect[Down][1] = { 38, 2, 34, 34 };
	g_rect[Right][0] = { 74, 2, 34, 34 };
	g_rect[Right][1] = { 74, 2, 34, 34 };
	g_rect[Left][0] = { 110, 2, 34, 34 };
	g_rect[Left][1] = { 110, 2, 34, 34 };


	for (int k = 0; k < LastDir; k++) {
		anim[k].PushBack(g_rect[k][0]);
		anim[k].PushBack(g_rect[k][1]);
	}

	speed = { 1, 1 };

	damage = 1;

	HitBox = { (int)position.x, (int)position.y, 32, 32 };
	life = 6000;
	App->particle->AddParticle(this, COLLIDER_ENEMY_PROJECTILE, life, damage, NULL);

}

bool Shadow_Projectile::Update(float dt)
{
	
	float diff_x, diff_y;
	float hip;
	float angle;

	fPoint p_pos;
	p_pos.x = App->player->link_coll->rect.x;
	p_pos.y = App->player->link_coll->rect.y;

	diff_x = (p_pos.x - position.x);
	diff_y = p_pos.y - position.y;

	if (p_pos.x > position.x) {
		diff_x = -diff_x;
		diff_y = -diff_y;
	}

	angle = (atan2(diff_y, diff_x));

	if (p_pos.x >= position.x) {
		speed.x = SHADOW_SPD * -(float)cos((double)angle);
		speed.y = SHADOW_SPD * -(float)sin((double)angle);
	}
	else {
		speed.x = SHADOW_SPD * (float)cos((double)angle);
		speed.y = SHADOW_SPD * (float)sin((double)angle);
	}

	iPoint path_t = { App->player->link_coll->rect.x, App->player->link_coll->rect.y };
	if (path_t.y < position.y && (path_t.x > position.x - ENEMY_DIR_CHANGE_OFFSET && path_t.x < position.x + ENEMY_DIR_CHANGE_OFFSET))
		curr_dir = Up;
	else if (path_t.y > position.y && (path_t.x > position.x - ENEMY_DIR_CHANGE_OFFSET && path_t.x < position.x + ENEMY_DIR_CHANGE_OFFSET))
		curr_dir = Down;
	else if (path_t.x < position.x)
		curr_dir = Left;
	else if (path_t.x > position.x)
		curr_dir = Right;

	switch (curr_dir) {
	case Up:
		HitBox = { (int)position.x + 8, (int)position.y, 32, 32 };
		break;
	case Down:
		HitBox = { (int)position.x + 8, (int)position.y + 30, 32, 32 };
		break;
	case Left:
		HitBox = { (int)position.x, (int)position.y + 16, 32, 32 };
		break;
	case Right:
		HitBox = { (int)position.x + 30, (int)position.y + 16, 32, 32 };
		break;
	}

	collider->rect = HitBox;

	collider->SetPos(HitBox.x, HitBox.y);

	Collider* aux = collider;

	if (aux->CheckCollision(App->player->link_coll->rect) && hit == false)
	{
		hit = true;
		LOG("Player HIT");
		App->player->HitPlayer(damage);
		App->particle->DestroyParticle(this);
	}

	//BLOCK INTERACTION
	for (std::list<Block*>::iterator it = App->scene_manager->GetCurrentScene()->GetCurrentRoom()->blocks.begin(); it != App->scene_manager->GetCurrentScene()->GetCurrentRoom()->blocks.end(); it++)
	{
		if (it._Ptr->_Myval != nullptr && it._Ptr->_Myval->HitBox != nullptr && collider != nullptr)
		{
			Collider* aux = collider;
			if (aux->CheckCollision(it._Ptr->_Myval->HitBox->rect) && hit == false)
			{
				hit = true;
				LOG("BLOCK HIT");
				App->particle->DestroyParticle(this);
			}
		}
	}
	//TILED INTERACTION
	if (this->CheckSpace(position.x, position.y) == 1)
	{
		LOG("ARROW HIT");
		App->particle->DestroyParticle(this);
	}

	if (this->collider->CheckCollision(App->player->weapon_coll->rect)) {
		App->particle->DestroyParticle(this);
	}

	LOG("LIFE %d", SDL_GetTicks() - born);

	return stdUpdate(dt);
}
