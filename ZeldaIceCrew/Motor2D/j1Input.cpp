#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Window.h"
#include "SDL/include/SDL.h"

#define MAX_KEYS 300

j1Input::j1Input() : j1Module()
{
	name.create("input");

	keyboard = new j1KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(j1KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(j1KeyState) * NUM_MOUSE_BUTTONS);
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

	return ret;
}

// Called before the first frame
bool j1Input::Start()
{
	SDL_StopTextInput();
	DefaultControls();
	Init_Pause_Matrix();
	return true;
}

// Called each loop iteration
bool j1Input::PreUpdate()
{
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

	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:
				windowEvents[WE_QUIT] = true;
			break;

			case SDL_TEXTINPUT:
				/* Add new text onto the end of our text */
				text += event.text.text;
				break;
			case SDL_WINDOWEVENT:
				switch(event.window.event)
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
				int scale = App->win->GetScale();
				mouse_motion_x = event.motion.xrel / scale;
				mouse_motion_y = event.motion.yrel / scale;
				mouse_x = event.motion.x / scale;
				mouse_y = event.motion.y / scale;
				//LOG("Mouse motion x %d y %d", mouse_motion_x, mouse_motion_y);
			break;
		}
	}

	return true;
}

// Called before quitting
bool j1Input::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool j1Input::GetWindowEvent(j1EventWindow ev)
{
	return windowEvents[ev];
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
	}
}

void j1Input::Start_Pause(Pause_Type type)
{
	int i = 0;

	for (std::list<j1Module*>::iterator item = App->modules.begin(); item != App->modules.end(); item++)
	{
		if (pause_matrix[i][type] == true)
			(*item)->pause = true;
		else
			(*item)->pause = false;
		i++;
	}

	pause2[type] = true;
}

void j1Input::Stop_Pause(Pause_Type type)
{
	for (std::list<j1Module*>::iterator item = App->modules.begin(); item != App->modules.end(); item++)
	{
		(*item)->pause = false;

	}

	pause2[type] = false;
}

void j1Input::Init_Pause_Matrix()
{
	for (int i = 0; i < last_module_; i++)
		for (int j = 0; j < last_pause_type_; j++)
			pause_matrix[i][j] = false;

	for (int j = 0; j < last_pause_type_; j++)
		pause2[j] = false;

	// General Pause
	{
		pause_matrix[j1Collision_][General_] = true;
		pause_matrix[ModuleParticles_][General_] = true;
	}

	// Inventory Pause
	{

	}
}