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
#include "HouseScene.h"
#include "j1Fonts.h"
#include "j1Player.h"
#include "VillageScene.h"
#include "Scene.h"
#include "SceneManager.h"
#include "DungeonScene.h"
#define MAX_TABS 2

HouseScene::HouseScene() 
{
}

// Destructor
HouseScene::~HouseScene()
{}

// Called before render is available
bool HouseScene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool HouseScene::Start()
{
	App->render->cam_travel = false;
	if (App->map->Load("House.tmx") == true)
	{
		//int w, h;
		//uchar* data = NULL;
		//if (App->map->CreateWalkabilityMap(w, h, &data))
		//	App->pathfinding->SetMap(w, h, data);
		//
		//RELEASE_ARRAY(data);
	}
	//to_overworld_coll = App->collisions->AddCollider({ 13 * 16,18 * 16,32,16 }, COLLIDER_TO_OVERWORLD_HOUSE, App->player);
	
	AddRoom(0, 0);

	GetRoom(0, 0)->room_rect.h = 768;

	AddEnemy(t_bluesoldier, 0, 0, 5, 5);
	//AddItem(drop_heart, 0, 0, 5, 5);

	DwScene* dw = nullptr;
	dw = (DwScene*)AddDoorway(dw_scene, 0, 0, Down, 13 * 16, 18 * 16);
	dw->SetTarget((Scene*)App->scene_manager->village_scene);
	dw->target_pos = { 23 * 16, 108 * 16 };

	App->render->CamBoundOrigin();

	App->player->SetPos(6.5 * 32, 8 * 32);
	App->render->camera.x = 256;
	App->render->camera.y = 128;
	
	follow_cam = false;
	App->render->ScaleCamBoundaries(300);
	
	//we can do that with an iterator that recieves the positions readed from the xml file
	//	Scene::AddDoorway(dw_house, Direction::Down, 13*16,20*16);


	//App->render->SetCamPos(-300, -300);

		App->audio->PlayMusic("Audio/music/Home.ogg");

		App->audio->SetVolumeMusic(40);

	return true;
};