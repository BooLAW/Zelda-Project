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

	scenes.push_back(village_scene);
	scenes.push_back(house_scene);

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
	if (current_scene != nullptr)
		ret = current_scene->CleanUp();

	return ret;
}

void SceneManager::ChangeScene(Scene * new_scene)
{
	LOG("Changing current scene");

	Scene* prev_scene = current_scene;
	current_scene = new_scene;
	prev_scene->CleanUp();
	current_scene->Start();
}

Scene * SceneManager::GetCurrentScene()
{
	return current_scene;
}
