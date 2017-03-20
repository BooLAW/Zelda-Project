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
#include "HouseScene.h"
#include "ModuleFadeToBlack.h"
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
	App->housescene->active = false;
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	
	if (App->map->Load("untitled.tmx") == true)
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
	//we can do that with an iterator that recieves the positions readed from the xml file
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(2, 17)));   
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(2, 18)));   
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(2, 19)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(3, 17)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(3, 18)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(3, 19)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(14, 17)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(15, 17)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(14, 18)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(15, 18)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(10, 4)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(11, 3)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(17, 3)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(19, 4)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(26, 21)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(26, 22)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(27, 22)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(27, 23)));
	Bushes.push_back(App->entitymanager->CreateEntity(bush, debug_tex, Bush_Rect, App->map->MapToWorld(28, 23)));
	House = (App->entitymanager->CreateEntity(bush, nullptr, House_Rect, App->map->MapToWorld(9, 11)));


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
		App->render->Blit(Bushes[i]->tex, Bushes[i]->pos.x, Bushes[i]->pos.y, &Bushes[i]->rect);

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
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		App->fadetoblack->FadeToBlack(App->scene, App->housescene);
	}
		
	

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	App->tex->UnLoad(debug_tex);
	App->collisions->CleanUp();


	App->player->Disable();
	App->map->Disable();	
	
	return true;
}
