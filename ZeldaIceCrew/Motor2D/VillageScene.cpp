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

	App->render->cam_travel = false;

	if (App->map->Load("Overworld.tmx") == true)
	{
		// int w, h;
		//uchar* data = NULL;
		//if (App->map->CreateWalkabilityMap(w, h, &data))
		//	App->pathfinding->SetMap(w, h, data);
		//
		//RELEASE_ARRAY(data);
	}
	//Bush_Rect = { 8*32,2*32,32,32 };
	debug_tex = App->tex->Load("maps/Exteriors.png"); /// CHANGE THIS TO PROPER SPRITESHEET DON'T CHARGE FROM MAPS TEXTURE
	//Colliders
	//Scene::AddDoorway(dw_overworld, Direction::Up, 40 * 16, 6 * 16);//dungeon doorway
	//Scene::AddDoorway(dw_overworld, Direction::Right, 55 * 16, 50 * 16);//shop doorway
	//Scene::AddDoorway(dw_overworld, Direction::Down, 23 * 16, 106 * 16);//house doorway
	to_house_coll = App->collisions->AddCollider({ 23 * 16,106 * 16,32,16 }, COLLIDER_TO_HOUSE, App->player);
	to_dungeon_coll = App->collisions->AddCollider({ 40 * 16,6 * 16,32,16 }, COLLIDER_TO_DUNGEON, App->player);
	to_shop_coll = App->collisions->AddCollider({ 55 * 16,50 * 16,32,16 }, COLLIDER_TO_SHOP, App->player);

	App->render->CamBoundOrigin();

	App->render->ScaleCamBoundaries(300);

	// Enemy Start
	//Enemy* new_enemy = nullptr;
	//new_enemy = App->entitymanager->CreateEnemy(t_boss_ballandchain);
	//new_enemy->pos = { 600, 300 };
	
	//enemies.push_back(new_enemy);
	//
	//new_enemy = App->entitymanager->CreateEnemy(RedSoldier);
	//new_enemy->pos = { 250, 300 };
	//
	//enemies.push_back(new_enemy);
	//
	//new_enemy = App->entitymanager->CreateEnemy(GreenSoldier);
	//new_enemy->pos = { 200, 300 };
	//
	//enemies.push_back(new_enemy);


	// Items Start

	//Item* new_item = nullptr;
	//
	//new_item = App->entitymanager->CreateItem(drop_tenrupee);
	//new_item->SetPositions({ 300.0f, 300.0f });
	//items.push_back(new_item);
	//
	//new_item = App->entitymanager->CreateItem(pegasus_boots);
	//new_item->SetPositions({ 450.0f, 300.0f });
	//new_item->SetPrice(20);
	//items.push_back(new_item);
	//
	//new_item = App->entitymanager->CreateItem(heart_container);
	//new_item->SetPositions({ 550.0f, 300.0f });
	//items.push_back(new_item);
	//
	//new_item = App->entitymanager->CreateItem(drop_rupee);
	//new_item->SetPositions({ 600.0f, 300.0f });
	//items.push_back(new_item);
	//
	//new_item = App->entitymanager->CreateItem(drop_fiverupee);
	//new_item->SetPositions({ 650.0f, 300.0f });
	//items.push_back(new_item);
	//
	//new_item = App->entitymanager->CreateItem(weapon_sword);
	//new_item->SetPositions({ 700.0f, 300.0f });
	//items.push_back(new_item);

	//we can do that with an iterator that recieves the positions readed from the xml file
	
	follow_cam = true;

	App->audio->PlayMusic("Audio/Music/Forest_Theme.ogg");
	App->audio->SetVolumeMusic(60);


	return true;
}

// Called each loop iteration
bool VillageScene::PreUpdate()
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
bool VillageScene::Update(float dt)
{

	//App->render->SetCamPos( 0, -(App->player->GetPos().y - App->render->camera.h / 2));

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;

	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		App->render->cam_travel = true;
		App->scene_manager->ChangeScene(App->scene_manager->dungeon_scene);
	}

	App->map->Draw();

	//for (int i = 0; i < Bushes.size(); i++) {
	////	App->render->Blit(Bushes[i]->GetTexture(), Bushes[i]->pos.x, Bushes[i]->pos.y, &Bushes[i]->GetRect());
	//
	//}
	
		return true;
	
}

// Called each loop iteration
bool VillageScene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
		ESC = true;
	}

	return ret;
}
bool VillageScene::CleanUp()
{
	App->collisions->EraseCollider(to_house_coll);
	App->collisions->EraseCollider(to_dungeon_coll);
	App->collisions->EraseCollider(to_shop_coll);

	App->map->CleanUp();

	if (items.empty() == false) {
		for (std::list<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				App->entitymanager->DestroyEnity((*it));
		}
		items.clear();
	}
	if (this->enemies.empty() == false) {
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

	/*if (doorways.empty() == false) {
		for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr)
				it._Ptr->_Myval->CleanUp();
			//RELEASE(*it);
		}
		doorways.clear();
	}*/
	return true;
}

