#include "ParticleManager.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Timer.h"
#include "GroundParticles.h"


ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

bool ParticleManager::Awake()
{
	return true;
}

bool ParticleManager::Start()
{
	//texture
	atlas_particle = App->tex->Load("particles/atlas_particle.png");

	//Link Follow
	Group_Follow.push_back(new GroundParticle(nullptr, &App->player->pos, SDL_Rect{ 0,6,2,0 }, iPoint(5, 2), iPoint(15, 5), 4, 20, true, false));
	/*
	//TODO 8: ----------------------------------------------------------------------------------
	//Uncomment
	Group_Follow.push_back(new P_Follow(nullptr, &App->input->GetMousePosition(), SDL_Rect{ 0,2,2,0 }, iPoint(0, 0), iPoint(15, 5), 4, 20, true, true));

	Group_Fire.push_back(new P_Fire(nullptr, &App->input->GetMousePosition(), iPoint(0,0), SDL_Rect{ 0,2,2,0 }, iPoint(5, 2), iPoint(12, 4), fPoint(60, -60), Part_Direction::Part_Direc_RANDOM, 65, 4, true, Wind::Part_Wind_NULL));
	// ---------------------------------------------------------------------------------------
	*/
	return true;
}

bool ParticleManager::PreUpdate()
{
	return true;
}

bool ParticleManager::Update(float dt)
{
	//Group FOLLOW -------------------------------------------------
	std::list<GroundParticle*>::iterator item = Group_Follow.begin();
	while (item != Group_Follow.end())
	{
		item._Ptr->_Myval->Update(dt);
		item++;
	}

	return true;
}

bool ParticleManager::PostUpdate()
{
	//Iterate all list
	//Group FOLLOW -------------------------------------------------
	std::list<GroundParticle*>::iterator item = Group_Follow.begin();
	while (item != Group_Follow.end())
	{
		item._Ptr->_Myval->PostUpdate();
		item++;
	}
	return true;
}

bool ParticleManager::CleanUp()
{
	for (std::list<GroundParticle*>::iterator item = Group_Follow.begin(); item != Group_Follow.cend(); ++item)
		RELEASE(*item);
	Group_Follow.clear();


	App->tex->UnLoad(atlas_particle);

	atlas_particle = nullptr;

	return true;
}

//CREATE GROUPS -------------------------------------------------------------------------------------------------------------------------------------
void ParticleManager::CreateFollow_P(Arrow* arrow_to_follow, Point<float>* object_follow, SDL_Rect initial_rect, iPoint area, iPoint timelife, int num_textures, int num_particles, bool active, bool isMouse)
{
	Group_Follow.push_back(new GroundParticle(arrow_to_follow, object_follow, initial_rect, area, timelife, num_textures, num_particles, active, isMouse));
}


//DELETE GROUPS -------------------------------------------------------------------------------------------------------------------------------------
bool ParticleManager::DeleteFollow_p(GroundParticle* group)
{
	std::list<GroundParticle*>::iterator item = Group_Follow.begin();
	while (item != Group_Follow.end())
	{
		if (item._Ptr->_Myval == group)
		{
			Group_Follow.erase(item);
		}
		item++;
	}
	return true;
}

