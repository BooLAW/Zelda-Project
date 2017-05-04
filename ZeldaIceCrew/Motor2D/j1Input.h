#ifndef __j1INPUT_H__
#define __j1INPUT_H__

#include "j1Module.h"

//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;

enum Controls {
	UP = 0,
	DOWN,
	RIGHT,
	LEFT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	ACTION,
	MENU,
	WPN_NEXT,
	WPN_PREV,
	__LAST_CONTROLS
};

enum j1EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum j1KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum Modules {
	j1Window_ = 0,
	j1Input_,
	j1Render_,
	j1Textures_,
	j1Audio_,
	j1FileSystem_,
	SceneManager_,
	j1Map_,
	j1PathFinding_,
	j1Fonts_,
	j1Gui_,
	j1Collision_,
	HUD_,
	j1Player_,
	EntityManager_,
	ModuleParticles_,
	DialogManager_,

	last_module_
};

enum Pause_Type {

	General_ = 0,
	Inventory_,

	last_pause_type_

};


class j1Input : public j1Module
{

public:

	j1Input();

	// Destructor
	virtual ~j1Input();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called before quitting
	bool CleanUp();

	// Gather relevant win events
	bool GetWindowEvent(j1EventWindow ev);

	// Check key states (includes mouse and joy buttons)
	j1KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	j1KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);
	std::string GetString();
	void DefaultControls();
	int controls [__LAST_CONTROLS];
	
	//Pause things
	void Start_Pause(Pause_Type type);
	void Stop_Pause(Pause_Type type);
	void Init_Pause_Matrix();

	bool pause_matrix[last_module_][last_pause_type_];
	bool pause2[last_pause_type_];
private:

	bool		windowEvents[WE_COUNT];
	j1KeyState*	keyboard;
	j1KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	int			mouse_motion_x;
	int			mouse_motion_y;
	int			mouse_x;
	int			mouse_y;
	std::string   text;
};

#endif // __j1INPUT_H__