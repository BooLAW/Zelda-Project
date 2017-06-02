#include "GroundParticles.h"
#include "Particle.h"
#include "j1Player.h"
#include "j1Window.h"
#include "j1Render.h"

GroundParticle::GroundParticle(Arrow* element, Point<float>* object, SDL_Rect initial_rect, iPoint area_, iPoint timelife_, int num_textures, int num_particles, bool active_, bool mouse)
{
	//TODO 3:---------------------------------------------------------------------------------------
	//Check if entity (element) is different from nullptr
	//Then set the position of the entity and the pointer iPoint (object) to nullptr and entity pointer has created in .h
	//Otherwise, do it backwards. //element == nullptr and position = object ------
	if(object!=nullptr)
	{
		pos.x = object->x / App->win->GetScale();
		pos.y = object->y / App->win->GetScale();
		object_follow = object;
		arrow_to_follow = nullptr;
	}
	//--------------------------------------------------------------------------------------------
	area = area_;
	number_particles = num_particles;
	godelete = false;
	isMouse = mouse;
	active = active_;
	timelife = timelife_;
	n_textures = num_textures;
	size_rect = initial_rect.w;
	for (int i = 0; i < num_particles; i++)//
	{
		//TODO 4: ------------------------------------------------------------------------------
		//In this TODO we need open Particle.h and see the constructor
		//Create a new Particle and pushback in vector.
		//TIPS: Speed = fPoint(0,0) // Part_Direction = P_NON
		Particlef* temp = new Particlef(pos, area, timelife, Point<float>(0, 0), Part_Direction::Part_Direc_NULL, initial_rect, size_rect, num_textures, active_);
		particle.push_back(temp);
		//-------------------------------------------------------------------------------
	}
}

GroundParticle::~GroundParticle()
{
	for (std::vector<Particlef*>::iterator item = particle.begin(); item != particle.cend(); ++item)
		RELEASE(*item);
	particle.clear();
}

bool GroundParticle::Update(float dt)
{
	//TODO 5:-------------------------------------------------------------
	//Here we have to Update the position.
	//Check if the entity is diferent nullptr. On the contrary, use Update_position(iPoint* pos);

		Update_position(object_follow);

	//-------------------------------------------------------------------------------
	return true;
}

bool GroundParticle::PostUpdate()
{
	render(pos);
	return true;
}

void GroundParticle::render(Point<float> pos)
{
	if (active)
	{
		//TODO 6: ---------------------------------------------------------------------------
		//Iterate the filled vector, First Comprovated if the particle is Dead, and then use particle[i]->Modify();
		//TIPS: Use number_particles!! // iPoint num_tex -> (0, n_textures)!
		for (int i = 0; i < number_particles; i++)
		{
			if (particle[i]->isDead())
			{
				particle[i]->Modify(pos, area, timelife, iPoint(0, n_textures));
			}
		}
		//---------------------------------------------------------------------------
	}

	//TODO 7: -------------------------------------------------------------------
	//Draw particles
	//Iterate the filled vector, Call the functioon render();
	for (int i = 0; i < number_particles; i++)
	{
		particle[i]->render();
	}
	//-------------------------------------------------------------------------------
}

void GroundParticle::Update_position(Point<float>* element)
{
	if (isMouse == false)
	{
		pos.x = element->x + 15;
		pos.y = element->y + 29;
	}
	else
	{
		pos.x = (element->x - App->render->camera.x / App->win->GetScale());
		pos.y = (element->y - App->render->camera.y / App->win->GetScale());
	}

	//LOG("%i - %i", element->x, element->y);
	//LOG("%i - %i", pos.x, pos.y);
}