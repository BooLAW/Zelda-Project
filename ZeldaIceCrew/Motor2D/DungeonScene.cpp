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

	if (App->map->Load("Dungeon.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	//Bush_Rect = { 8*32,2*32,32,32 };
	App->player->SetPosTile(2, 2);

	App->render->CamBoundOrigin();

	App->render->ScaleCamBoundaries(300);
	//Door Colliders
		//Boss room
	boss_door = App->collisions->AddCollider({ 32 * 16,32 * 16,32,10 }, COLLIDER_DUNGEON_DOWN, App->scene_manager);

	// Enemy Start


	// Items Start


	//we can do that with an iterator that recieves the positions readed from the xml file


	App->player->SetPos(500, 100);



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
bool DungeonScene::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
		App->scene_manager->ChangeScene(App->scene_manager->shop_scene);

	if (up == true)
	{
		App->render->camera.y += 1024;
	//	App->render->culling_cam.y += 1024;
		up = false;
	}
	if (down == true)
	{
		App->render->camera.y += 1024;
	//	App->render->culling_cam.y -= 1024;
		App->player->MovePos(500, 100);


		down = false;
	}
	if (right == true)
	{
		App->render->camera.x += 576;
	//	App->render->culling_cam.x += 576;

		right = false;
	}
	if (left == true)
	{
		App->render->camera.x -= 576;
	//	App->render->culling_cam.x -= 576;
		left = false;
	}
	App->map->Draw();

	//for (int i = 0; i < Bushes.size(); i++) {
	////	App->render->Blit(Bushes[i]->GetTexture(), Bushes[i]->pos.x, Bushes[i]->pos.y, &Bushes[i]->GetRect());
	//
	//}

	// Debug pathfinding ------------------------------
	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.size(),
		map_coordinates.x, map_coordinates.y);

	//int x, y;
	if (App->debug == true) {
		App->input->GetMousePosition(x, y);
		iPoint p = App->render->ScreenToWorld(x, y);
		p = App->map->WorldToMap(p.x, p.y);
		p = App->map->MapToWorld(p.x, p.y);
		App->win->SetTitle(title.GetString());
		//App->render->Blit(debug_tex, p.x, p.y);
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
		App->player->curr_life_points -= 1;
	}
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

	return ret;
}

// Called before quitting
bool DungeonScene::CleanUp()
{
	LOG("Freeing village scene");

	if (ESC != true)
	{
		App->map->CleanUp();

		for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
		{
			App->entitymanager->DestroyEnity(*it);
		}
		enemies.clear();
		for (std::list<Item*>::iterator it = items.begin(); it != items.end(); it++)
		{
			App->entitymanager->DestroyEnity(*it);
		}
		items.clear();

		if (debug_tex != NULL)
			App->tex->UnLoad(debug_tex);
	}



	return true;
}