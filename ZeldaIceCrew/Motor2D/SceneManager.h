#pragma once
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "j1Module.h"
#include "j1Gui.h"
#include "Scene.h"
#include "j1FileSystem.h"

struct SDL_Texture;
class VillageScene;
class HouseScene;
class DungeonScene;
class ShopScene;
//add the forward declaration for each new scene

class Scene;
class Main_Screen;
class SceneManager : public j1Module
{
public:

	SceneManager();

	// Destructor
	virtual ~SceneManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool LoadRooms(const char* file_name);

	// Change scene
	void ChangeScene(Scene* new_scene);
	void toChangeScene(Scene* new_scene) {
		to_change_scene = true;
		target = new_scene;
	}
	Scene* GetCurrentScene();
	Scene* SetCurrentScene();


public:
	bool to_change_scene = false;
	Scene* target = nullptr;

	VillageScene*					village_scene = nullptr;//we need to change the name to villageScene
	HouseScene*						house_scene = nullptr;
	DungeonScene*					dungeon_scene = nullptr;
	ShopScene*						shop_scene = nullptr;
	Main_Screen*					main_screen = nullptr;
private:
	pugi::xml_document	scene_file;
	std::string			folder;
	std::list<Scene*>				 scenes;
	Scene*							 current_scene = nullptr;

};					


#endif // __SCENEMANAGER_H__
