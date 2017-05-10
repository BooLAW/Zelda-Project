#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include "EntityManager.h"
#include "Entity.h"
#include "j1App.h"

class Puzzle
{
public:
	Puzzle() {};
	virtual ~Puzzle() {};
	//bool LoadAttributes(pugi::xml_node attributes);
	virtual void Start() {};
	virtual void Update(float dt) {};
	virtual void CleanUp() {};
	virtual void Loop() {};

public:
	
	uint frame_start;
	uint interval;
	bool win_condition = false;
	bool started = false;
	bool lop_start = false;
};

#endif // !__PUZZL_H__