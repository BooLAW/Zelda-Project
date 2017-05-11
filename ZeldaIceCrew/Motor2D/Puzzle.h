#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include "EntityManager.h"
#include "Entity.h"
#include "j1App.h"
#include "Block.h"
#include "Room.h"

class Room;
class Block;

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


//Simon Says Puzzle

class SimonSays_Dungeon : public Puzzle {
public:
	void Start();

	void Update();

	void Loop();
	//void CleanUp() {};

public:
	int check_loop = 0;
	bool check_player = true;
	bool loop_start = false;
	int curr_block_check = 0;

	int current_block = 0;
	int phase = 0;
	int first_block;
	int condition[6][2];

	iPoint room_puzzle = {1,1};
	//std::deque<Block*> ssd_blocks;
	
	
	/*
	std::list<Block*>::iterator it = ...
	for(int i = 0; i < first_block; i++) {
		it++;
	}
	(*it)->
	*/

};





#endif // !__PUZZL_H__