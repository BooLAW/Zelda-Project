#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "VillageScene.h"
#include "j1Fonts.h"
#include "j1Player.h"
#include "Scene.h"
#include "SceneManager.h"
#include "DungeonScene.h"
#include <fstream>

#define MAX_TABS 2

DungeonScene::DungeonScene()
{

}

// Destructor
DungeonScene::~DungeonScene()
{

}

// Called before render is available
bool DungeonScene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool DungeonScene::Start()
{
	App->scene_manager->loading_screen->active = true;
	BROFILER_CATEGORY("StartDungeon", Profiler::Color::DarkBlue);
	curr_id = dungeon;
	stdStart();
	//GetRoom(0, 2)->AddNpc(NPC_ZELDA,500, 400, 1);
	App->player->PlayerInmortal(10);
	if (App->scene_manager->dungeon_id == 6) {
		wave_time.Start();
		wave_time.SetFlag(true);

		starting = false;

		spawn1 = { 592, 393 };
		spawn2 = { 592, ROOM_H + 297 };
		spawn3 = { ROOM_W + 386, ROOM_H + 297 };
		spawn4 = { ROOM_W + 386, 393 };
		App->player->pl_speed.x = ORIGIN_SPD;
		App->player->pl_speed.y = ORIGIN_SPD;
		to_round = 0;
		round = 0;

	}
	/*if (App->scene_manager->dungeon_id == 0) {
		App->scene_manager->GetCurrentScene()->GetRoom(2, 4)->AddNpc(NPC_ZELDA, 500,250, 1);
	}
	if (App->scene_manager->dungeon_id == 1) {
		App->scene_manager->GetCurrentScene()->GetRoom(1, 4)->AddNpc(NPC_ZELDA, 500, 250, 1);
	}
	if (App->scene_manager->dungeon_id == 2) {
		App->scene_manager->GetCurrentScene()->GetRoom(3, 3)->AddNpc(NPC_ZELDA, 500, 250, 1);
	}
	if (App->scene_manager->dungeon_id == 3) {
		App->scene_manager->GetCurrentScene()->GetRoom(3, 3)->AddNpc(NPC_ZELDA, 500, 250, 1);
	}
	if (App->scene_manager->dungeon_id == 4) {
		App->scene_manager->GetCurrentScene()->GetRoom(2, 5)->AddNpc(NPC_ZELDA, 500, 250, 1);
	}*/
	if (App->scene_manager->dungeon_id == 5) {
		App->scene_manager->GetCurrentScene()->GetRoom(0, 0)->AddNpc(NPC_ZELDA, 500, 250, 1);
	}

	App->player->rupees = 50;

	App->Pause();

	
	
	starting_time.Start();
	starting_time.SetFlag(true);

	return true;
}

// Called each loop iteration
bool DungeonScene::Update(float dt)
{
	
	
	BROFILER_CATEGORY("UpdateDungeon", Profiler::Color::Red)

	stdUpdate(dt);
	if (starting_time.GetFlag() == true && starting_time.Read() < 1500) {
		App->scene_manager->loading_screen->active = true;
	}
	if (starting_time.GetFlag() == true && starting_time.Read() > 1500) {
		App->UnPause();
		starting_time.SetFlag(false);
		App->scene_manager->loading_screen->active = false;
	}


		if (App->scene_manager->dungeon_id == 6) {
			if (wave_time.Read() > 5000 && starting == false) {
				wave_time.SetFlag(false);
				starting = true;
				round = 1;
				change_round = 0;
				LOG("STARTING");
			}

			if (starting) {
					wave_time.Start();
					if (GetRoom(0, 0)->NoEnemies() == true) {
						wave_time.SetFlag(true);
					}

					if (wave_time.Read() > 5000) {
						LOG("WAVE");
						if (to_round < round) {
							LOG("ROUND");
							round_timer.Start();
							round_timer.SetFlag(true);
							if (round_timer.Read() > 2000) {
								LOG("SPAWN");
								AddEnemy(rand() % 9, 0, 0, spawn1.x, spawn1.y);
								AddEnemy(rand() % 9, 0, 0, spawn2.x, spawn2.y);
								AddEnemy(rand() % 9, 0, 0, spawn3.x, spawn3.y);
								AddEnemy(rand() % 9, 0, 0, spawn4.x, spawn4.y);
								to_round++;
								round_timer.SetFlag(false);
							}
						}
						else {
							GetRoom(0, 0)->AddItem(rand() % 14, 1025, 622);
							if (round < 3) {
								if(change_round % 3 == 0)
								round++;
							}
							else { round = 3; }
							change_round++;
							to_round = 0;
							wave_time.SetFlag(false);
							round_timer.SetFlag(false);
						}
					}
				}
			
		}

		return true;
	}






