#include "Puzzle.h"

void SimonSays_Dungeon::Start() {

	if (started == false) {

		if (App->puzzle_manager->puzzles.empty() == false) {//comprobar que la current scene es la correcte per el puzzle
			started = true;
			interval = 30;
		}
	}
	LOG("Dungeon's SimonSays Puzzle initialized");
}

void SimonSays_Dungeon::Update() {

	if (started == true) {
		if (loop_start == false && check_player == true) {
			for (uint i = 0; i < App->puzzle_manager->blocks_used.size(); i++) {
				if (App->puzzle_manager->blocks_used[i]->subtype == button_wall && App->puzzle_manager->blocks_used[i]->anim == on) {
					loop_start = true;
					frame_start = App->frame_count;
					first_block = i;
					break;
				}
			}

			for (int i = 0; i < 6; i++) {
				condition[i][0] = first_block + (rand() % 4);
			}
		}

		if (loop_start == true) {
			check_player = false;
			Loop();
		}

		if (loop_start == false && check_player == false) {
			for (int i = first_block; i < first_block + 4; i++)
				if (App->puzzle_manager->blocks_used[i]->anim == lit && condition[curr_block_check][1] == 0) {
					condition[curr_block_check][1] = i;
					curr_block_check++;
				}
		}

		if (curr_block_check >= 3) {
			for (int i = 0; i < 6; i++) {
				if (condition[i][0] != condition[i][1]) {
					started = false;
					break;
				}
			}
			if (started == false) {
				//spawneja enemics
			}
			else {
				//reward
			}
		}
	}

}

void SimonSays_Dungeon::Loop() {
	if (check_loop < 3) {
		if (App->frame_count = frame_start + interval * phase) {
			App->puzzle_manager->blocks_used[current_block]->anim = idle;
			current_block = condition[phase][0];
		}

		while (current_block < App->puzzle_manager->blocks_used.size() && App->frame_count >= frame_start + interval * phase) {

			if (App->puzzle_manager->blocks_used[current_block]->subtype == torch_bowl && App->puzzle_manager->blocks_used[current_block]->puzzle == SimonSays_Dungeon_) {
				App->puzzle_manager->blocks_used[current_block]->anim = lit;
				phase++;
				break;
			}

			current_block++;
		}

		if (phase > 5) {
			phase = 0;
			loop_start = false;
		}
	}

}