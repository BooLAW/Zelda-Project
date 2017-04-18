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
	Doorway* dw = nullptr;
	dw = AddDoorway(dw_scene, Up, 23 * 16, 106 * 16);
	dw->SetTarget((Scene*)App->scene_manager->house_scene);
	dw->target_pos = {6'5 * 32, 8 * 32 };

	dw = AddDoorway(dw_scene, Up, 39 * 16, 6 * 16);
	dw->SetTarget((Scene*)App->scene_manager->dungeon_scene);
	dw->target_pos = { 500, 400 + ROOM_H * 3 };

	dw = AddDoorway(dw_scene, Up, 54 * 16, 50 * 16);
	dw->SetTarget((Scene*)App->scene_manager->shop_scene);
	dw->target_pos = { 8 * 32, 8 * 32 };

	///App->render->CamBoundOrigin();

	App->render->ScaleCamBoundaries(300);
	
	follow_cam = true;

	App->audio->PlayMusic("Audio/Music/Forest_Theme.ogg");
	App->audio->SetVolumeMusic(60);


	return true;
}

// Called each loop iteration
bool VillageScene::PreUpdate()
{

	follow_cam = true;
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

	DoorUpdate(dt);

	//App->render->SetCamPos( 0, -(App->player->GetPos().y - App->render->camera.h / 2));

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;

	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		//App->render->cam_travel = true;
		App->scene_manager->toChangeScene(App->scene_manager->dungeon_scene);
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

