#pragma once
#ifndef _P_FOLLOW_H_
#define _P_FOLLOW_H_

#include "ModuleParticles.h"

class Particlef;

class GroundParticle
{
public:
	GroundParticle(Arrow* arrow_to_follow, fPoint* object_follow, SDL_Rect initial_rect, iPoint area, iPoint timelife, int num_textures, int num_particles, bool active_, bool isMouse);
	~GroundParticle();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);

	void Update_position(fPoint* pos);


public:
	//TODO 2: ---------------------------------------------------------------------
	//Create a Particle Vector, use std::vector
	//Also, create a pointer to an entity (SceneElement*)
	//And finally a pointer to an iPoint (iPoint*)
	std::vector<Particlef*> particle;
	Arrow* arrow_to_follow = nullptr;
	fPoint* object_follow = nullptr;
	//-----------------------------------------------------------------------------
	//Num of particles
	int number_particles = 0;

	//iPoints
	iPoint area = { 0,0 };
	iPoint timelife = { 0,0 };

	//position
	fPoint pos = { 0.0f,0.0f };
	int size_rect = 0;
	int n_textures = 0;

	//velocity
	//fPoint speed;
	bool active = false;
	bool isMouse = false;

	bool godelete = false;

};

#endif /*_P_FOLLOW_H_*/
