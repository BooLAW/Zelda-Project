// ----------------------------------------------------
// j1Module.h
// Interface for all engine modules
// ----------------------------------------------------

#ifndef __j1MODULE_H__
#define __j1MODULE_H__

#include "p2SString.h"
#include  "p2Defs.h"
#include "PugiXml\src\pugixml.hpp"
#include <list>
#include <string>
class j1App;
class PhysBody;
class b2Fixture;
class Collider;

class j1Module
{
public:

	j1Module() : active(false)
	{}

	virtual ~j1Module()
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}
	//COLLISIONS
	virtual void OnCollision(Collider* bodyA, Collider* bodyB)
	{

	}
	//CONSOLE
	virtual void OnCommand(std::list<std::string>& tokens) {

	}

	virtual void OnCVar(std::list<std::string>& tokens) {

	}

	virtual void SaveCVar(std::string& cvar_name, pugi::xml_node& node) const {

	}
public:

	p2SString	name;
	bool		active;

};

#endif // __j1MODULE_H__