#ifndef _SimonSays_Puzzles_H_
#define _SimonSays_Puzzles_H__

#include "Puzzle.h"
#include "Puzzle_Manager.h"
#include "Block.h"

class SimonSays_Dungeon : public Puzzle
{
public:
	void Start();

	void Update();

	void Loop();
	//void CleanUp() {};

public:
	bool check_loop1 = false;
	bool check_loop2 = false;
	bool check_loop3 = false;

	int current_block = 0;
	int phase = 0;

	std::deque<Block*> ssd_blocks;
};

#endif //!_SimonSays_Puzzles_H__