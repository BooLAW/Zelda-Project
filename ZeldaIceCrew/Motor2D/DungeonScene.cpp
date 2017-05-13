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
{}

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
	BROFILER_CATEGORY("StartDungeon", Profiler::Color::DarkBlue);
	curr_id = dungeon;
	stdStart();
	//GetRoom(0, 2)->AddNpc(NPC_ZELDA,500, 400, 1);
	App->player->PlayerInmortal(10);
	if (App->scene_manager->dungeon_id == 6) {
		wave_time.Start();
		wave_time.SetFlag(true);

		starting = false;

		spawn1 = { 1200, 500 };
		spawn2 = { 1300, 500 };
		spawn3 = { 1400, 500 };
		spawn4 = { 1500, 500 };

		to_round = 0;

	}

	App->Pause();

	return true;
}

// Called each loop iteration
bool DungeonScene::Update(float dt)
{
	BROFILER_CATEGORY("UpdateDungeon", Profiler::Color::Red)

	stdUpdate(dt);

	starting_time.Start();
	starting_time.SetFlag(true);

	if (starting_time.Read() > 1500) {
		App->UnPause();
	}

		if (App->scene_manager->dungeon_id == 6) {
			if (wave_time.Read() > 5000) {
				wave_time.SetFlag(false);
				starting = true;
				round = 1;
				LOG("STARTING");
			}

			if (starting) {
				wave_time.Start();
				wave_time.SetFlag(true);

				if (wave_time.Read() > 2000 && to_round <= round) {
					LOG("WAVE");
					round_timer.Start();
					round_timer.SetFlag(true);
					if (round_timer.Read() > 500) {
						LOG("SPAWN");
						AddEnemy(rand() % 10, 0, 0, spawn1.x, spawn1.y);
						AddEnemy(rand() % 10, 0, 0, spawn2.x, spawn2.y);
						AddEnemy(rand() % 10, 0, 0, spawn3.x, spawn3.y);
						AddEnemy(rand() % 10, 0, 0, spawn4.x, spawn4.y);
						to_round++;
						round_timer.SetFlag(false);
					}
				}
				else {
					round++;
					to_round = 0;
					wave_time.SetFlag(false);
				}

			}

		}

	return true;

}