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

VillageScene::VillageScene()
{
	
}

// Destructor
VillageScene::~VillageScene()
{}

// Called before render is available
bool VillageScene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool VillageScene::Start()
{
	BROFILER_CATEGORY("StartVillage", Profiler::Color::DarkBlue);
	curr_id = village;
	stdStart();
	App->player->room = { 0,0 };
	GetRoom(0, 2)->AddNpc(NPC_ZELDA, 2000, 550, 1);
	return true;
};
bool VillageScene::Update(float dt)
{
	BROFILER_CATEGORY("UpdateDungeon", Profiler::Color::Red)

		stdUpdate(dt);
	return true;
}