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
#include "j1Scene.h"
#include "j1Fonts.h"
#include "j1Player.h"

#define MAX_TABS 2

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	
	if (App->map->Load("FirstMap.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	Bush_Rect = { 8*32,2*32,32,32 };
	House_Rect = {0,0,195,195};
	debug_tex = App->tex->Load("maps/Exteriors.png"); /// CHANGE THIS TO PROPER SPRITESHEET DON'T CHARGE FROM MAPS TEXTURE

	App->player->SetPosTile(2, 2);

	App->render->CamBoundOrigin();

	App->render->ScaleCamBoundaries(300);

	// Enemy Start
	Enemy* new_enemy;
	new_enemy = App->entitymanager->CreateEnemy(BlueSoldier);
	new_enemy->pos = { 20, 20 };

	enemies.push_back(new_enemy);

	new_enemy = App->entitymanager->CreateEnemy(RedSoldier);
	new_enemy->pos = { 60, 30 };

	enemies.push_back(new_enemy);

	new_enemy = App->entitymanager->CreateEnemy(GreenSoldier);
	new_enemy->pos = { 200, 10 };

	enemies.push_back(new_enemy);


	// Items Start

	Item* new_item = nullptr;

	new_item = App->entitymanager->CreateItem(drop_tenrupee);
	new_item->SetPositions({ 300.0f, 50.0f });
	items.push_back(new_item);

	new_item = App->entitymanager->CreateItem(pegasus_boots);
	new_item->SetPositions({ 450.0f, 50.0f });
	items.push_back(new_item);
	///////////////////////////////////
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 470.0f, 50.0f });
	items.push_back(new_item);				  
											 
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 490.0f, 50.0f });
	items.push_back(new_item);				 
											 
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 510.0f, 50.0f });
	items.push_back(new_item);				  
											  
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 530.0f, 50.0f });
	items.push_back(new_item);				 
											 
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 550.0f, 50.0f });
	items.push_back(new_item);				  
											  
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 570.0f, 50.0f });
	items.push_back(new_item);				 
											  
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 590.0f, 50.0f });
	items.push_back(new_item);				  
											  
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 610.0f, 50.0f });
	items.push_back(new_item);				  
											  
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 630.0f, 50.0f });
	items.push_back(new_item);				  
											  
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 650.0f, 50.0f });
	items.push_back(new_item);				 
											  
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 670.0f, 50.0f });
	items.push_back(new_item);				  
											  
	new_item = App->entitymanager->CreateItem(power_gauntlet);
	new_item->SetPositions({ 690.0f, 50.0f });
	items.push_back(new_item);

	//////////////////////////////////
	new_item = App->entitymanager->CreateItem(heart_container);
	new_item->SetPositions({ 550.0f, 50.0f });
	items.push_back(new_item);

	new_item = App->entitymanager->CreateItem(drop_rupee);
	new_item->SetPositions({ 600.0f, 50.0f });
	items.push_back(new_item);

	new_item = App->entitymanager->CreateItem(drop_fiverupee);
	new_item->SetPositions({ 650.0f, 50.0f });
	items.push_back(new_item);


	//we can do that with an iterator that recieves the positions readed from the xml file


	App->player->SetPos(500, 100);
	


	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
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
bool j1Scene::Update(float dt)
{
	
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;

	App->map->Draw();

	for (int i = 0; i < Bushes.size(); i++) {
		App->render->Blit(Bushes[i]->GetTexture(), Bushes[i]->pos.x, Bushes[i]->pos.y, &Bushes[i]->GetRect());

	}
	
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
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


