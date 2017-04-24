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
#include "HouseScene.h"
#include "ShopScene.h"

#define MAX_TABS 2

ShopScene::ShopScene()
{

}

// Destructor
ShopScene::~ShopScene()
{}

// Called before render is available
bool ShopScene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool ShopScene::Start()
{

	if (App->map->Load("Shop.tmx") == true)
	{
		//int w, h;
		//uchar* data = NULL;
		//if (App->map->CreateWalkabilityMap(w, h, &data))
		//	App->pathfinding->SetMap(w, h, data);
		//
		//RELEASE_ARRAY(data);
	}

	AddRoom(0, 0);

	GetRoom(0, 0)->room_rect.h = 768;

	Doorway* dw = nullptr;
	dw = Scene::AddDoorway(dw_scene, 0, 0, Down, 14 * 16, 20 * 16);
	dw->SetTarget((Scene*)App->scene_manager->village_scene);
	dw->target_pos = { 54 * 16, 54 * 16 };

	App->render->CamBoundOrigin();

	App->render->ScaleCamBoundaries(300);

	App->audio->PlayMusic("Audio/Music/Shop.ogg");
	App->audio->SetVolumeMusic(40);


	Item* new_item = nullptr;
	new_item = AddItem(weapon_bow, 0, 0, 350, 190);
	new_item->SetPrice(30);

	new_item = AddItem(pegasus_boots, 0, 0, 150, 190);
	new_item->SetPositions({ 150.0f, 190.0f });
	new_item->SetPrice(30);

	// Enemy Start

	// Items Start

	//we can do that with an iterator that recieves the positions readed from the xml file

	follow_cam = false;

	App->render->SetCamPos(0, 0);



	return true;
}

// Called each loop iteration
bool ShopScene::PreUpdate()
{
	return true;
};