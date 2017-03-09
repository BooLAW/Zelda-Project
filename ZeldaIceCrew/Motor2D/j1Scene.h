#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
//UI forward declarations
class Image;
class Label;
class Text_Box;
class Button;
class Window;
class Selector;
class Windowed_Image;

class element {
public:
	SDL_Texture* texture = nullptr;
	PhysBody* physbody = nullptr;
	SDL_Rect box;
	iPoint position;
public:
	element() {}
	//call a constructure	
	element(SDL_Texture* texture, uint rect_x, uint rect_y, uint width, uint height, uint pos_x, uint pos_y)
	{
		(this)->texture = texture;
		box.x = rect_x;
		box.y = rect_y;
		box.w = width;
		box.h = height;
		position.x = pos_x;
		position.y = pos_y;
	}
	~element() {}
};
class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

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
	element* column1;

	Window* window;
	Label* win_title;
};

#endif // __j1SCENE_H__