#ifndef __PUZZLE_MANAGER_H__
#define __PUZZLE_MANAGER_H__

#include "EntityManager.h"
#include "Entity.h"
#include "Block.h"


#include "Puzzle.h"

enum Puzzle_List {
	no_puzzles = 0,
	SimonSays_Dungeon_,

	_last_
};

class Puzzle;
class SimonSays_Dungeon;
class Block;

class Puzzle_Manager : public j1Module
{
public:
	Puzzle_Manager();
	virtual ~Puzzle_Manager() {};
	//bool LoadAttributes(pugi::xml_node attributes);
	bool Start();
	//bool PreUpdate();
	bool Update(float dt);
	//bool PostUpdate();
	bool CleanUp();
	void PushBlock(Block* block);
	void PushPuzzle(Puzzle* puzzle);

	std::deque<Block*> blocks_used;
	std::deque<Puzzle*> puzzles;

	//SimonSays_Dungeon SimonSays_Dungeon_;

private:
	j1Timer time;
	
};

#endif // !__PUZZLE_MANAGER_H__