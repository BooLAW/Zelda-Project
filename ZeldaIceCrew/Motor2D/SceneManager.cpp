#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Module.h"
#include "j1Render.h"
#include "j1Window.h"
#include "SceneManager.h"
#include "VillageScene.h"
#include "HouseScene.h"
#include "DungeonScene.h"
#include "ShopScene.h"

#define NUMBER_OF_PLAYERS 4

SceneManager::SceneManager() : j1Module()
{
	name = "SceneManager";
}

// Destructor
SceneManager::~SceneManager()
{

}

// Called before render is available
bool SceneManager::Awake()
{
	bool ret = true;

	LOG("Loading SceneManager");

	return ret;
}

// Called before the first frame
bool SceneManager::Start()
{
	bool ret = false;

	LOG("Start module scene");

	// Create scenes
	village_scene = new VillageScene();
	house_scene = new HouseScene();
	dungeon_scene = new DungeonScene();
	shop_scene = new ShopScene();

	scenes.push_back(village_scene);
	scenes.push_back(house_scene);
	scenes.push_back(dungeon_scene);
	scenes.push_back(shop_scene);

	// -------------

	current_scene = house_scene;

	if (current_scene != nullptr)
		ret = current_scene->Start();

	return ret;
}

// Called each loop iteration
bool SceneManager::PreUpdate()
{
	bool ret = false;

	if (to_change_scene == true) {

		if(target != nullptr)
			ChangeScene(target);

		target = nullptr;
		to_change_scene = false;
	}

	if (current_scene != nullptr)
		ret = current_scene->PreUpdate();

	return ret;
}

// Called each loop iteration
bool SceneManager::Update(float dt)
{
	bool ret = false;

	if (current_scene != nullptr)
		ret = current_scene->Update(dt);

	return ret;
}

// Called each loop iteration
bool SceneManager::PostUpdate()
{
	bool ret = false;

	if (current_scene != nullptr)
		ret = current_scene->PostUpdate();

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneManager::CleanUp()
{
	LOG("Freeing scene");

	bool ret = false;

	for (std::list<Scene*>::iterator it = scenes.begin(); it != scenes.end(); it++) {
		if((*it) != nullptr) 
			it._Ptr->_Myval->CleanUp();
		RELEASE(it._Ptr->_Myval);
	}

	scenes.clear();

	//if (current_scene != nullptr)
	//	ret = current_scene->CleanUp();

	current_scene = nullptr;

	return ret;
}

bool SceneManager::LoadRooms(const char * file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.c_str(), file_name);

	char* buf;
	int size = App->fs->Load(tmp.GetString(), &buf);
	pugi::xml_parse_result result = scene_file.load_buffer(buf, size);

	RELEASE(buf);
	return false;
}

void SceneManager::ChangeScene(Scene * new_scene)
{
	LOG("Changing current scene");
	App->render->cam_travel = false;
	Scene* prev_scene = current_scene;
	current_scene = new_scene;
	prev_scene->CleanUp();
	LOG("CLEANUP PREV");
	current_scene->Start();
	LOG("START NEXT");
}

Scene * SceneManager::GetCurrentScene()
{
	return current_scene;
}
