#include "Simon_Says_Puzzle.h"


void SimonSays_Dungeon::Start() {

	if (started == false) {

		if (App->puzzle_manager->puzzles.empty() == false) {//comprobar que la current scene es la correcte per el puzzle
			started = true;
			active = true;
		}
	}
	LOG("Dungeon's SimonSays Puzzle initialized");
}

void SimonSays_Dungeon::Update() {

	if (started == true) {
		if (loop_start == false) {
			for (uint i = 0; i < blocks_used.size(); i++) {
				if (blocks_used[i].subtype == button_wall && blocks_used[i].anim = on) {
					loop_start = true;
					frame_start = App->frame_count;
					current_block = i;
				}
			}
		}
		
		if (loop_start == true)
			Loop();

	}

}

void SimonSays_Dungeon::Loop() {
	
	if (App->frame_count = frame_start + interval * phase) {
		blocks_used[current_block].anim = idle;
		current_block++;
	}

	while (current_block < blocks_used.size() && App->frame_count >= frame_start + interval * phase) {

		if (blocks_used[current_block].subtype == torch_bowl && blocks_used[current_block].puzzle == SimonSays_Dungeon_) {
			blocks_used[current_block].anim = lit;
			phase++;
			break;
		}

		current_block++;
	}
	
	
	
}