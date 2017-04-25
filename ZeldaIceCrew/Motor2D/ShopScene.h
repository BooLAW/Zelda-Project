#pragma once
#ifndef __SHOPSCENE_H__
#define __SHOPSCENE_H__

#include "EntityManager.h"
#include <vector>
#include "j1Gui.h"
#include "Scene.h"
struct SDL_Texture;
//UI forward declarations

class ShopScene : public Scene
{
public:

	ShopScene();

	// Destructor
	virtual ~ShopScene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

public:
	bool to_overworld_shop = false;
private:
	Collider* to_overworld_coll = nullptr;

	bool ESC = false;
	SDL_Texture* debug_tex;
	//std::vector<Entity*> Bushes;
	//SDL_Rect Bush_Rect
};

#endif // __j1SCENE_H__
