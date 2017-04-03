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

	if (App->map->Load("House.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	
	App->player->SetPos(6.5 * 32, 8 * 32);
	App->render->MoveCam(256, 128);
	App->render->ScaleCamBoundaries(300);
	
	//we can do that with an iterator that recieves the positions readed from the xml file
		overworld_door = App->collisions->AddCollider({ 13 * 16,20 * 16,32,10 }, COLLIDER_TO_OVERWORLD_HOUSE, App->scene_manager);
	

		App->audio->PlayMusic("Home.ogg");
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
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
		App->scene_manager->ChangeScene(App->scene_manager->dungeon_scene);
	
	if (to_overworld == true)
	{
		App->scene_manager->ChangeScene(App->scene_manager->village_scene);
		to_overworld = false;
	}

	App->map->Draw();

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

// Called before quitting
bool HouseScene::CleanUp()
{
	LOG("Freeing house scene");
	
	App->map->CleanUp();
	App->collisions->EraseCollider(overworld_door);

	return true;
}
