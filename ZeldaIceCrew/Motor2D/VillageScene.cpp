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
#include "DungeonScene.h"

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

	if (App->map->Load("Village.tmx") == true)
	{
		// int w, h;
		//uchar* data = NULL;
		//if (App->map->CreateWalkabilityMap(w, h, &data))
		//	App->pathfinding->SetMap(w, h, data);
		//
		//RELEASE_ARRAY(data);
	}
	//debug_tex = App->tex->Load("maps/Exteriors.png"); /// CHANGE THIS TO PROPER SPRITESHEET DON'T CHARGE FROM MAPS TEXTURE
	//Colliders

	AddRoom(0, 0, 1024, 5000);

	//Doorway* dw = nullptr;
	//dw = AddDoorway(dw_scene, 0, 0, Up, 23 * 16, 106 * 16);
	//dw->SetTarget((Scene*)App->scene_manager->house_scene);
	//dw->target_pos = {6'5 * 32, 8 * 32 };
	//
	//dw = AddDoorway(dw_scene, 0, 0, Up, 39 * 16, 6 * 16);
	//dw->SetTarget((Scene*)App->scene_manager->dungeon_scene);
	//dw->target_pos = { 500, 400 + ROOM_H * 3 };
	//
	//dw = AddDoorway(dw_scene, 0, 0, Up, 54 * 16, 50 * 16);
	//dw->SetTarget((Scene*)App->scene_manager->shop_scene);
	//dw->target_pos = { 8 * 32, 8 * 32 };

	///App->render->CamBoundOrigin();

	App->render->ScaleCamBoundaries(300);
	
	follow_cam = true;

	App->audio->PlayMusic("Audio/Music/Forest_Theme.ogg");
	App->audio->SetVolumeMusic(60);
	
	return true;
};