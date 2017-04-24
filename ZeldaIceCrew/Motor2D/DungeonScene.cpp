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
	
	AddRoom(0, 0);
	AddRoom(0, 1);
	AddRoom(0, 2);
	AddRoom(0, 3);
	AddRoom(1, 1);

	Scene::AddDungeonDoorway(Direction::Up, 0, 3); 
	Scene::AddDungeonDoorway(Direction::Down, 0, 2); 
	Scene::AddDungeonDoorway(Direction::Up, 0, 2); 
	Scene::AddDungeonDoorway(Direction::Down, 0, 1); 
	Scene::AddDungeonDoorway(Direction::Up, 0, 1); 
	ChainBoss_dw = Scene::AddDungeonDoorway(Direction::Down, 0, 0); 
	Scene::AddDungeonDoorway(Direction::Right, 0, 1); 
	Scene::AddDungeonDoorway(Direction::Left, 1, 1);

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
	AddEnemy(t_bluesoldier, 0, 2, 200, 124);
	AddEnemy(t_bluesoldier, 0, 2, 800, 124);
	AddEnemy(t_hinox,		0, 2, 500, 74);
	// ROOM 0x1
	AddEnemy(t_greensoldier, 0, 1, 250, 74);
	AddEnemy(t_greensoldier, 0, 1, ROOM_W - 150, 74);
	// ROOM 0x0
	ChainBoss = AddEnemy(t_boss_ballandchain, 0, 0, 500, 120);
	// ROOM 1x1
	AddEnemy(t_greensoldier, 1, 1, 200, 75);
	AddEnemy(t_greensoldier, 1, 1, 200, 425);
	AddEnemy(t_redsoldier, 1, 1,   800, 75);
	AddEnemy(t_redsoldier, 1, 1,   850, 425);

	AllEnemyActive(false);

	// Block Start
	// ROOM 0x1
	// PUZZLE 0x1 01
	AddItem(heart_container, 0, 1,	75 + 32 * 2, 65);
	AddBlock(slabs,	0, 1, 75 + 32 * 0,     65);
	AddBlock(slabs,	0, 1, 75 + 32 * 1 + 1, 65);
	AddBlock(slabs,	0, 1, 75 + 32 * 3 + 3, 65);
	AddBlock(slabs,	0, 1, 75 + 32 * 4 + 4, 65);
	AddBlock(slabs,	0, 1, 75 + 32 * 1 + 1, 65 + 32);
	AddBlock(slabs,	0, 1, 75 + 32 * 2 + 2, 65 + 32);
	AddBlock(slabs,	0, 1, 75 + 32 * 3 + 3, 65 + 32);
	AddBlock(slabs,	0, 1, 75 + 32 * 0,     65 + 32 * 2);
	AddBlock(slabs,	0, 1, 75 + 32 * 4 + 4, 65 + 32 * 2);
	AddBlock(slabs,	0, 1, 75 + 32 * 1 + 1, 65 + 32 * 3);
	AddBlock(slabs,	0, 1, 75 + 32 * 2 + 2, 65 + 32 * 3);
	AddBlock(slabs,	0, 1, 75 + 32 * 3 + 3, 65 + 32 * 3);

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
bool DungeonScene::Update(float dt)
{
	stdUpdate(dt);

	if (chain_boss_defeated == false && IsEnemy(ChainBoss) == false)
		chain_boss_defeated = true;

	if (chain_boss_defeated == false) {
		if (GetRoom(0, 0)->PlayerInside() == true) {
			
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
					GetRoom(0, 0)->AddEnemy(t_greensoldier, 150, 150);
					GetRoom(0, 0)->AddEnemy(t_greensoldier, 850, 150);
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

	return true;

}