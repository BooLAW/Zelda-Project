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
#include "DungeonScene.h"
#include "ShopScene.h"

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
	boss_music = false;
	chain_boss_defeated = false;

	if (App->map->Load("Dungeon.tmx") == true)
	{
		//int w, h;
		//uchar* data = NULL;
		//if (App->map->CreateWalkabilityMap(w, h, &data))
		//	App->pathfinding->SetMap(w, h, data);
		//
		//RELEASE_ARRAY(data);
	}

	App->render->CamBoundOrigin();

	App->render->ScaleCamBoundaries(300);
	//Door Colliders
		//Boss room
	
	Scene::AddDoorway(dw_dungeon, Direction::Up, 0, 3); 
	Scene::AddDoorway(dw_dungeon, Direction::Down, 0, 2); 
	Scene::AddDoorway(dw_dungeon, Direction::Up, 0, 2); 
	Scene::AddDoorway(dw_dungeon, Direction::Down, 0, 1); 
	Scene::AddDoorway(dw_dungeon, Direction::Up, 0, 1); 
	ChainBoss_dw = Scene::AddDoorway(dw_dungeon, Direction::Down, 0, 0); 
	Scene::AddDoorway(dw_dungeon, Direction::Right, 0, 1); 
	Scene::AddDoorway(dw_dungeon, Direction::Left, 1, 1);
	//room1_up = App->collisions->AddCollider({ ROOM_W/2 + 0, 50 + 3 * ROOM_H,32,16 }, COLLIDER_DUNGEON_UP, App->player);
	//room2_down = App->collisions->AddCollider({ ROOM_W/2 +0, ROOM_H - 50 + 2 * ROOM_H,32,16 }, COLLIDER_DUNGEON_DOWN, App->player);
	//room2_up= App->collisions->AddCollider({ ROOM_W/2 + 0, 50 + 2 * ROOM_H,32,16 }, COLLIDER_DUNGEON_UP, App->player);
	//room3_down = App->collisions->AddCollider({ ROOM_W/2 + 0, ROOM_H - 50 + 1 * ROOM_H,32,16 }, COLLIDER_DUNGEON_DOWN, App->player);
	//room3_up = App->collisions->AddCollider({ ROOM_W / 2 + 0, 50 + 1 * ROOM_H,32,16 }, COLLIDER_DUNGEON_UP, App->player);
	//room5_down = App->collisions->AddCollider({ ROOM_W / 2 + 0, ROOM_H - 50 + 0 * ROOM_H,32,16 }, COLLIDER_DUNGEON_DOWN, App->player);
	//room3_right = App->collisions->AddCollider({ ROOM_W - 50 + 0, ROOM_H / 2 + 1 * ROOM_H,16,32 }, COLLIDER_DUNGEON_RIGHT, App->player);
	//room4_left = App->collisions->AddCollider({ 50 + 1 * ROOM_W , ROOM_H / 2 + 1 * ROOM_H,16,32 }, COLLIDER_DUNGEON_LEFT, App->player);
	


	// Enemy Start
	

	/// LLISTA D'ENEMICS:
		// t_bluesoldier,
		// t_redsoldier,
		// t_greensoldier,
		// t_hinox,
		// t_boss_ballandchain,

	// ROOM 0x2
	AddEnemy(t_bluesoldier, 200, 124 + ROOM_H * 2);
	AddEnemy(t_bluesoldier, 800, 124 + ROOM_H * 2);
	AddEnemy(t_hinox, 500, 74 + ROOM_H * 2);
	// ROOM 0x1
	AddEnemy(t_greensoldier, 250, 74 + ROOM_H);
	AddEnemy(t_greensoldier, ROOM_W - 150, 74 + ROOM_H);
	// ROOM 0x0
	ChainBoss = AddEnemy(t_boss_ballandchain, 500, 120);
	// ROOM 1x1
	AddEnemy(t_greensoldier, 200 + ROOM_W, 75 + ROOM_H);
	AddEnemy(t_greensoldier, 200 + ROOM_W, 425 + ROOM_H);
	AddEnemy(t_redsoldier, 800 + ROOM_W, 75 + ROOM_H);
	AddEnemy(t_redsoldier, 850 + ROOM_W, 425 + ROOM_H);

	for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
		it._Ptr->_Myval->active = true;
	}

	// Block Start
	// ROOM 0x1
	// PUZZLE 0x1 01
	AddItem(heart_container, 75 + 32 * 2, 65 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 0,     65 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 1 + 1, 65 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 3 + 3, 65 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 4 + 4, 65 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 1 + 1, 65 + 32 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 2 + 2, 65 + 32 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 3 + 3, 65 + 32 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 0,     65 + 32 * 2 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 4 + 4, 65 + 32 * 2 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 1 + 1, 65 + 32 * 3 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 2 + 2, 65 + 32 * 3 + ROOM_H * 1);
	AddBlock(slabs, 75 + 32 * 3 + 3, 65 + 32 * 3 + ROOM_H * 1);

	// Items Start

	//Item* new_item = nullptr;
	//
	//new_item = App->entitymanager->CreateItem(drop_tenrupee);
	//new_item->SetPositions({ 300.0f, 300.0f });
	//items.push_back(new_item);
	
	/// LLISTA DE OBJECTES:
		//power_gauntlet,
		//pegasus_boots,
		//heart_container,
		//drop_heart,
		//drop_bomb,
		//drop_potion,
		//drop_rupee,
		//drop_fiverupee,
		//drop_tenrupee,
		//weapon_sword,
		//weapon_bow,



	//we can do that with an iterator that recieves the positions readed from the xml file


	//App->render->camera.x = 0;
	//App->render->camera.y = -ROOM_H * 3;

	App->player->SetPos(500, 400 + ROOM_H * 3);
	App->player->room = { 0 , 3 };

	App->player->room = { (int)trunc(App->player->pos.x / ROOM_W), (int)trunc(App->player->pos.y / ROOM_H) };
	App->audio->PlayMusic("Audio/Music/Song_of_Storms.ogg");
	App->audio->SetVolumeMusic(60);

	follow_cam = false;
	//App->render->cam_travel = true;
	//App->render->camera = { 0, 0 };
	return true;
}

// Called each loop iteration
bool DungeonScene::PreUpdate()
{
	// debug pathfing ------------------
	if (App->debug == true) {
		static iPoint origin;
		static bool origin_selected = false;

		int x, y;
		App->input->GetMousePosition(x, y);
		iPoint p = App->render->ScreenToWorld(x, y);
		p = App->map->WorldToMap(p.x, p.y);

		//if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		//{
		//	if (origin_selected == true)
		//	{
		//		App->pathfinding->CreatePath(origin, p);
		//		origin_selected = false;
		//	}
		//	else
		//	{
		//		origin = p;
		//		origin_selected = true;
		//	}
		//}
	}
	return true;
}

// Called each loop iteration
bool DungeonScene::Update(float dt)
{

	DoorUpdate(dt);

	//if (App->render->cam_travel == true) {
	//	if (-App->render->camera.y >= (App->player->room.y) * ROOM_H) {
	//		App->render->cam_travel = false;
	//	}
	//	else
	//		App->render->camera.y -= 5;
	//}
	//else
	//	for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
	//		it._Ptr->_Myval->active = true;
	//	}

	if (chain_boss_defeated == false && IsEnemy(ChainBoss) == false)
		chain_boss_defeated = true;

	if (chain_boss_defeated == false) {
		if (IsInside(App->player->link_coll->rect, { 0, 0, ROOM_W, ROOM_H }) == true) {
			
			if (chain_boss_defeated == false)
				ChainBoss_dw->open = false;
			else
				ChainBoss_dw->open = true;

			if (boss_music == false) {
				App->audio->PlayMusic("Audio/Music/Hyrule_Castle.ogg");
				boss_music = true;
			}

			if (chain_boss_defeated == true && boss_music == true) {
				App->audio->PlayMusic("");
				boss_music = false;
			}

				boss_minions_spawn_time.Start();
				boss_minions_spawn_time.SetFlag(true);
				if (boss_minions_spawn_time.ReadSec() >= 5) {
					AddEnemy(t_greensoldier, 150, 150);
					AddEnemy(t_greensoldier, 850, 150);
					boss_minions_spawn_time.SetFlag(false);
				}
		}
		else {
			if (boss_music == true) {
				App->audio->PlayMusic("Audio/Music/Song_of_Storms.ogg");
				boss_music = false;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;
	 
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		//App->render->cam_travel = true;
		App->scene_manager->toChangeScene(App->scene_manager->shop_scene);
	}

	App->map->Draw();

	return true;

}

// Called each loop iteration
bool DungeonScene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
		ESC = true;
	}

	if (ESC == true) {
		this->CleanUp();
	}

	return ret;
}

bool DungeonScene::CleanUp()
{
		LOG("DUNGEON CLEANUP");
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

		if (ChainBoss_dw != nullptr) {
			ChainBoss_dw->CleanUp();
			RELEASE(ChainBoss_dw);
		}

		if (ChainBoss != nullptr) {
			ChainBoss->CleanUp();
			RELEASE(ChainBoss)
		}

		return true;

}
