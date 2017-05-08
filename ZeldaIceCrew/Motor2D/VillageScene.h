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
	// Called each loop iteration
	bool Update(float dt);
public:
	bool to_house = false;
	bool to_dungeon = false;
	bool to_shop = false;
private:
	bool ESC = false;
	SDL_Texture* debug_tex;
	
	bool round02 = false;

};

#endif // __j1SCENE_H__