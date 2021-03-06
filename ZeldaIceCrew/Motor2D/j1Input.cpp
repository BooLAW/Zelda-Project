#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Window.h"



#define MAX_KEYS 300

j1Input::j1Input() : j1Module()
{
	name.create("input");

	keyboard = new j1KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(j1KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(j1KeyState) * NUM_MOUSE_BUTTONS);
	memset(gamepad_connected, -1, sizeof(int)*MAX_GAMECONTROLLERS);
}

// Destructor
j1Input::~j1Input()
{
	delete[] keyboard;
}

// Called before render is available
bool j1Input::Awake(pugi::xml_node& config)
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	// GUI -------------------------
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		LOG("Error on SDL_Init");
	// GameController --------------
	/// To use PS3 Controller install this driver https://github.com/nefarius/ScpToolkit/releases/tag/v1.6.238.16010
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0)
		LOG("Error on SDL_Init");
	if (SDL_Init(SDL_INIT_JOYSTICK) != 0)
		LOG("Error on SDL_Init JOYSTICK");

	return ret;
}

// Called before the first frame
bool j1Input::Start()
{
	SDL_StopTextInput();
	DefaultControls();
	return true;
}

// Called each loop iteration
bool j1Input::PreUpdate()
{
	if (App->input->connected_gamepads > 0) {
		if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
			if (dpad_p != c_idle)
				dpad_p = c_repeat;
			else
				dpad_p = c_pressed;
		}
		else {
			dpad_p = c_idle;
		}

		if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_A) || SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_B)) {
			if (mmenu_p != c_idle)
				mmenu_p = c_repeat;
			else
				mmenu_p = c_pressed;
		}
		else {
			mmenu_p = c_idle;
		}

		if (preset_1 == true) {
			if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_Y) || SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_B) || SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_A) || SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_X)) {
				if (ctrl_p != c_idle)
					ctrl_p = c_repeat;
				else
					ctrl_p = c_pressed;
			}
			else {
				ctrl_p = c_idle;
			}
		}
		else {
			if (SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 12000 || SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 12000) {
				if (ctrl_p != c_idle)
					ctrl_p = c_repeat;
				else
					ctrl_p = c_pressed;
			}
			else {
				ctrl_p = c_idle;
			}
		}
	}
	static SDL_Event event;
	
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for(int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if(mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if(mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}

	for (std::vector<GamePad*>::iterator it = gamepads.begin(); it != gamepads.end(); it++)
	{
		for (int i = 0; i < NUM_CONTROLLER_BUTTONS; ++i)
		{
			if ((*it)->gamecontroller_buttons[i] == KEY_DOWN)
				(*it)->gamecontroller_buttons[i] = KEY_REPEAT;

			if ((*it)->gamecontroller_buttons[i] == KEY_UP)
				(*it)->gamecontroller_buttons[i] = KEY_IDLE;
		}
	}


	while(SDL_PollEvent(&event) != 0)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				windowEvents[WE_QUIT] = true;
				break;

			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
					//case SDL_WINDOWEVENT_LEAVE:
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_FOCUS_LOST:
					windowEvents[WE_HIDE] = true;
					break;

					//case SDL_WINDOWEVENT_ENTER:
				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				case SDL_WINDOWEVENT_MAXIMIZED:
				case SDL_WINDOWEVENT_RESTORED:
					windowEvents[WE_SHOW] = true;
					break;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons[event.button.button - 1] = KEY_DOWN;
				//LOG("Mouse button %d down", event.button.button-1);
				break;

			case SDL_MOUSEBUTTONUP:
				mouse_buttons[event.button.button - 1] = KEY_UP;
				//LOG("Mouse button %d up", event.button.button-1);
				break;

			case SDL_MOUSEMOTION:
			{
				int scale = App->win->GetScale();
				mouse_motion_x = event.motion.xrel / scale;
				mouse_motion_y = event.motion.yrel / scale;
				mouse_x = event.motion.x / scale;
				mouse_y = event.motion.y / scale;
				//LOG("Mouse motion x %d y %d", mouse_motion_x, mouse_motion_y);
			}
			break;

			// GUI -------------------
			
			// ------------------------

			// GamePads Events --------
			case SDL_CONTROLLERDEVICEADDED:
			{
				AddController(event.cdevice.which);
				PadDefaultControls();
			}
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				RemoveController(event.cdevice.which);
				break;

			case SDL_CONTROLLERBUTTONDOWN:
			{
				for (std::vector<GamePad*>::iterator it = gamepads.begin(); it != gamepads.end(); it++)
				{
					if ((*it)->id == event.cbutton.which)
					{
						(*it)->gamecontroller_buttons[event.cbutton.button] = KEY_DOWN;
						break;
					}
				}
			}
			break;

			case SDL_CONTROLLERBUTTONUP:
			{
				for (std::vector<GamePad*>::iterator it = gamepads.begin(); it != gamepads.end(); it++)
				{
					if ((*it)->id == event.cbutton.which)
					{
						(*it)->gamecontroller_buttons[event.cbutton.button] = KEY_UP;
						break;
					}
				}
			}
			break;

			case SDL_CONTROLLERAXISMOTION:
			{
				AxisReaction(event.caxis.which, event.caxis.axis, event.caxis.value);
			}
			break;
			// ------------------------

			}
		}
	}

	return true;
}

// Called before quitting
bool j1Input::CleanUp()
{
	gamepads.clear();
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool j1Input::GetWindowEvent(j1EventWindow ev)
{
	return windowEvents[ev];
}

const char * j1Input::GetKeyString(SDL_Scancode scan) const
{
	return SDL_GetKeyName(SDL_GetKeyFromScancode(scan));
}

void j1Input::GetMousePosition(int& x, int& y)
{
	x = mouse_x;
	y = mouse_y;
}

void j1Input::GetMouseMotion(int& x, int& y)
{
	x = mouse_motion_x;
	y = mouse_motion_y;
}

std::string j1Input::GetString()
{
	std::string ret = text;
	text.shrink_to_fit();
	return ret;
}

void j1Input::DefaultControls()
{
	for (int i = 0; i < __LAST_CONTROLS; i++) {
		if (i == MOVE_UP) {
			controls[i] = SDL_SCANCODE_W;
		}
		if (i == MOVE_DOWN) {
			controls[i] = SDL_SCANCODE_S;
		}
		if (i == MOVE_RIGHT) {
			controls[i] = SDL_SCANCODE_D;
		}
		if (i == MOVE_LEFT) {
			controls[i] = SDL_SCANCODE_A;
		}
		if (i == UP) {
			controls[i] = SDL_SCANCODE_UP;
		}
		if (i == DOWN) {
			controls[i] = SDL_SCANCODE_DOWN;
		}
		if (i == RIGHT) {
			controls[i] = SDL_SCANCODE_RIGHT;
		}
		if (i == LEFT) {
			controls[i] = SDL_SCANCODE_LEFT;
		}
		if (i == ACTION) {
			controls[i] = SDL_SCANCODE_SPACE;
		}
		if (i == MENU) {
			controls[i] = SDL_SCANCODE_TAB;
		}
		if (i == WPN_NEXT) {
			controls[i] = SDL_SCANCODE_E;
		}
		if (i == WPN_PREV) {
			controls[i] = SDL_SCANCODE_Q;
		}
		if (i == DASH) {
			controls[i] = SDL_SCANCODE_RCTRL;
		}
	}
}
void j1Input::PadDefaultControls()
{
	if (App->player->controller_index != 0) {
		for (int i = 0; i < __LAST_CONTROLS; i++) {
			if (i == MOVE_UP) {
				controls[i] = SDL_CONTROLLER_BUTTON_DPAD_UP;
			}
			if (i == MOVE_DOWN) {
				controls[i] = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
			}
			if (i == MOVE_RIGHT) {
				controls[i] = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
			}
			if (i == MOVE_LEFT) {
				controls[i] = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
			}
			if (i == UP) {
				controls[i] = SDL_CONTROLLER_BUTTON_Y;
			}
			if (i == DOWN) {
				controls[i] = SDL_CONTROLLER_BUTTON_A;
			}
			if (i == RIGHT) {
				controls[i] = SDL_CONTROLLER_BUTTON_B;
			}
			if (i == LEFT) {
				controls[i] = SDL_CONTROLLER_BUTTON_X;
			}
			if (i == ACTION) {
				controls[i] = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
			}
			if (i == MENU) {
				controls[i] = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
			}
			if (i == WPN_NEXT) {
				controls[i] = SDL_SCANCODE_E;
			}
			if (i == WPN_PREV) {
				controls[i] = SDL_SCANCODE_Q;
			}
			if (i == DASH) {
				controls[i] = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
			}
		}
	}
}
SDL_Scancode j1Input::returnkey()
{

	if (GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
		return SDL_SCANCODE_Q;
	}
	else if (GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
		return SDL_SCANCODE_W;
	}
	else if (GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		return SDL_SCANCODE_E;
	}
	else if (GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
		return SDL_SCANCODE_R;
	}
	else if (GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
		return SDL_SCANCODE_T;
	}
	else if (GetKey(SDL_SCANCODE_Y) == KEY_DOWN) {
		return SDL_SCANCODE_Y;
	}
	else if (GetKey(SDL_SCANCODE_U) == KEY_DOWN) {
		return SDL_SCANCODE_U;
	}
	else if (GetKey(SDL_SCANCODE_I) == KEY_DOWN) {
		return SDL_SCANCODE_I;
	}
	else if (GetKey(SDL_SCANCODE_O) == KEY_DOWN) {
		return SDL_SCANCODE_O;
	}
	else if (GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		return SDL_SCANCODE_P;
	}
	else if (GetKey(SDL_SCANCODE_A) == KEY_DOWN) {
		return SDL_SCANCODE_A;
	}
	else if (GetKey(SDL_SCANCODE_S) == KEY_DOWN) {
		return SDL_SCANCODE_S;
	}
	else if (GetKey(SDL_SCANCODE_D) == KEY_DOWN) {
		return SDL_SCANCODE_D;
	}
	else if (GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
		return SDL_SCANCODE_F;
	}
	else if (GetKey(SDL_SCANCODE_G) == KEY_DOWN) {
		return SDL_SCANCODE_G;
	}
	else if (GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
		return SDL_SCANCODE_H;
	}
	else if (GetKey(SDL_SCANCODE_J) == KEY_DOWN) {
		return SDL_SCANCODE_J;
	}
	else if (GetKey(SDL_SCANCODE_K) == KEY_DOWN) {
		return SDL_SCANCODE_K;
	}
	else if (GetKey(SDL_SCANCODE_L) == KEY_DOWN) {
		return SDL_SCANCODE_L;
	}
	else if (GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
		return SDL_SCANCODE_Z;
	}
	else if (GetKey(SDL_SCANCODE_X) == KEY_DOWN) {
		return SDL_SCANCODE_X;
	}
	else if (GetKey(SDL_SCANCODE_C) == KEY_DOWN) {
		return SDL_SCANCODE_C;
	}
	else if (GetKey(SDL_SCANCODE_V) == KEY_DOWN) {
		return SDL_SCANCODE_V;
	}
	else if (GetKey(SDL_SCANCODE_B) == KEY_DOWN) {
		return SDL_SCANCODE_B;
	}
	else if (GetKey(SDL_SCANCODE_N) == KEY_DOWN) {
		return SDL_SCANCODE_N;
	}
	else if (GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
		return SDL_SCANCODE_M;
	}
	else if (GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) {
		return SDL_SCANCODE_TAB;
	}
	else if (GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
		return SDL_SCANCODE_UP;
	}
	else if (GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
		return SDL_SCANCODE_DOWN;
	}
	else if (GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
		return SDL_SCANCODE_RIGHT;
	}
	else if (GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
		return SDL_SCANCODE_LEFT;
	}
	else if (GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		return SDL_SCANCODE_1;
	}
	else if (GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		return SDL_SCANCODE_2;
	}
	else if (GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
		return SDL_SCANCODE_3;
	}
	else if (GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
		return SDL_SCANCODE_4;
	}
	else if (GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
		return SDL_SCANCODE_5;
	}
	else if (GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
		return SDL_SCANCODE_6;
	}
	else if (GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
		return SDL_SCANCODE_7;
	}
	else if (GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
		return SDL_SCANCODE_8;
	}
	else if (GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
		return SDL_SCANCODE_9;
	}
	else if (GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		return SDL_SCANCODE_SPACE;
	}
	else if (GetKey(SDL_SCANCODE_RSHIFT) == KEY_DOWN) {
		return SDL_SCANCODE_RSHIFT;
	}
	else if (GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN) {
		return SDL_SCANCODE_LSHIFT;
	}
	else if (GetKey(SDL_SCANCODE_RCTRL) == KEY_DOWN) {
		return SDL_SCANCODE_RCTRL;
	}
	else if (GetKey(SDL_SCANCODE_LCTRL) == KEY_DOWN) {
		return SDL_SCANCODE_LCTRL;
	}
	else {
		return SDL_SCANCODE_0;
	}
	return SDL_SCANCODE_0;
}

j1KeyState j1Input::GetControllerButton(int pad, int id) const
{
	for (std::vector<GamePad*>::const_iterator it = gamepads.begin(); it != gamepads.end(); it++)
	{
		if ((*it)->id == gamepad_connected[pad]) {
			return (*it)->gamecontroller_buttons[id];
		}
	}
	return j1KeyState_null;
}

uint j1Input::GetControllerJoystickMove(int pad, int id) const
{
	for (std::vector<GamePad*>::const_iterator it = gamepads.begin(); it != gamepads.end(); it++)
	{
		if ((*it)->id == gamepad_connected[pad]) {
			return (*it)->joystick_moves[id];
		}
	}
	return 0;
}

void j1Input::AxisReaction(int pad, int axis, int value)
{
	for (std::vector<GamePad*>::iterator it = gamepads.begin(); it != gamepads.end(); it++)
	{
		if ((*it)->id == pad) {
			switch (axis)
			{
			case 0:
				if (value > 0)
				{
					(*it)->joystick_moves[LEFTJOY_RIGHT] = value;
					(*it)->joystick_moves[LEFTJOY_LEFT] = 0;
				}
				else
				{
					(*it)->joystick_moves[LEFTJOY_LEFT] = -value;
					(*it)->joystick_moves[LEFTJOY_RIGHT] = 0;
				}
				break;
			case 1:
				if (value > 0)
				{
					(*it)->joystick_moves[LEFTJOY_DOWN] = value;
					(*it)->joystick_moves[LEFTJOY_UP] = 0;
				}
				else
				{
					(*it)->joystick_moves[LEFTJOY_UP] = -value;
					(*it)->joystick_moves[LEFTJOY_DOWN] = 0;
				}
				break;
			case 2:
				if (value > 0)
				{
					(*it)->joystick_moves[RIGHTJOY_RIGHT] = value;
					(*it)->joystick_moves[RIGHTJOY_LEFT] = 0;
				}
				else
				{
					(*it)->joystick_moves[RIGHTJOY_LEFT] = -value;
					(*it)->joystick_moves[RIGHTJOY_RIGHT] = 0;
				}
				break;
			case 3:
				if (value > 0)
				{
					(*it)->joystick_moves[RIGHTJOY_DOWN] = value;
					(*it)->joystick_moves[RIGHTJOY_UP] = 0;
				}
				else
				{
					(*it)->joystick_moves[RIGHTJOY_UP] = -value;
					(*it)->joystick_moves[RIGHTJOY_DOWN] = 0;
				}
				break;
			case 4:
				(*it)->joystick_moves[LEFT_TRIGGER] = value;
				break;
			case 5:
				(*it)->joystick_moves[RIGHT_TRIGGER] = value;
				break;
			}
			break;
		}
	}
}

void j1Input::AddController(int id)
{
	if (SDL_IsGameController(id) && connected_gamepads < MAX_GAMECONTROLLERS)
	{
		pad = SDL_GameControllerOpen(id);

		if (pad)
		{
			joy = SDL_GameControllerGetJoystick(pad);
			int instanceID = SDL_JoystickInstanceID(joy);
			GamePad* new_pad = new GamePad();
			new_pad->id = instanceID;
			ConnectGamePad(instanceID);
			memset(new_pad->gamecontroller_buttons, KEY_IDLE, sizeof(j1KeyState)*NUM_CONTROLLER_BUTTONS);
			memset(new_pad->joystick_moves, 0, sizeof(uint)*JOY_MOVES_NULL);
			new_pad->pad = pad;
			new_pad->pad_num = connected_gamepads;
			gamepads.push_back(new_pad);
			connected_gamepads++;
			App->player->controller_index = id;
			PadDefaultControls();
		}
	}
}

void j1Input::RemoveController(int id)
{
	for (std::vector<GamePad*>::iterator it = gamepads.begin(); it != gamepads.end() && gamepads.size()>0; it++)
	{
		if ((*it)->id == id)
		{
			DisconectGamePad(id);
			SDL_GameControllerClose((*it)->pad);
			RELEASE(*it);
			gamepads.erase(it);
			connected_gamepads--;
			break;
		}
	}
}

void j1Input::ConnectGamePad(int instanceID)
{
	for (int i = 0; i < MAX_GAMECONTROLLERS; i++) {
		if (gamepad_connected[i] == -1)
		{
			gamepad_connected[i] = instanceID;
			break;
		}
	}
}

void j1Input::DisconectGamePad(int instanceID)
{
	for (int i = 0; i < MAX_GAMECONTROLLERS; i++) {
		if (gamepad_connected[i] == instanceID)
		{
			gamepad_connected[i] = -1;
			break;
		}
	}
}

