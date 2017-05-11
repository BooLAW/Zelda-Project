#include "Puzzle_Manager.h"

Puzzle_Manager::Puzzle_Manager(){
	name = "puzzle_manager";
}

bool Puzzle_Manager::Start() {
	bool ret = true;

	return ret;
}

bool Puzzle_Manager::Update(float dt) {
	bool ret = true;

	if (blocks_used.empty() == false)
		//LOG("PUZZLES UPDT START");
		if (puzzles.empty() == false)
			for (int i = 0; i < puzzles.size(); i++) {
				if (puzzles[i] != nullptr) {
					if (!App->IsPaused()) {
						//LOG("PUZZLES UPDATE %d", i);
						if (puzzles[i]->started == true)
							puzzles[i]->Update(dt);
					}
				}
			}

	return ret;
}

bool Puzzle_Manager::CleanUp() {
	bool ret = true;

	std::deque<Block*>::iterator aux;

	for (uint i = 0; i < blocks_used.size(); i++) {
		if (blocks_used[i] != nullptr) {
			aux = std::find(blocks_used.begin(), blocks_used.end(), blocks_used[i]);
			blocks_used.erase(aux);
		}
	}

	return ret;
}

void Puzzle_Manager::PushBlock(Block * block)
{
	if (block != nullptr)
		blocks_used.push_back(block);
	else
		LOG("Error Pushing Puzzle Block to Block used for Puzzles List");
}

void Puzzle_Manager::PushPuzzle(Puzzle * puzzle)
{
	if (puzzle != nullptr) {
		puzzle->Start();
		puzzles.push_back(puzzle);
	}
	else
		LOG("Error Pushing Puzzle to Puzzles List");
}
