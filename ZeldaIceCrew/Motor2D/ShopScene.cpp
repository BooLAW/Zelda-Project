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
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	Scene::AddDoorway(dw_shop, Direction::Down, 14 * 16, 20 * 16);

	App->player->SetPosTile(10, 10);

	App->render->CamBoundOrigin();

	App->render->ScaleCamBoundaries(300);

	App->audio->PlayMusic("Audio/Music/Shop.ogg");

	// Enemy Start

	// Items Start

	//we can do that with an iterator that recieves the positions readed from the xml file

	App->render->camera.x = 0;
	App->render->camera.y = 0;



	return true;
}

// Called each loop iteration
bool ShopScene::PreUpdate()
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
bool ShopScene::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
		App->scene_manager->ChangeScene(App->scene_manager->village_scene);

	App->map->Draw();
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
		App->player->curr_life_points -= 1;
	}
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

// Called before quitting
bool ShopScene::CleanUp()
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