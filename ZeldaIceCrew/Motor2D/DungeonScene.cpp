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
	GetRoom(0, 2)->AddNpc(NPC_ZELDA,500, 400, 1);
	boss_music = false;
	chain_boss_defeated = false;

	return true;
}

// Called each loop iteration
bool DungeonScene::Update(float dt)
{
	BROFILER_CATEGORY("UpdateDungeon", Profiler::Color::Red)

	stdUpdate(dt);

	//if (chain_boss_defeated == false && IsEnemy(ChainBoss) == false)
	//	chain_boss_defeated = true;
	//
	//if (chain_boss_defeated == false) {
	//	if (GetRoom(0, 0)->PlayerInside() == true) {
	//		
	//		if (chain_boss_defeated == false)
	//			ChainBoss_dw->open = false;
	//		else
	//			ChainBoss_dw->open = true;
	//
	//		if (boss_music == false) {
	//			App->audio->PlayMusic("Audio/Music/Hyrule_Castle.ogg");
	//			boss_music = true;
	//		}
	//
	//		if (chain_boss_defeated == true && boss_music == true) {
	//			App->audio->PlayMusic("");
	//			boss_music = false;
	//		}
	//
	//			boss_minions_spawn_time.Start();
	//			boss_minions_spawn_time.SetFlag(true);
	//			if (boss_minions_spawn_time.ReadSec() >= 5) {
	//				GetRoom(0, 0)->AddEnemy(t_greensoldier, 150, 150);
	//				GetRoom(0, 0)->AddEnemy(t_greensoldier, 850, 150);
	//				boss_minions_spawn_time.SetFlag(false);
	//			}
	//	}
	//	else {
	//		if (boss_music == true) {
	//			App->audio->PlayMusic("Audio/Music/Song_of_Storms.ogg");
	//			boss_music = false;
	//		}
	//	}
	//}

	return true;

}