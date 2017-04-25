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
	Doorway* dw = nullptr;
	dw = Scene::AddDoorway(dw_scene, Direction::Down, 14 * 16, 20 * 16);
	dw->SetTarget((Scene*)App->scene_manager->village_scene);
	dw->target_pos = { 54 * 16, 54 * 16 };

	App->render->CamBoundOrigin();

	App->render->ScaleCamBoundaries(300);

	App->audio->PlayMusic("Audio/Music/Shop.ogg");
	App->audio->SetVolumeMusic(40);

	Item* new_item = nullptr;
	new_item = App->entitymanager->CreateItem(weapon_sword);
	new_item->SetPositions({ 350.0f, 190.0f });
	new_item->SetPrice(30);
	items.push_back(new_item);

	new_item = App->entitymanager->CreateItem(pegasus_boots);
	new_item->SetPositions({ 150.0f, 190.0f });
	new_item->SetPrice(30);
	items.push_back(new_item);
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
}

// Called each loop iteration
bool ShopScene::Update(float dt)
{

	App->render->cam_travel = false;

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		//App->render->cam_travel = true;
		App->scene_manager->toChangeScene(App->scene_manager->village_scene);
	}

	//follow_cam = true;

	App->map->Draw();

	DoorUpdate(dt);

	return true;

}

// Called each loop iteration
bool ShopScene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
		ESC = true;
	}

	return ret;
}
bool ShopScene::CleanUp()
{
	
	App->collisions->EraseCollider(to_overworld_coll);
	App->map->CleanUp();

	if (items.empty() == false) {
		for (std::list<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				App->entitymanager->DestroyEnity((*it));
		}
		items.clear();
	}
	if (enemies.empty() == false) {
		for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				App->entitymanager->DestroyEnity((*it));
		}
		enemies.clear();
	}

	if (blocks.empty() == false) {
		for (std::list<Block*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				App->entitymanager->DestroyEnity((*it));
		}
		blocks.clear();
	}

	if (doorways.empty() == false) {
		for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr)
				it._Ptr->_Myval->CleanUp();
			//RELEASE(*it);
		}
		doorways.clear();
	}
	return true;
}