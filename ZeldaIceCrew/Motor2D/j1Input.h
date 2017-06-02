#ifndef __j1INPUT_H__
#define __j1INPUT_H__

#include "j1Module.h"
#include "SDL/include/SDL.h"
#include "j1Player.h"
#include <vector>
//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
#define NUM_CONTROLLER_BUTTONS 15
#define MAX_GAMECONTROLLERS 1
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;
struct _SDL_GameController;

enum JOYSTICK_MOVES
{
	LEFTJOY_LEFT = 0,
	LEFTJOY_RIGHT,
	LEFTJOY_UP,
	LEFTJOY_DOWN,
	RIGHTJOY_LEFT,
	RIGHTJOY_RIGHT,
	RIGHTJOY_UP,
	RIGHTJOY_DOWN,
	LEFT_TRIGGER,
	RIGHT_TRIGGER,
	JOY_MOVES_NULL
};

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
	DASH,
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
	KEY_UP,
	j1KeyState_null
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

struct GamePad
{
	j1KeyState				gamecontroller_buttons[NUM_CONTROLLER_BUTTONS];
	uint					joystick_moves[JOY_MOVES_NULL];
	int						pad_num = -1;
	int						id = -1;
	_SDL_GameController*	pad = nullptr;
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
	const char* GetKeyString(SDL_Scancode scan)const ;
	// Check key states (includes mouse and joy buttons)
	j1KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	SDL_Scancode returnkey();

	j1KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}
	j1KeyState GetControllerButton(int pad, int id) const;

	// Return the motion value (form 0 to 32767) for a joystick direction

	uint GetControllerJoystickMove(int pad, int id) const;
	void AxisReaction(int pad, int axis, int value);
	void AddController(int id);
	void RemoveController(int id);

	void ConnectGamePad(int instanceID);
	void DisconectGamePad(int instanceID);
	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);
	std::string GetString();
	void DefaultControls();
	void PadDefaultControls();
	int controls [__LAST_CONTROLS];
	int pad_controls[__LAST_CONTROLS];

	
	//Pause things


	
private:

	bool		windowEvents[WE_COUNT];
	j1KeyState*	keyboard;
	j1KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	int			mouse_motion_x;
	int			mouse_motion_y;
	int			mouse_x;
	int			mouse_y;
	std::string   text;

	std::vector<GamePad*>	gamepads;
	int			connected_gamepads = 0;
	int			gamepad_connected[MAX_GAMECONTROLLERS];
};

#endif // __j1INPUT_H__