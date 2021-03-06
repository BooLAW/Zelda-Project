#include "Main_Screen.h"
#include "j1Player.h"
#include <fstream>
#include"j1Window.h"
#include "Video.h"
#include "j1App.h"

Main_Screen::Main_Screen()
{
}

Main_Screen::~Main_Screen()
{
}

bool Main_Screen::Awake()
{
	LOG("Loading Scene");
	bool ret = true;



	return ret;;
}

bool Main_Screen::Start()
{
	
	std::ifstream f("save/save_game.xml");
	
	if (f.good())
		App->LoadGame("save_game.xml");
	else
		App->player->SetToNewGame();
	
	AddRoom(0, 0);
	App->player->room = { 0,0 };
	bool ret = true;
	App->player->inMainScreen = true;
	fx = App->audio->LoadFx("Audio/Fx/cursor.wav");
	press_fx = App->audio->LoadFx("Audio/Fx/button.wav");
	tex = App->tex->Load("Sprites/TitleScreen.png");
	error = App->audio->LoadFx("Audio/Fx/error.wav");
	controlers = App->tex->Load("Sprites/ControllerControls.png");
	controlers_sel = App->tex->Load("Sprites/ControllerControlsselected.png");

	//App->render->camera.w = 1920;
	//App->render->camera.h = 1200;
	App->render->cam_travel = true;
	background = (GuiImage*)App->gui->CreateElement(image);
	background->pos = { 0,0 };
	background->texture = tex;
	background->texture_rect = { 0,0,1024,768 };
	background->active = true;
	background->movable = true;

	Continue = (GuiImage*)App->gui->CreateElement(image);
	Continue->pos = { 250, 250 };
	Continue->texture_rect = { 0 , 514, 683,36 };
	Continue->active = true;
	Continue->movable = true;
	ui_elements.push_back(Continue);

	cont = (GuiText*)App->gui->CreateElement(text);
	cont->str = "Dungeons";
	cont->active = true;
	cont->movable = true;
	cont->pos = { Continue->pos.x + 550, Continue->pos.y + 2 };

	New_game = (GuiImage*)App->gui->CreateElement(image);
	New_game->pos = { Continue->pos.x,Continue->pos.y + 100 };
	New_game->texture_rect = { 0 , 514, 683,36 };
	New_game->active = true;
	New_game->movable = true;
	ui_elements.push_back(New_game);

	new_game = (GuiText*)App->gui->CreateElement(text);
	new_game->str = "New Game";
	new_game->active = true;
	new_game->movable = true;
	new_game->pos = { New_game->pos.x + 550, New_game->pos.y + 2 };

	Arena = (GuiImage*)App->gui->CreateElement(image);
	Arena->pos = { New_game->pos.x,New_game->pos.y + 100 };
	Arena->texture_rect = { 0 , 514, 683,36 };
	Arena->active = true;
	Arena->movable = true;
	ui_elements.push_back(Arena);

	arena = (GuiText*)App->gui->CreateElement(text);
	arena->str = "Arena";
	arena->active = true;
	arena->movable = true;
	arena->pos = { Arena->pos.x + 550, Arena->pos.y + 2 };

	Settings = (GuiImage*)App->gui->CreateElement(image);
	Settings->pos = { Arena->pos.x,Arena->pos.y + 100 };
	Settings->texture_rect = { 0 , 514, 683,36 };;
	Settings->active = true;
	Settings->movable = true;
	ui_elements.push_back(Settings);

	settings = (GuiText*)App->gui->CreateElement(text);
	settings->str = "Settings";
	settings->active = true;
	settings->movable = true;
	settings->pos = { Settings->pos.x + 550, Settings->pos.y + 2 };



	Exit = (GuiImage*)App->gui->CreateElement(image);
	Exit->pos = { Settings->pos.x,Settings->pos.y + 100 };
	Exit->texture_rect = { 0 , 514, 683,36 };
	Exit->active = true;
	Exit->movable = true;
	ui_elements.push_back(Exit);

	exit = (GuiText*)App->gui->CreateElement(text);
	exit->str = "Exit";
	exit->active = true;
	exit->movable = true;
	exit->pos = { Exit->pos.x + 550, Exit->pos.y + 2 };

	Controls = (GuiImage*)App->gui->CreateElement(image);
	Controls->pos = { 250,350 };
	Controls->texture_rect = { 0, 514, 683, 36 };
	Controls->active = false;
	Controls->movable = true;
	settings_elements.push_back(Controls);

	Mute = (GuiImage*)App->gui->CreateElement(image);
	Mute->pos = { Controls->pos.x,Controls->pos.y + 100 };
	Mute->texture_rect = { 0, 514, 683, 36 };
	Mute->active = false;
	Mute->movable = true;
	settings_elements.push_back(Mute);

	

	controls = (GuiText*)App->gui->CreateElement(text);
	controls->str = "Controls";
	controls->active = false;
	controls->movable = true;
	controls->pos = { Controls->pos.x + 550, Controls->pos.y + 2 };

	mute = (GuiText*)App->gui->CreateElement(text);
	mute->str = "Mute";
	mute->active = false;
	mute->movable = true;
	mute->pos = { Mute->pos.x + 550, Mute->pos.y + 2 };

/*	Screen = (GuiImage*)App->gui->CreateElement(image);
	Screen->pos = { Mute->pos.x, Mute->pos.y + 100 };
	Screen->active = false;
	Screen->movable = true;
	Screen->texture_rect = { 0, 514, 683, 36 };
	settings_elements.push_back(Screen);


	screen = (GuiText*)App->gui->CreateElement(text);
	screen->str = "Full Screen";
	screen->active = false;
	screen->movable = true;
	screen->pos = { Screen->pos.x + 550, Screen->pos.y + 2 };*/
	
	Back = (GuiImage*)App->gui->CreateElement(image);
	Back->pos = { Mute->pos.x,Mute->pos.y + 100 };
	Back->texture_rect = { 0, 514, 683, 36 };
	Back->active = false;
	Back->movable = true;
	settings_elements.push_back(Back);

	back = (GuiText*)App->gui->CreateElement(text);
	back->str = "Back";
	back->active = false;
	back->movable = true;
	back->pos = { Back->pos.x + 550, Back->pos.y + 2 };

	///////////////////////////

	Up = (GuiImage*)App->gui->CreateElement(image);
	Up->pos = { 250,100 };
	Up->texture_rect = { 0, 514, 683, 36 };
	Up->active = false;
	Up->movable = true;
	controls_elements.push_back(Up);

	up = (GuiText*)App->gui->CreateElement(text);
	up->str = "Up";
	up->active = false;
	up->movable = true;
	up->pos = { Up->pos.x + 350, Up->pos.y + 2 };

	Down = (GuiImage*)App->gui->CreateElement(image);
	Down->pos = { Up->pos.x,Up->pos.y + 50 };
	Down->texture_rect = { 0, 514, 683, 36 };
	Down->active = false;
	Down->movable = true;
	controls_elements.push_back(Down);

	down = (GuiText*)App->gui->CreateElement(text);
	down->str = "Down";
	down->active = false;
	down->movable = true;
	down->pos = { Down->pos.x + 350, Down->pos.y + 2 };

	Right = (GuiImage*)App->gui->CreateElement(image);
	Right->pos = { Down->pos.x,Down->pos.y + 50 };
	Right->texture_rect = { 0, 514, 683, 36 };
	Right->active = false;
	Right->movable = true;
	controls_elements.push_back(Right);

	right = (GuiText*)App->gui->CreateElement(text);
	right->str = "Right";
	right->active = false;
	right->movable = true;
	right->pos = { Right->pos.x + 350, Right->pos.y + 2 };

	Left = (GuiImage*)App->gui->CreateElement(image);
	Left->pos = { Right->pos.x,Right->pos.y + 50 };
	Left->texture_rect = { 0, 514, 683, 36 };
	Left->active = false;
	Left->movable = true;
	controls_elements.push_back(Left);

	left = (GuiText*)App->gui->CreateElement(text);
	left->str = "Left";
	left->active = false;
	left->movable = true;
	left->pos = { Left->pos.x + 350, Left->pos.y + 2 };

	Move_up = (GuiImage*)App->gui->CreateElement(image);
	Move_up->pos = { Left->pos.x,Left->pos.y + 50 };
	Move_up->texture_rect = { 0, 514, 683, 36 };
	Move_up->active = false;
	Move_up->movable = true;
	controls_elements.push_back(Move_up);

	move_up = (GuiText*)App->gui->CreateElement(text);
	move_up->str = "Move Up";
	move_up->active = false;
	move_up->movable = true;
	move_up->pos = { Move_up->pos.x + 350, Move_up->pos.y + 2 };

	Move_down = (GuiImage*)App->gui->CreateElement(image);
	Move_down->pos = { Move_up->pos.x,Move_up->pos.y + 50 };
	Move_down->texture_rect = { 0, 514, 683, 36 };
	Move_down->active = false;
	Move_down->movable = true;
	controls_elements.push_back(Move_down);

	move_down = (GuiText*)App->gui->CreateElement(text);
	move_down->str = "Move Down";
	move_down->active = false;
	move_down->movable = true;
	move_down->pos = { Move_down->pos.x + 350, Move_down->pos.y + 2 };

	Move_right = (GuiImage*)App->gui->CreateElement(image);
	Move_right->pos = { Move_down->pos.x,Move_down->pos.y + 50 };
	Move_right->texture_rect = { 0, 514, 683, 36 };
	Move_right->active = false;
	Move_right->movable = true;
	controls_elements.push_back(Move_right);

	move_right = (GuiText*)App->gui->CreateElement(text);
	move_right->str = "Move Right";
	move_right->active = false;
	move_right->movable = true;
	move_right->pos = { Move_right->pos.x + 350, Move_right->pos.y + 2 };

	Move_left = (GuiImage*)App->gui->CreateElement(image);
	Move_left->pos = { Move_right->pos.x,Move_right->pos.y + 50 };
	Move_left->texture_rect = { 0, 514, 683, 36 };
	Move_left->active = false;
	Move_left->movable = true;
	controls_elements.push_back(Move_left);

	move_left = (GuiText*)App->gui->CreateElement(text);
	move_left->str = "Move_left";
	move_left->active = false;
	move_left->movable = true;
	move_left->pos = { Move_left->pos.x + 350, Move_left->pos.y + 2 };

	Menu = (GuiImage*)App->gui->CreateElement(image);
	Menu->pos = { Move_left->pos.x,Move_left->pos.y + 50 };
	Menu->texture_rect = { 0, 514, 683, 36 };
	Menu->active = false;
	Menu->movable = true;
	controls_elements.push_back(Menu);

	menu = (GuiText*)App->gui->CreateElement(text);
	menu->str = "Menu";
	menu->active = false;
	menu->movable = true;
	menu->pos = { Menu->pos.x + 350, Menu->pos.y + 2 };

	Action = (GuiImage*)App->gui->CreateElement(image);
	Action->pos = { Menu->pos.x,Menu->pos.y + 50 };
	Action->texture_rect = { 0, 514, 683, 36 };
	Action->active = false;
	Action->movable = true;
	controls_elements.push_back(Action);

	action = (GuiText*)App->gui->CreateElement(text);
	action->str = "Action";
	action->active = false;
	action->movable = true;
	action->pos = { Action->pos.x + 350, Action->pos.y + 2 };

	Dash = (GuiImage*)App->gui->CreateElement(image);
	Dash->pos = { Action->pos.x,Action->pos.y + 50 };
	Dash->texture_rect = { 0, 514, 683, 36 };
	Dash->active = false;
	Dash->movable = true;
	controls_elements.push_back(Dash);

	dash = (GuiText*)App->gui->CreateElement(text);
	dash->str = "Dash";
	dash->active = false;
	dash->movable = true;
	dash->pos = { Dash->pos.x + 350, Dash->pos.y + 2 };

	Back_controls = (GuiImage*)App->gui->CreateElement(image);
	Back_controls->pos = { Dash->pos.x, Dash->pos.y + 50 };
	Back_controls->texture_rect = { 0, 514, 683, 36 };
	Back_controls->active = false;
	Back_controls->movable = true;
	controls_elements.push_back(Back_controls);

	back_controls = (GuiText*)App->gui->CreateElement(text);
	back_controls->str = "Back";
	back_controls->active = false;
	back_controls->movable = true;
	back_controls->pos = { Back_controls->pos.x + 550, Back_controls->pos.y + 2 };



	up_key= (GuiText*)App->gui->CreateElement(text);
	up_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[UP]);
	up_key->active = false;
	up_key->movable = true;
	up_key->pos = { up->pos.x + 200, up->pos.y };

	down_key = (GuiText*)App->gui->CreateElement(text);
	down_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[DOWN]);
	down_key->active = false;
	down_key->movable = true;
	down_key->pos = { down->pos.x + 200, down->pos.y };

	left_key = (GuiText*)App->gui->CreateElement(text);
	left_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[LEFT]);
	left_key->active = false;
	left_key->movable = true;
	left_key->pos = { left->pos.x + 200, left->pos.y };

	right_key = (GuiText*)App->gui->CreateElement(text);
	right_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[RIGHT]);
	right_key->active = false;
	right_key->movable = true;
	right_key->pos = { right->pos.x + 200, right->pos.y };

	move_up_key = (GuiText*)App->gui->CreateElement(text);
	move_up_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[MOVE_UP]);
	move_up_key->active = false;
	move_up_key->movable = true;
	move_up_key->pos = { move_up->pos.x + 200, move_up->pos.y };

	move_down_key = (GuiText*)App->gui->CreateElement(text);
	move_down_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[MOVE_DOWN]);
	move_down_key->active = false;
	move_down_key->movable = true;
	move_down_key->pos = { move_down->pos.x + 200, move_down->pos.y };

	move_left_key = (GuiText*)App->gui->CreateElement(text);
	move_left_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[MOVE_LEFT]);
	move_left_key->active = false;
	move_left_key->movable = true;
	move_left_key->pos = { move_left->pos.x + 200, move_left->pos.y };

	move_right_key = (GuiText*)App->gui->CreateElement(text);
	move_right_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[MOVE_RIGHT]);
	move_right_key->active = false;
	move_right_key->movable = true;
	move_right_key->pos = { move_right->pos.x + 200, move_right->pos.y };


	menu_key = (GuiText*)App->gui->CreateElement(text);
	menu_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[MENU]);
	menu_key->active = false;
	menu_key->movable = true;
	menu_key->pos = { menu->pos.x + 200, menu->pos.y };

	action_key = (GuiText*)App->gui->CreateElement(text);
	action_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[ACTION]);
	action_key->active = false;
	action_key->movable = true;
	action_key->pos = { action->pos.x + 200, action->pos.y };

	dash_key = (GuiText*)App->gui->CreateElement(text);
	dash_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[DASH]);
	dash_key->active = false;
	dash_key->movable = true;
	dash_key->pos = { dash->pos.x + 200, dash->pos.y };

	

	d1= (GuiImage*)App->gui->CreateElement(image);
	d1->pos= { 250 , 100 };
	d1->active = false;
	d1->texture_rect = { 0, 514, 683, 36 };
	d1->movable = true;
	dungeons.push_back(d1);

	d2 = (GuiImage*)App->gui->CreateElement(image);
	d2->pos = { d1->pos.x , d1->pos.y+100 };
	d2->active = false;
	d2->texture_rect = { 0, 514, 683, 36 };
	d2->movable = true;
	dungeons.push_back(d2);

	d3 = (GuiImage*)App->gui->CreateElement(image);
	d3->pos = { d2->pos.x , d2->pos.y + 100 };
	d3->active = false;
	d3->texture_rect = { 0, 514, 683, 36 };
	d3->movable = true;
	dungeons.push_back(d3);

	d4 = (GuiImage*)App->gui->CreateElement(image);
	d4->pos = { d3->pos.x , d3->pos.y + 100 };
	d4->active = false;
	d4->texture_rect = { 0, 514, 683, 36 };
	d4->movable = true;
	dungeons.push_back(d4);

	d5 = (GuiImage*)App->gui->CreateElement(image);
	d5->pos = { d4->pos.x , d4->pos.y + 100 };
	d5->active = false;
	d5->texture_rect = { 0, 514, 683, 36 };
	d5->movable = true;
	dungeons.push_back(d5);

	dungeon_boss = (GuiImage*)App->gui->CreateElement(image);
	dungeon_boss->pos = { d5->pos.x , d5->pos.y + 100 };
	dungeon_boss->active = false;
	dungeon_boss->texture_rect = { 0, 514, 683, 36 };
	dungeon_boss->movable = true;
	dungeons.push_back(dungeon_boss);


	Back_dung = (GuiImage*)App->gui->CreateElement(image);
	Back_dung->pos = { dungeon_boss->pos.x , dungeon_boss->pos.y + 100 };
	Back_dung->active = false;
	Back_dung->texture_rect = { 0, 514, 683, 36 };
	Back_dung->movable = true;
	dungeons.push_back(Back_dung);

	D1 = (GuiText*)App->gui->CreateElement(text);
	D1->pos = { d1->pos.x + 540, d1->pos.y + 2 };
	D1->active = false;
	D1->str = "Hyrule Castle";
	D1->movable = true;

	D2 = (GuiText*)App->gui->CreateElement(text);
	D2->pos = { d2->pos.x + 550, d2->pos.y + 2 };
	D2->active = false;
	D2->str = "1989";
	D2->movable = true;
	App->audio->PlayMusic("Audio/Music/Opening.ogg");

	D3 = (GuiText*)App->gui->CreateElement(text);
	D3->pos = { d3->pos.x + 550, d3->pos.y + 2 };
	D3->active = false;
	D3->str = "Lost Woods";
	D3->movable = true;

	D4 = (GuiText*)App->gui->CreateElement(text);
	D4->pos = { d4->pos.x + 550, d4->pos.y + 2 };
	D4->active = false;
	D4->str = "Death Mountain";
	D4->movable = true;

	D5 = (GuiText*)App->gui->CreateElement(text);
	D5->pos = { d5->pos.x + 550, d5->pos.y + 2 };
	D5->active = false;
	D5->str = "Gerudo Valley";
	D5->movable = true;

	back_dung = (GuiText*)App->gui->CreateElement(text);
	back_dung->pos = { Back_dung->pos.x + 550, Back_dung->pos.y + 2 };
	back_dung->active = false;
	back_dung->str = "Back";
	back_dung->movable = true;

	DB = (GuiText*)App->gui->CreateElement(text);
	DB->pos = { dungeon_boss->pos.x + 530, dungeon_boss->pos.y + 2 };
	DB->active = false;
	DB->str = "Agahnim Castle";
	DB->movable = true;

	d1_lvl= (GuiText*)App->gui->CreateElement(text);
	d1_lvl->pos = { d1->pos.x + 400, d1->pos.y + 2 };
	d1_lvl->active = false;
	d1_lvl->str = "Easy";
	d1_lvl->movable = true;

	d2_lvl = (GuiText*)App->gui->CreateElement(text);
	d2_lvl->pos = { d2->pos.x + 400, d2->pos.y + 2 };
	d2_lvl->active = false;
	d2_lvl->str = "Medium";
	d2_lvl->movable = true;

	d3_lvl = (GuiText*)App->gui->CreateElement(text);
	d3_lvl->pos = { d3->pos.x +400, d3->pos.y + 2 };
	d3_lvl->active = false;
	d3_lvl->str = "Medium";
	d3_lvl->movable = true;

	d4_lvl = (GuiText*)App->gui->CreateElement(text);
	d4_lvl->pos = { d4->pos.x +400, d4->pos.y + 2 };
	d4_lvl->active = false;
	d4_lvl->str = "Hard";
	d4_lvl->movable = true;

	d5_lvl = (GuiText*)App->gui->CreateElement(text);
	d5_lvl->pos = { d5->pos.x +400, d5->pos.y + 2 };
	d5_lvl->active = false;
	d5_lvl->str = "Hard";
	d5_lvl->movable = true;

	

	key1 = (GuiImage*)App->gui->CreateElement(image);
	key1->pos = { D1->pos.x - 50, D1->pos.y };
	key1->texture_rect = { 939,455,28,32 };
	key1->active = false;
	key1->movable = true;

	key2 = (GuiImage*)App->gui->CreateElement(image);
	key2->pos = { D2->pos.x - 50, D2->pos.y };
	key2->texture_rect = { 939,455,28,32 };
	key2->active = false;
	key2->movable = true;

	key3 = (GuiImage*)App->gui->CreateElement(image);
	key3->pos = { D3->pos.x - 50, D3->pos.y };
	key3->texture_rect = { 939,455,28,32 };
	key3->active = false;
	key3->movable = true;

	key4 = (GuiImage*)App->gui->CreateElement(image);
	key4->pos = { D4->pos.x - 50, D4->pos.y };
	key4->texture_rect = { 939,455,28,32 };
	key4->active = false;
	key4->movable = true;

	key5 = (GuiImage*)App->gui->CreateElement(image);
	key5->pos = { D5->pos.x - 50, D5->pos.y };
	key5->texture_rect = { 939,455,28,32 };
	key5->active = false;
	key5->movable = true;


	img_dung = (GuiImage*)App->gui->CreateElement(image);
	img_dung->texture = App->tex->Load("Sprites/MapImages.png");
	img_dung->active = false;
	img_dung->movable = true;
	img_dung->pos = { 20,450 };

	Pad = (GuiImage*)App->gui->CreateElement(image);
	Pad->pos = key3->pos;
	Pad->texture_rect = { 939,455,28,32 };
	Pad->active = false;
	Pad->movable = true;
	choosing.push_back(Pad);

	Key = (GuiImage*)App->gui->CreateElement(image);
	Key->pos = key4->pos;
	Key->texture_rect = { 939,455,28,32 };
	Key->active = false;
	Key->movable = true;
	choosing.push_back(Key);
	
	pad = (GuiText*)App->gui->CreateElement(text);
	pad->pos = { Pad->pos.x , Pad->pos.y + 2 };
	pad->active = false;
	pad->str = "Gamepad";
	pad->movable = true;

	key = (GuiText*)App->gui->CreateElement(text);
	key->pos = { Key->pos.x , Key->pos.y + 2 };
	key->active = false;
	key->str = "Keyboard";
	key->movable = true;

	preset1 = (GuiImage*)App->gui->CreateElement(image);
	preset1->pos = { 200,10 };
	preset1->active = false;
	preset1->movable = true;
	preset1->texture = controlers;
	preset1->texture_rect = { 0,0,500,293 };

	preset2 = (GuiImage*)App->gui->CreateElement(image);
	preset2->pos = { 200, 400 };
	preset2->active = false;
	preset2->movable = true;
	preset2->texture = controlers;
	preset2->texture_rect = { 0,335,500,293 };
	
	Generatekeys();

	selected = Continue;

	in_settings = false;
	in_controls = false;
	changing_controls = false;
	in_dungeons = false;
	in_keyboard = false;
	in_pad = false;

	if (App->first_open == false) {
		App->video->PlayVideo("./IntroLogo_1.ogv", { 0, 0, (int)App->win->GetWidth(), (int)App->win->GetHeight() });
		App->first_open = true;
	}

	return ret;
}

bool Main_Screen::Update(float dt)
{

	bool ret = true;
	if (in_settings) {

		for (std::list<UIElement*>::const_iterator it = controls_elements.cbegin(); it != controls_elements.cend(); it++) {
			it._Ptr->_Myval->active = false;
		}
		//Screen->active = true;
		//screen->active = true;
		Disablekeys();
		Disable_dungeons();
		img_dung->active = false;
		preset1->active = false;
		preset2->active = false;
		Arena->active = false;
		arena->active = false;
		up->active = false;
		Pad->active = false;
		pad->active = false;
		Key->active = false;
		key->active = false;
		
		down->active = false;
		right->active = false;
		left->active = false;
		move_up->active = false;
		move_down->active = false;
		move_right->active = false;
		move_left->active = false;
		menu->active = false;
		action->active = false;
		dash->active = false;
		back_controls->active = false;
		////////////////////////////////////////////
		New_game->active = false;
		new_game->active = false;
		Continue->active = false;
		cont->active = false;
		Settings->active = false;
		settings->active = false;
		Exit->active = false;
		exit->active = false;
		//////////////////////////////
		Controls->active = true;
		controls->active = true;
		Mute->active = true;
		mute->active = true;
		Back->active = true;
		back->active = true;

		up_key->active = false;
		down_key->active = false;
		left_key->active = false;
		right_key->active = false;
		move_up_key->active = false;
		move_down_key->active = false;
		move_left_key->active = false;
		move_right_key->active = false;
		menu_key->active = false;
		action_key->active = false;
		dash_key->active = false;

		d1_lvl->active = false;
		d2_lvl->active = false;
		d3_lvl->active = false;
		d4_lvl->active = false;
		d5_lvl->active = false;

		for (std::list<UIElement*>::const_iterator it = settings_elements.cbegin(); it != settings_elements.cend(); it++) {
			if (selected == it._Ptr->_Myval) {
				it._Ptr->_Myval->texture_rect = { 0,473,683,36 };
				it._Ptr->_Myval->pos.x = 300;
			}
			else {
				it._Ptr->_Myval->texture_rect = { 0, 514, 683, 36 };
				it._Ptr->_Myval->pos.x = 250;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1)) {
			App->audio->PlayFx(fx);
			selected = Settings_Prev();
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1)) {
			App->audio->PlayFx(fx);
			selected = Settings_Next();

		}
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_A))) {
			App->audio->PlayFx(press_fx);
			if (selected == Controls) {
				in_settings = false;
				in_controls = true;
				selected = choosing.front();

			}
			if (selected == Mute) {
				if (App->audio->volume_percentatge == 0) {
					Mute->texture_rect = { 0, 514, 683, 36 };
				}
				if (App->audio->volume_percentatge != 0) {
					App->audio->volume_percentatge = 0;
					App->audio->SetVolumeMusic(0);
					App->audio->SetVolume(0, -1);
				}
				else {
					App->audio->volume_percentatge = 1;
					App->audio->SetVolumeMusic(App->audio->volume_std * App->audio->volume_percentatge);
					App->audio->SetVolume(App->audio->volume_std * App->audio->volume_percentatge, -1);
				}
			}
		/*	if (selected == Screen) {
				if (App->fullscreen) {
					SDL_SetWindowFullscreen(App->win->window, SDL_FALSE);
					App->fullscreen = false;
				}
				else {
					SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_FULLSCREEN);
					App->fullscreen = true;
				}
			}*/
			if (selected == Back) {

				selected = ui_elements.front();
				in_settings = false;
				in_controls = false;
			}

		}
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_B))) {
			selected = ui_elements.front();
			in_settings = false;
			in_controls = false;
		}



	}
	else if (in_controls) {
		
		preset1->active = false;
		preset2->active = false;
		Pad->active = true;
		Key->active = true;
		pad->active = true;
		key->active = true;
		Disablekeys();
		Disable_dungeons();
		img_dung->active = false;
		Arena->active = false;
		arena->active = false;
		New_game->active = false;
		new_game->active = false;
		Continue->active = false;
		cont->active = false;
		Settings->active = false;
		settings->active = false;
		Exit->active = false;
		exit->active = false;


		Controls->active = false;
		controls->active = false;
		Mute->active = false;
		mute->active = false;
		Back->active = false;
		back->active = false;
		d1_lvl->active = false;
		d2_lvl->active = false;
		d3_lvl->active = false;
		d4_lvl->active = false;
		d5_lvl->active = false;

		for (std::list<UIElement*>::const_iterator it = controls_elements.cbegin(); it != controls_elements.cend(); it++) {
			it._Ptr->_Myval->active = false;
		}
		up->active = false;
		down->active = false;
		right->active = false;
		left->active = false;
		move_up->active = false;
		move_down->active = false;
		move_right->active = false;
		move_left->active = false;
		menu->active = false;
		action->active = false;
		dash->active = false;
		back_controls->active = false;

		up_key->active = false;
		down_key->active = false;
		left_key->active = false;
		right_key->active = false;
		move_up_key->active = false;
		move_down_key->active = false;
		move_left_key->active = false;
		move_right_key->active = false;
		menu_key->active = false;
		action_key->active = false;
		dash_key->active = false;

		for (std::list<UIElement*>::const_iterator it = choosing.cbegin(); it != choosing.cend(); it++) {
			if (selected == it._Ptr->_Myval) {
				it._Ptr->_Myval->texture_rect = { 0,473,683,36 };
				it._Ptr->_Myval->pos.x = 300;
			}
			else {
				it._Ptr->_Myval->texture_rect = { 0, 514, 683, 36 };
				it._Ptr->_Myval->pos.x = 250;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1)) {
			App->audio->PlayFx(fx);
			selected = Choosing_Prev();
			/*if (!IsInsideCam(selected)) {
			Scroll_Down();
			}*/
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1)) {
			App->audio->PlayFx(fx);
			selected = Choosing_Next();
			/*if (!IsInsideCam(selected)) {
			Scroll_Up();
			}*/

		}
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_A))) {
			if (selected == Pad) {
				App->audio->PlayFx(press_fx);
				in_pad = true;
				in_controls = false;
				selected = preset1;
				changing_controls = false;
			}
			else if (selected == Key){
				App->audio->PlayFx(press_fx);
				in_keyboard = true;
				in_controls = false;
				changing_controls = false;
				selected = controls_elements.front();
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_B))) {
			App->audio->PlayFx(press_fx);
			in_settings = true;
			in_controls = false;
			selected = settings_elements.front();
			changing_controls = false;



		}
	}
	else if (in_pad) {
		//selected = preset1;
		preset1->active = true;
		preset2->active = true;
		Pad->active = false;
		Key->active = false;
		pad->active = false;
		key->active = false;
		Disablekeys();
		Disable_dungeons();
		img_dung->active = false;
		Arena->active = false;
		arena->active = false;
		New_game->active = false;
		new_game->active = false;
		Continue->active = false;
		cont->active = false;
		Settings->active = false;
		settings->active = false;
		Exit->active = false;
		exit->active = false;


		Controls->active = false;
		controls->active = false;
		Mute->active = false;
		mute->active = false;
		Back->active = false;
		back->active = false;
		d1_lvl->active = false;
		d2_lvl->active = false;
		d3_lvl->active = false;
		d4_lvl->active = false;
		d5_lvl->active = false;

		

		for (std::list<UIElement*>::const_iterator it = controls_elements.cbegin(); it != controls_elements.cend(); it++) {
			it._Ptr->_Myval->active = false;
		}
		up->active = false;
		down->active = false;
		right->active = false;
		left->active = false;
		move_up->active = false;
		move_down->active = false;
		move_right->active = false;
		move_left->active = false;
		menu->active = false;
		action->active = false;
		dash->active = false;
		back_controls->active = false;

		up_key->active = false;
		down_key->active = false;
		left_key->active = false;
		right_key->active = false;
		move_up_key->active = false;
		move_down_key->active = false;
		move_left_key->active = false;
		move_right_key->active = false;
		menu_key->active = false;
		action_key->active = false;
		dash_key->active = false;

		if (selected == preset1) {
			preset1->texture = controlers_sel;
			preset2->texture = controlers;
		}
		else {
			preset1->texture = controlers;
			preset2->texture = controlers_sel;
		}

		

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1)) {
			App->audio->PlayFx(fx);
			if (selected == preset1) {
				selected = preset2;
			}
			else {
				selected = preset1;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1)) {
			App->audio->PlayFx(fx);
			if (selected == preset1) {
				selected = preset2;
			}
			else {
				selected = preset1;
			}

		}
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_A))) {
			if (selected == preset1) {
				App->audio->PlayFx(press_fx);
				App->input->preset_1 = true;
				in_controls = true;
				in_pad = false;
				selected = choosing.front();
			}
			else if (selected == preset2) {
				App->audio->PlayFx(press_fx);
				App->input->preset_1 = false;
				in_controls = true;
				in_pad = false;
				selected = choosing.front();
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_B))) {
			App->audio->PlayFx(press_fx);
			in_controls = true;
			in_pad = false;
			selected = choosing.front();
			



		}



	}
	else if (in_keyboard) {
		preset1->active = false;
		preset2->active = false;
		Pad->active = false;
		pad->active = false;
		Key->active = false;
		key->active=false;
		//Screen->active =false;
		//screen->active =false;
		Disablekeys();
		Disable_dungeons();
		img_dung->active = false;
		Arena->active = false;
		arena->active = false;
		New_game->active = false;
		new_game->active = false;
		Continue->active = false;
		cont->active = false;
		Settings->active = false;
		settings->active = false;
		Exit->active = false;
		exit->active = false;
		

		Controls->active = false;
		controls->active = false;
		Mute->active = false;
		mute->active = false;
		Back->active = false;
		back->active = false;
		d1_lvl->active = false;
		d2_lvl->active = false;
		d3_lvl->active = false;
		d4_lvl->active = false;
		d5_lvl->active = false;

		for (std::list<UIElement*>::const_iterator it = controls_elements.cbegin(); it != controls_elements.cend(); it++) {
			it._Ptr->_Myval->active = true;
		}

		up->active = true;
		down->active = true;
		right->active = true;
		left->active = true;
		move_up->active = true;
		move_down->active = true;
		move_right->active = true;
		move_left->active = true;
		menu->active = true;
		action->active = true;
		dash->active = true;
		back_controls->active = true;

		up_key->active = true;
		down_key->active = true;
		left_key->active = true;
		right_key->active = true;
		move_up_key->active = true;
		move_down_key->active = true;
		move_left_key->active = true;
		move_right_key->active = true;
		menu_key->active = true;
		action_key->active = true;
		dash_key->active = true;

		
		
			for (std::list<UIElement*>::const_iterator it = controls_elements.cbegin(); it != controls_elements.cend(); it++) {
				if (selected == it._Ptr->_Myval) {
					it._Ptr->_Myval->texture_rect = { 0,473,683,36 };
					it._Ptr->_Myval->pos.x = 300;
				}
				else {
					it._Ptr->_Myval->texture_rect = { 0, 514, 683, 36 };
					it._Ptr->_Myval->pos.x = 250;
				}
			}
			if (changing_controls) {
				SDL_Scancode code = App->input->returnkey();
				selected->texture_rect = { 0,555,685,34 };
				if (code != SDL_SCANCODE_0) {
					if (selected == Up) {

						if (code != SDL_SCANCODE_0) {
							App->input->controls[UP] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}

					}
					if (selected == Down) {
						if (code != SDL_SCANCODE_0) {

							App->input->controls[DOWN] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}
					}
					if (selected == Right) {

						if (code != SDL_SCANCODE_0) {
							App->input->controls[RIGHT] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}
					}
					if (selected == Left) {
						if (code != SDL_SCANCODE_0) {
							App->input->controls[LEFT] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}
					}
					if (selected == Move_left) {
						if (code != SDL_SCANCODE_0) {
							App->input->controls[MOVE_LEFT] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}
					}
					if (selected == Move_up) {
						if (code != SDL_SCANCODE_0) {
							App->input->controls[MOVE_UP] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}

					}
					if (selected == Move_down) {
						if (code != SDL_SCANCODE_0) {
							App->input->controls[MOVE_DOWN] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}

					}
					if (selected == Move_right) {
						if (code != SDL_SCANCODE_0) {
							App->input->controls[MOVE_RIGHT] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}
					}
					if (selected == Menu) {
						if (code != SDL_SCANCODE_0) {
							App->input->controls[MENU] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}
					}
					if (selected == Action) {
						if (code != SDL_SCANCODE_0) {
							App->input->controls[ACTION] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}
					}
					if (selected == Dash) {

						if (code != SDL_SCANCODE_0) {
							App->input->controls[DASH] = code;
							selected->texture_rect = { 0, 514, 683, 36 };
							changing_controls = false;
						}
					}
				}
			}

			else{
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1)) {
				App->audio->PlayFx(fx);
				selected = Controls_Prev();
				/*if (!IsInsideCam(selected)) {
				Scroll_Down();
				}*/
			}
			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1)) {
				App->audio->PlayFx(fx);
				selected = Controls_Next();
				/*if (!IsInsideCam(selected)) {
				Scroll_Up();
				}*/

			}
			if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_A))) {
				if (selected == Back_controls) {
					App->audio->PlayFx(press_fx);
					in_keyboard = false;
					in_controls = true;
					selected = choosing.front();
					changing_controls = false;
				}
				else {
					changing_controls = true;
					App->audio->PlayFx(press_fx);
				}
			}
			if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_B))) {
				App->audio->PlayFx(press_fx);
				in_keyboard = false;
				in_controls = true;
				selected = choosing.front();
				changing_controls = false;

				
			
			}


			}
		}
		else if (in_dungeons) {
			UpdateKeys();
			Enablekeys();
			if (selected == d1) {
				img_dung->active = true;
				img_dung->texture_rect = { 0,0,441,264};
			}
			if (selected == d2) {
				img_dung->active = true;
				img_dung->texture_rect = { 445,0,440,264 };
			}
			if (selected == d3) {
				img_dung->active = true;
				img_dung->texture_rect = { 0,269,440,264 };
			}
			if (selected == d4) {
				img_dung->active = true;
				img_dung->texture_rect = { 445,269,440,264 };
			}
			if (selected == d5) {
				img_dung->active = true;
				img_dung->texture_rect = { 0,538,440,264 };
			}
			if (selected == dungeon_boss) {
				img_dung->active = true;
				img_dung->texture_rect = { 445,538,440,264 };
			}
			if (selected == Back_dung) {
				img_dung->active = false;
			}

			//Screen->active =false;
		//	screen->active =false;
			Enable_dungeons();
			preset1->active = false;
			preset2->active = false;
			d1_lvl->active = true;
			d2_lvl->active = true;
			d3_lvl->active = true;
			d4_lvl->active = true;
			d5_lvl->active = true;
			//img_dung->active = true;
			Back_dung->active = true;
			Arena->active = false;
			Pad->active = false;
			pad->active = false;
			Key->active = false;
			key->active = false;
			arena->active = false;
			back_dung->active = true;
			up->active = false;
			down->active = false;
			right->active = false;
			left->active = false;
			move_up->active = false;
			move_down->active = false;
			move_right->active = false;
			move_left->active = false;
			menu->active = false;
			action->active = false;
			dash->active = false;
			back_controls->active = false;

			Up->active = false;
			Down->active = false;
			Right->active = false;
			Left->active = false;
			Move_up->active = false;
			Move_down->active = false;
			Move_left->active = false;
			Move_right->active = false;
			Menu->active = false;
			Action->active = false;
			Dash->active = false;
			Back_controls->active = false;

			New_game->active = false;
			new_game->active = false;
			Continue->active = false;
			cont->active = false;
			Settings->active = false;
			settings->active = false;
			Exit->active = false;
			exit->active = false;
			Controls->active = false;
			controls->active = false;
			Mute->active = false;
			mute->active = false;
			Back->active = false;
			back->active = false;

			up_key->active = false;
			down_key->active = false;
			left_key->active = false;
			right_key->active = false;
			move_up_key->active = false;
			move_down_key->active = false;
			move_left_key->active = false;
			move_right_key->active = false;
			menu_key->active = false;
			action_key->active = false;
			dash_key->active = false;

			for (int i = 0; i < 5; i++) {
				if (i == 0) {
					if ((App->player->completed_maps[i]) == true) {
						key1->texture_rect = { 977,455,28,32 };
					}
					else {
						key1->texture_rect = { 939,455,28,32 };
					}
				}
				if (i == 1) {
					if ((App->player->completed_maps[i]) == true) {
						key2->texture_rect = { 977,455,28,32 };
					}
					else {
						key2->texture_rect = { 939,455,28,32 };
					}
				}
				if (i == 2) {
					if ((App->player->completed_maps[i+1]) == true) {
						key3->texture_rect = { 977,455,28,32 };
					}
					else {
						key3->texture_rect = { 939,455,28,32 };
					}
				}
				if (i == 3) {
					if ((App->player->completed_maps[i-1]) == true) {
						key5->texture_rect = { 977,455,28,32 };
					}
					else {
						key5->texture_rect = { 939,455,28,32 };
					}
				}
				if (i == 4) {
					if ((App->player->completed_maps[i]) == true) {
						key4->texture_rect = { 977,455,28,32 };
					}
					else {
						key4->texture_rect = { 939,455,28,32 };
					}
				}
			}
			for (std::list<UIElement*>::const_iterator it = dungeons.cbegin(); it != dungeons.cend(); it++) {
				if (selected == it._Ptr->_Myval) {
					it._Ptr->_Myval->texture_rect = { 0,473,683,36 };
					it._Ptr->_Myval->pos.x = 300;

				}
				else {
					it._Ptr->_Myval->texture_rect = { 0, 514, 683, 36 };
					it._Ptr->_Myval->pos.x = 250;
				}
			}
			if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
				App->player->keys = 5;
				
			}
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1)) {
				App->audio->PlayFx(fx);
				if (selected == Back_dung) {
					if (App->player->keys >= 3) {
						selected = dungeon_boss;
					}
					else {
						selected = d5;
					}
				}
				else {
					selected = Dungeons_Prev();
				}
				/*if (!IsInsideCam(selected)) {
				Scroll_Down();
				}*/
			}
			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1)) {
				App->audio->PlayFx(fx);

				if (selected == d5) {
					if (App->player->keys >= 3) {
						selected = dungeon_boss;
					}
					else {
						selected = Back_dung;
					}
				}
				else {
					selected = Dungeons_Next();
				}
				/*if (!IsInsideCam(selected)) {
				Scroll_Up();
				}*/

			}

			if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_A))) {
				
				if (selected == Back_dung) {
					in_controls = false;
					in_settings = false;
					in_dungeons = false;
					selected = ui_elements.front();
				}
				if (selected == d1) {
					if (App->player->completed_maps[0] == false) {
						App->scene_manager->loading_screen->active = true;
						App->audio->PlayFx(press_fx);
						App->scene_manager->dungeon_id = 0;
						App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
						App->hud->Minimap->active = false;
						App->hud->link_point->active = false;
						App->player->inMainScreen = false;
					}
					else {
						App->audio->PlayFx(error);
					}
				}
				if (selected == d2) {
					if (App->player->completed_maps[1] == false) {
						App->scene_manager->loading_screen->active = true;
						App->audio->PlayFx(press_fx);
						App->scene_manager->dungeon_id = 1;
						App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
						App->hud->Minimap->active = false;
						App->hud->link_point->active = false;
						App->player->inMainScreen = false;
					}
					else {
						App->audio->PlayFx(error);
					}
				}
				if (selected == d3) {
					if (App->player->completed_maps[3] == false) {
						App->scene_manager->loading_screen->active = true;
						App->audio->PlayFx(press_fx);
						App->scene_manager->dungeon_id = 3;
						App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
						App->hud->Minimap->active = false;
						App->hud->link_point->active = false;
						App->player->inMainScreen = false;
					}
					else {
						App->audio->PlayFx(error);
					}
				}
				if (selected == d4) {
					if (App->player->completed_maps[4] == false) {
						App->scene_manager->loading_screen->active = true;
						App->audio->PlayFx(press_fx);
						App->scene_manager->dungeon_id = 4;
						App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
						App->hud->Minimap->active = false;
						App->hud->link_point->active = false;
						App->player->inMainScreen = false;
					}
					else {
						App->audio->PlayFx(error);
					}
				}
				if (selected == d5) {
					if (App->player->completed_maps[2] == false) {
						App->scene_manager->loading_screen->active = true;
						App->audio->PlayFx(press_fx);
						App->scene_manager->dungeon_id = 2;
						App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
						App->hud->Minimap->active = false;
						App->hud->link_point->active = false;
						App->player->inMainScreen = false;
					}
					else {
						App->audio->PlayFx(error);
					}
				}
				if (selected == dungeon_boss) {
					App->scene_manager->loading_screen->active = true;
					App->audio->PlayFx(press_fx);
					App->scene_manager->dungeon_id = 5;
					App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
					App->hud->Minimap->active = false;
					App->hud->link_point->active = false;
					App->player->inMainScreen = false;
				}
				
				//App->LoadGame("save_game.xml");
			}
			if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_B))) {
				App->audio->PlayFx(press_fx);
				in_settings = false;
				in_controls = false;
				changing_controls = false;
				in_dungeons = false;
				selected = ui_elements.front();
				



			}

		}

	
	else {

		for (std::list<UIElement*>::const_iterator it = controls_elements.cbegin(); it != controls_elements.cend(); it++) {
			it._Ptr->_Myval->active = false;
		}
		//Screen->active = false;
		//screen->active = false;
		img_dung->active = false;
		Disablekeys();
		Disable_dungeons();
		preset1->active = false;
		preset2->active = false;
		Pad->active = false;
		pad->active = false;
		Key->active = false;
		key->active = false;
		d1_lvl->active = false;
		d2_lvl->active = false;
		d3_lvl->active = false;
		d4_lvl->active = false;
		d5_lvl->active = false;
		up->active = false;
		down->active = false;
		right->active = false;
		left->active = false;
		move_up->active = false;
		move_down->active = false;
		move_right->active = false;
		move_left->active = false;
		menu->active = false;
		action->active = false;
		dash->active = false;
		back_controls->active = false;

		up_key->active = false;
		down_key->active = false;
		left_key->active = false;
		right_key->active = false;
		move_up_key->active = false;
		move_down_key->active = false;
		move_left_key->active = false;
		move_right_key->active = false;
		menu_key->active = false;
		action_key->active = false;
		dash_key->active = false;

		Arena->active = true;
		arena->active = true;
		New_game->active = true;
		new_game->active = true;
		Continue->active = true;
		cont->active = true;
		Settings->active = true;
		settings->active = true;
		Exit->active = true;
		exit->active = true;

		Controls->active = false;
		controls->active = false;
		Mute->active = false;
		mute->active = false;
		Back->active = false;
		back->active = false;

		for (std::list<UIElement*>::const_iterator it = ui_elements.cbegin(); it != ui_elements.cend(); it++) {
			if (selected == it._Ptr->_Myval) {
				it._Ptr->_Myval->texture_rect = { 0,473,683,36 };
				it._Ptr->_Myval->pos.x = 300;
			}
			else {
				it._Ptr->_Myval->texture_rect = { 0, 514, 683, 36 };
				it._Ptr->_Myval->pos.x = 250;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1)) {
			App->audio->PlayFx(fx);
			selected = Prev();
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || (App->input->dpad_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1)) {
			App->audio->PlayFx(fx);
			selected = Next();

		}
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || (App->input->mmenu_p == 1 && SDL_GameControllerGetButton(App->input->pad, SDL_CONTROLLER_BUTTON_A))) {
			App->audio->PlayFx(press_fx);
			if (selected == New_game) {
				// start a new game, for now:
				App->player->SetToNewGame();
				in_dungeons = true;
				selected = dungeons.front();
			}
			if (selected == Continue) {
				//continue with the current game, for now:
				in_dungeons = true;
				selected = dungeons.front();
			}
			if (selected == Arena) {
				App->scene_manager->dungeon_id = 6;
				App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
				App->hud->Minimap->active = false;
				App->hud->link_point->active = false;

			}
			if (selected == Settings) {
				in_settings = true;
				selected = settings_elements.front();
			}
			if (selected == Exit) {
				ret = false;

			}
		}
	}



	up_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[UP]);
	down_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[DOWN]);
	left_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[LEFT]);
	right_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[RIGHT]);
	move_up_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[MOVE_UP]);
	move_down_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[MOVE_DOWN]);
	move_left_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[MOVE_LEFT]);
	move_right_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[MOVE_RIGHT]);
	menu_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[MENU]);
	action_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[ACTION]);
	dash_key->str = App->input->GetKeyString((SDL_Scancode)App->input->controls[DASH]);


	return ret;
}

UIElement * Main_Screen::Next()
{
	if (selected != nullptr) {
		if (!ui_elements.empty()) {
			if (selected == ui_elements.back()) {
				return ui_elements.back();
			}
			else {
				for (std::list<UIElement*>::const_iterator it = ui_elements.cbegin(); it != ui_elements.cend(); it++) {
					if (selected == it._Ptr->_Myval) {
						if (selected == ui_elements.back()) {
							return ui_elements.back();
						}
						else {
							it++;
							if (it._Ptr != nullptr)
								return it._Ptr->_Myval;
							else
								return ui_elements.back();
						}
					}
				}
			}
		}
	}
}

UIElement * Main_Screen::Prev()
{
	if (selected != nullptr) {
		if (!ui_elements.empty()) {
			if (selected == ui_elements.front()) {
				return ui_elements.front();
			}
			for (std::list<UIElement*>::const_iterator it = ui_elements.cend(); it != ui_elements.cbegin(); it--) {
				if (selected == it._Ptr->_Myval) {
					if (selected == ui_elements.front()) {
						return ui_elements.front();
					}
					else {
						it--;
						if (it._Ptr != nullptr)
							return it._Ptr->_Myval;
						else
							return ui_elements.back();
					}
				}


			}
		}
	}

}

UIElement * Main_Screen::Settings_Next()
{
	if (selected != nullptr) {
		if (!settings_elements.empty()) {
			if (selected == settings_elements.back()) {
				return settings_elements.back();
			}
			else {
				for (std::list<UIElement*>::const_iterator it = settings_elements.cbegin(); it != settings_elements.cend(); it++) {
					if (selected == it._Ptr->_Myval) {
						if (selected == settings_elements.back()) {
							return settings_elements.back();
						}
						else {
							it++;
							if (it._Ptr != nullptr)
								return it._Ptr->_Myval;
							else
								return settings_elements.back();
						}
					}
				}
			}
		}
	}
}

UIElement * Main_Screen::Settings_Prev()
{
	if (selected != nullptr) {
		if (!settings_elements.empty()) {
			if (selected == settings_elements.front()) {
				return settings_elements.front();
			}
			for (std::list<UIElement*>::const_iterator it = settings_elements.cend(); it != settings_elements.cbegin(); it--) {
				if (selected == it._Ptr->_Myval) {
					if (selected == settings_elements.front()) {
						return settings_elements.front();
					}
					else {
						it--;
						if (it._Ptr != nullptr)
							return it._Ptr->_Myval;
						else
							return settings_elements.back();
					}
				}


			}
		}
	}

}

UIElement * Main_Screen::Controls_Prev()
{
	if (selected != nullptr) {
		if (!controls_elements.empty()) {
			if (selected == controls_elements.front()) {
				return controls_elements.front();
			}
			for (std::list<UIElement*>::const_iterator it = controls_elements.cend(); it != controls_elements.cbegin(); it--) {
				if (selected == it._Ptr->_Myval) {
					if (selected == controls_elements.front()) {
						return controls_elements.front();
					}
					else {
						it--;
						if (it._Ptr != nullptr)
							return it._Ptr->_Myval;
						else
							return controls_elements.back();
					}
				}


			}
		}
	}
}

UIElement * Main_Screen::Controls_Next()
{
	if (selected != nullptr) {
		if (!controls_elements.empty()) {
			if (selected == controls_elements.back()) {
				return controls_elements.back();
			}
			else {
				for (std::list<UIElement*>::const_iterator it = controls_elements.cbegin(); it != controls_elements.cend(); it++) {
					if (selected == it._Ptr->_Myval) {
						if (selected == controls_elements.back()) {
							return controls_elements.back();
						}
						else {
							it++;
							if (it._Ptr != nullptr)
								return it._Ptr->_Myval;
							else
								return controls_elements.back();
						}
					}
				}
			}
		}
	}
}

UIElement * Main_Screen::Dungeons_Next()
{
	if (selected != nullptr) {
		if (!dungeons.empty()) {
			if (selected == dungeons.back()) {
				return dungeons.back();
			}
			else {
				for (std::list<UIElement*>::const_iterator it = dungeons.cbegin(); it != dungeons.cend(); it++) {
					if (selected == it._Ptr->_Myval) {
						if (selected == dungeons.back()) {
							return dungeons.back();
						}
						else {
							it++;
							if (it._Ptr != nullptr)
								return it._Ptr->_Myval;
							else
								return dungeons.back();
						}
					}
				}
			}
		}
	}
}

UIElement * Main_Screen::Dungeons_Prev()
{
	if (selected != nullptr) {
		if (!dungeons.empty()) {
			if (selected == dungeons.front()) {
				return dungeons.front();
			}
			for (std::list<UIElement*>::const_iterator it = dungeons.cend(); it != dungeons.cbegin(); it--) {
				if (selected == it._Ptr->_Myval) {
					if (selected == dungeons.front()) {
						return dungeons.front();
					}
					else {
						it--;
						if (it._Ptr != nullptr)
							return it._Ptr->_Myval;
						else
							return dungeons.back();
					}
				}


			}
		}
	}
}

UIElement * Main_Screen::Choosing_Next()
{
	if (selected != nullptr) {
		if (!choosing.empty()) {
			if (selected == choosing.back()) {
				return choosing.back();
			}
			else {
				for (std::list<UIElement*>::const_iterator it = choosing.cbegin(); it != choosing.cend(); it++) {
					if (selected == it._Ptr->_Myval) {
						if (selected == choosing.back()) {
							return choosing.back();
						}
						else {
							it++;
							if (it._Ptr != nullptr)
								return it._Ptr->_Myval;
							else
								return choosing.back();
						}
					}
				}
			}
		}
	}
}

UIElement * Main_Screen::Choosing_Prev()
{
	if (selected != nullptr) {
		if (!choosing.empty()) {
			if (selected == choosing.front()) {
				return choosing.front();
			}
			for (std::list<UIElement*>::const_iterator it = choosing.cend(); it != choosing.cbegin(); it--) {
				if (selected == it._Ptr->_Myval) {
					if (selected == choosing.front()) {
						return choosing.front();
					}
					else {
						it--;
						if (it._Ptr != nullptr)
							return it._Ptr->_Myval;
						else
							return choosing.back();
					}
				}


			}
		}
	}
}

void Main_Screen::Erasekeys()
{
	for (std::list<UIElement*>::const_iterator it = keys.cbegin(); it != keys.cend(); it++) {
		it._Ptr->_Myval->texture_rect = { 977,455,28,32 };
	}
}

void Main_Screen::Scroll_Up()
{
	for (std::list<UIElement*>::const_iterator it = controls_elements.cbegin(); it != controls_elements.cend(); it++) {
		it._Ptr->_Myval->pos.y -= 100;
	}
}

void Main_Screen::Scroll_Down()
{
	for (std::list<UIElement*>::const_iterator it = controls_elements.cbegin(); it != controls_elements.cend(); it++) {
		it._Ptr->_Myval->pos.y += 100;
	}
}

void Main_Screen::Generatekeys()
{
	iPoint pos = { dungeon_boss->pos.x +400 ,dungeon_boss->pos.y  };
	for (uint i = 0; i < 3; i++) {
		GuiImage* img = (GuiImage*)App->gui->CreateElement(image);
		img->pos = pos;
		img->texture_rect = { 939,455,28,32 };
		img->active = false;
		img->movable = true;
		keys.push_back(img);
		pos.x += 30;
		
	}
}

void Main_Screen::UpdateKeys()
{
	int i = 0;
	for (std::list<UIElement*>::const_iterator it = keys.cbegin(); it != keys.cend(); it++) {
		if (i < App->player->keys) {
			it._Ptr->_Myval->texture_rect = { 977,455,28,32 };
		}
		else {
			it._Ptr->_Myval->texture_rect = { 939,455,28,32 };
		}
		i++;
	}
	
}

void Main_Screen::Enablekeys()
{
	for (std::list<UIElement*>::const_iterator it = keys.cbegin(); it != keys.cend(); it++) {
		it._Ptr->_Myval->active = true;

	}
}

void Main_Screen::Disablekeys()
{
	for (std::list<UIElement*>::const_iterator it = keys.cbegin(); it != keys.cend(); it++) {
		it._Ptr->_Myval->active = false;

	}
}

bool Main_Screen::IsInsideCam(UIElement * element)
{
	if ((element->pos.x > App->render->camera.x) && (element->pos.x < App->render->camera.x + App->render->camera.w)) {
		if ((element->pos.y > App->render->camera.y) && (element->pos.y < App->render->camera.y + App->render->camera.h)) {
			return true;
		}
		else return false;
	}
	else {
		return false;
	}
}

bool Main_Screen::CleanUp()
{
	App->scene_manager->loading_screen->active = true;
	bool ret = true;
	App->player->inMainScreen = false;
	App->tex->UnLoad(tex);

	ui_elements.clear();
	settings_elements.clear();
	controls_elements.clear();
	dungeons.clear();
	Disablekeys();
	keys.clear();
	choosing.clear();

	Disablekeys();
	img_dung->active = false;
	Disable_dungeons();
	background->active = false;
	Arena->active = false;
	arena->active = false;
	up->active=false;
	down->active=false;
	right->active=false;
	left->active=false;
	move_up->active=false;
	move_down->active = false;
	move_right->active = false;
	move_left->active = false;
	preset1->active = false;
	preset2->active = false;
	
	menu->active = false;
	action->active = false;
	dash->active = false;
	back_controls->active= false;
	//Screen->active = false;
	//screen->active = false;
	d1_lvl->active = false;
	d2_lvl->active = false;
	d3_lvl->active = false;
	d4_lvl->active = false;
	d5_lvl->active = false;
	Up->active= false;
	Down->active= false;
	Right->active=false;
	Left->active = false;
	Move_up->active= false;
	Move_down->active= false;
	Move_left->active = false;
	Move_right->active = false;
	Menu->active = false;
	Action->active = false;
	Dash->active = false;
	Back_controls->active = false;
	Pad->active = false;
	pad->active = false;
	Key->active = false;
	key->active = false;
	New_game->active = false;
	new_game->active = false;
	Continue->active = false;
	cont->active = false;
	Settings->active = false;
	settings->active = false;
	Exit->active= false;
	exit->active = false;
	Controls->active= false;
	controls->active=false;
	Mute->active=false;
	mute->active=false;
	Back->active=false;
	back->active=false;

	up_key->active = false;
	down_key->active = false;
	left_key->active = false;
	right_key->active = false;
	move_up_key->active = false;
	move_down_key->active = false;
	move_left_key->active = false;
	move_right_key->active = false;
	menu_key->active = false;
	action_key->active = false;
	dash_key->active = false;
	App->hud->Minimap->active = false;
	App->hud->link_point->active = false;
		




	//App->gui->DeleteElement(background);
	/*App->gui->DeleteElement(up);
	App->gui->DeleteElement(down);
	App->gui->DeleteElement(right);
	App->gui->DeleteElement(left);
	App->gui->DeleteElement(move_up);
	App->gui->DeleteElement(move_down);
	App->gui->DeleteElement(move_right);
	App->gui->DeleteElement(move_left);
	App->gui->DeleteElement(menu);
	App->gui->DeleteElement(action);
	App->gui->DeleteElement(dash);
	App->gui->DeleteElement(back_controls);

	App->gui->DeleteElement(Up);
	App->gui->DeleteElement(Down);
	App->gui->DeleteElement(Right);
	App->gui->DeleteElement(Left);
	App->gui->DeleteElement(Move_up);
	App->gui->DeleteElement(Move_down);
	App->gui->DeleteElement(Move_left);
	App->gui->DeleteElement(Move_right);
	App->gui->DeleteElement(Menu);
	App->gui->DeleteElement(Action);
	App->gui->DeleteElement(Dash);
	App->gui->DeleteElement(Back_controls);

	App->gui->DeleteElement(New_game);
	App->gui->DeleteElement(new_game);
	App->gui->DeleteElement(Continue);
	App->gui->DeleteElement(cont);
	App->gui->DeleteElement(Settings);
	App->gui->DeleteElement(settings);
	App->gui->DeleteElement(Exit);
	App->gui->DeleteElement(exit);
	App->gui->DeleteElement(Controls);
	App->gui->DeleteElement(controls);
	App->gui->DeleteElement(Mute);
	App->gui->DeleteElement(mute);
	App->gui->DeleteElement(Back);
	App->gui->DeleteElement(back);*/
	

	return ret;
}

void Main_Screen::Disable_dungeons()
{
	 d1->active = false;
	 d2->active = false;
	 d3->active = false;
	 d4->active = false;
	 d5->active = false;
	 dungeon_boss->active = false;
	 

	 key1->active = false;
	 key2->active = false;
	 key3->active = false;
	 key4->active = false;
	 key5->active = false;


	D1->active = false;
	D2->active = false;
	D3->active = false;
	D4->active = false;
	D5->active = false;
	DB->active = false;
	back_dung->active = false;
	Back_dung->active = false;

}

void Main_Screen::Enable_dungeons()
{

	d1->active = true;
	d2->active = true;
	d3->active = true;
	d4->active = true;
	d5->active = true;
	dungeon_boss->active = true;

	key1->active = true;
	key2->active = true;
	key3->active = true;
	key4->active = true;
	key5->active = true;


	D1->active = true;
	D2->active = true;
	D3->active = true;
	D4->active = true;
	D5->active = true;
	DB->active = true;
	//Back_dung->active = true;
	//back_dung->active = true;
}
