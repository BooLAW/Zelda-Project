#ifndef _SimonSays_Puzzles_H_
#define _SimonSays_Puzzles_H__

#include "Puzzle.h"
#include "Puzzle_Manager.h"
#include "Block.h"
#include "j1App.h"
#include "Block.h"

class SimonSays_Dungeon : public Puzzle
{
public:
	void Start();

	void Update();

	void LoopA();
	void LoopB();
	void LoopC();
	//void CleanUp() {};

public:
	bool check_loopA = false;
	bool check_loopB = false;
	bool check_loopC = false;
	bool check_player = true;
	bool loop_start = false;
	int curr_block_check = 0;

	int current_block = 0;
	int phase = 0;
	int first_block;
	int condition[4][2];

	std::deque<Block*> ssd_blocks;
};

#endif //!_SimonSays_Puzzles_H__