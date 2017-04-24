#ifndef __HOUSE_SCENE_H__
#define __HOUSE_SCENE_H__

#include "j1Module.h"
#include "EntityManager.h"
#include <vector>
#include "Scene.h"

struct SDL_Texture;
//UI forward declarations
class Image;
class Label;
class Text_Box;
class Button;
class Window;
class Selector;
class Windowed_Image;
class HouseScene : public Scene
{
public:

	HouseScene();

	// Destructor
	virtual ~HouseScene();

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

	bool CleanUp();


public:
	bool to_overworld_house = false;
private:
	Collider* to_overworld_coll = nullptr;
	SDL_Texture* debug_tex;
//	std::vector<Entity*> Bushes;
//	SDL_Rect Bush_Rect;
	Entity* House;
	SDL_Rect House_Rect;
	
	Window* window;
	Label* win_title;

	////////////////////////

};

#endif

