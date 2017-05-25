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
#include "DungeonScene.h"
#include "Main_Screen.h"
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

	CA_tex = App->tex->Load("Sprites/rain_and_circle.png");
	CA_Rect[0] = { 5, 3911,		1039, 895 };
	CA_Rect[1] = { 1059, 3911,	1039, 895 };
	CA_Rect[2] = { 5, 4829,		1039, 895 };
	CA_Rect[3] = { 1059, 4829,	1039, 895 };
	CA_Rect[4] = { 5, 5747,		1039, 895 };
	CA_Rect[5] = { 1059, 5747,	1039, 895 };
	CA_Rect[6] = { 5, 6679,		1039, 895 };
	CA_Rect[7] = { 1059, 6679,	1039, 895 };

	ChangeAnimation.PushBack(CA_Rect[0]);
	ChangeAnimation.PushBack(CA_Rect[1]);
	ChangeAnimation.PushBack(CA_Rect[2]);
	ChangeAnimation.PushBack(CA_Rect[3]);
	ChangeAnimation.PushBack(CA_Rect[4]);
	ChangeAnimation.PushBack(CA_Rect[5]);
	ChangeAnimation.PushBack(CA_Rect[6]);
	ChangeAnimation.PushBack(CA_Rect[7]);

	ChangeAnimation.speed = 0.2;
	ChangeAnimation.loop = false;

	// Create scenes
	village_scene = new VillageScene();
	dungeon_scene = new DungeonScene();
	main_screen = new Main_Screen();

	village_scene->curr_id = village;
	dungeon_scene->curr_id = dungeon;
	main_screen->curr_id = mainscreen;
	scenes.push_back(village_scene);
	scenes.push_back(dungeon_scene);
	scenes.push_back(main_screen);
	// -------------

	current_scene = main_screen;

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

	/*if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;*/


	return ret;
}

// Called before quitting
bool SceneManager::CleanUp()
{
	LOG("Freeing scene");

	bool ret = false;

	if(CA_tex != nullptr)
		App->tex->UnLoad(CA_tex);

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
	ChangeAnimation.Reset();
	App->particle->DestroyParticles();
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

Scene * SceneManager::SetCurrentScene(Scene* new_scene)
{
	current_scene = new_scene;
	return current_scene;
}
