#ifndef __DUNGEON_SCENE_H__
#define __DUNGEON_SCENE_H__

#include "j1Module.h"
#include "EntityManager.h"
#include <vector>
#include "Scene.h"
#include "j1Gui.h"

struct SDL_Texture;
//UI forward declarations
class Image;
class Label;
class Text_Box;
class Button;
class Window;
class Selector;
class Windowed_Image;
class Main_Screen : public Scene
{
public:

	Main_Screen();

	// Destructor
	virtual ~Main_Screen();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	UIElement* Next();
	UIElement* Prev();

private:

	std::list<UIElement*> ui_elements;
	UIElement* selected;

};

#endif //__Main_Screen_H__

