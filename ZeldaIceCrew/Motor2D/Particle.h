#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "ParticleManager.h"

#define TIME_WIND 160

class Particlef
{
public:
	//Initialize position and animation
	//Constructor Particle
	Particlef(fPoint respawn, iPoint area_respawn = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, Part_Direction p_direction = Part_Direction::Part_Direc_NULL, SDL_Rect initial_rect = { 0,0,8,2 }, int size = 2, int num_tex_p = 4, bool active = false, Wind dir = Wind::Part_Wind_NULL, iPoint num_tex = { 0,0 });

	//Reactive this only when the particle is created
	bool Modify(fPoint respawn, iPoint area_respawn = { 12, 2 },iPoint timelife = { 15,5 }, iPoint num_tex_p = { 0, 4 });

	//Checks if particle is dead
	bool isDead();

	//render particle
	void render();

	//Move particle
	void Move(fPoint speed, Wind dir = Wind::Part_Wind_NULL, bool Move_alternative = false);

	//GetPosition
	fPoint GetPosition();
	//GetSpeed
	fPoint GetSpeed();
	//Set Gravity (Simulation)
	void SetSpeedGreavity(fPoint speed);

	//Only Firework --------------------
	void SetRepeat(bool);
	bool GetRepeat();

private:
	//position
	fPoint position = { 0.0f,0.0f };

	//Texture
	SDL_Rect rect = { 0,0,0,0 };
	SDL_Rect initial_rect = { 0,0,0,0 };

	//velocity
	fPoint speed = { 0.0f,0.0f };
	int size_rect = 0;

	//Rect

	bool not_repeat = false; //ONLY FIREWORK

							 //Time Life
	iPoint degrade = { 0.0f,0.0f };
};

#endif /*_PARTICLE_H_*/
