#ifndef __PUZZLE_MANAGER_H__
#define __PUZZLE_MANAGER_H__

#include "EntityManager.h"
#include "Entity.h"
#include "Block.h"
#include "SceneManager.h"
#include "Scene.h"
#include "j1App.h"
#include "Puzzle_Manager.h"

class Puzzle
{
public:
	Puzzle() {};
	virtual ~Puzzle() {};
	//bool LoadAttributes(pugi::xml_node attributes);
	virtual void Start() {};
	virtual void Update(float dt) {};
	virtual void CleanUp() {};

public:
	
	uint frame_start;
	uint interval;

};

#endif // !__PUZZLE_MANAGER_H__