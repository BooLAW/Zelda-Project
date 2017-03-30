#ifndef __VILLAGESCENE_H__
#define __VILLAGESCENE_H__

#include "EntityManager.h"
#include <vector>
#include "j1Gui.h"
#include "Scene.h"
struct SDL_Texture;
//UI forward declarations

class VillageScene : public Scene
{
public:

	VillageScene();

	// Destructor
	virtual ~VillageScene();

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

private:

	SDL_Texture* debug_tex;
	std::vector<Entity*> Bushes;
	SDL_Rect Bush_Rect;
public:
	std::list<Enemy*> enemies;
	std::list<Item*> items;




};

#endif // __j1SCENE_H__