#pragma once
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "j1Module.h"
#include "j1Gui.h"
#include "Scene.h"

struct SDL_Texture;
class VillageScene;
class HouseScene;
//add the forward declaration for each new scene


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

	// Change scene
	void ChangeScene(Scene* new_scene);
	Scene* GetCurrentScene();

public:
	VillageScene*					 village_scene = nullptr;//we need to change the name to villageScene
	HouseScene*					 house_scene = nullptr;
private:
	std::list<Scene*>				 scenes;
	Scene*						 current_scene = nullptr;

};

#endif // __SCENEMANAGER_H__
