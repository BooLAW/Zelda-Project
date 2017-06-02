#pragma once
#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include "j1Module.h"
#include "Scene.h"

#define MAX_TIMELIFE 255
#define NORMAL_SPEED_Y 180

enum Wind {
	Part_Wind_UP,
	Part_Wind_DOWN,
	Part_Wind_LEFT,
	Part_Wind_RIGHT,
	Part_Wind_NULL
};

enum Part_Direction {
	Part_Direc_UP,
	Part_Direc_DOWN,
	Part_Direc_LEFT,
	Part_Direc_RIGHT,
	Part_Direc_RANDOM_X,
	Part_Direc_RANDOM_Y,
	Part_Direc_RANDOM,
	Part_Direc_RANDOM_FIREWORK,
	Part_Direc_NULL
};

enum Explosion_Type {
	CIRCLE,
	SEMICIRCLE_UPPER,
	SEMICIRCLE_LOWER,
	CROSS,
	RANDOM,
	NOTHING
};

class GroundParticle;


class ParticleManager : public j1Module
{
public:

	ParticleManager();

	// Destructor
	~ParticleManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//FUNCTIONS TO CREATE

	//Create & Delete Follow Group
	void CreateFollow_P(Arrow* arrow_to_follow, Point<float>* object_follow, SDL_Rect initial_rect, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, int num_textures = 4, int num_particles = 20, bool active_ = false, bool isMouse = false);
	bool DeleteFollow_p(GroundParticle* group);


	/*
	//Create & Delete Firework Group
	void CreateFirework_Particle(SceneElement* arrow_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, Part_Direction p_direction = Part_Direction::Part_Direc_NULL, int num_particles = 20, int num_textures = 4, iPoint next_textures = { 0, 4 }, iPoint last_textures = { 0, 4 });
	bool DeleteFirework_p(P_Firework* group);
	/**/

public:

	std::list<GroundParticle*> Group_Follow;

	SDL_Texture* atlas_particle = nullptr;
};

#endif // __PARTICLESYSTEM_H__#pragma once
