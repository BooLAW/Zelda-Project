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
	to_overworld_coll = App->collisions->AddCollider({ 13 * 16,18 * 16,32,16 }, COLLIDER_TO_OVERWORLD_HOUSE, App->player);

	App->player->SetPos(6.5 * 32, 8 * 32);
	App->render->MoveCam(256, 128);
	App->render->ScaleCamBoundaries(300);
	
	//we can do that with an iterator that recieves the positions readed from the xml file
	//	Scene::AddDoorway(dw_house, Direction::Down, 13*16,20*16);

	follow_cam = true;


		App->render->camera.x = -App->render->camera.w / 2;
		App->render->camera.y = -App->render->camera.h / 2;

		App->audio->PlayMusic("Audio/music/Home.ogg");
	return true;
}

// Called each loop iteration
bool HouseScene::PreUpdate()
{
	// debug pathfing ------------------
	
	if (App->debug == true) {
		static iPoint origin;
		static bool origin_selected = false;

		int x, y;
		App->input->GetMousePosition(x, y);
		iPoint p = App->render->ScreenToWorld(x, y);
		p = App->map->WorldToMap(p.x, p.y);

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			if (origin_selected == true)
			{
				App->pathfinding->CreatePath(origin, p);
				origin_selected = false;
			}
			else
			{
				origin = p;
				origin_selected = true;
			}
		}
	}
	return true;
}

// Called each loop iteration
bool HouseScene::Update(float dt)
{
	App->render->cam_travel = false;

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		App->render->cam_travel = true;
		App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
	}

	App->map->Draw();

	return true;
}

// Called each loop iteration
bool HouseScene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

bool HouseScene::CleanUp()
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