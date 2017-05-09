#include "Main_Screen.h"

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
	AddRoom(0, 0);
	App->player->room = { 0,0 };
	bool ret = true;
	App->player->inMainScreen = true;
	fx = App->audio->LoadFx("Audio/Fx/cursor.wav");
	press_fx = App->audio->LoadFx("Audio/Fx/button.wav");
	tex = App->tex->Load("Sprites/TitleScreen.png");
	//App->render->camera.w = 1920;
	//App->render->camera.h = 1200;

	background = (GuiImage*)App->gui->CreateElement(image);
	background->pos = { 0,0 };
	background->texture = tex;
	background->texture_rect = { 0,0,1024,768 };
	background->active = true;
	background->movable = true;


	New_game = (GuiImage*)App->gui->CreateElement(image);
	New_game->pos = { 250 , 350 };
	New_game->texture_rect = { 0 , 514, 683,36 };
	New_game->active = true;
	New_game->movable = true;
	ui_elements.push_back(New_game);

	new_game = (GuiText*)App->gui->CreateElement(text);
	new_game->str = "New Game";
	new_game->active = true;
	new_game->movable = true;
	new_game->pos = { New_game->pos.x + 550, New_game->pos.y + 2 };



	Continue = (GuiImage*)App->gui->CreateElement(image);
	Continue->pos = { New_game->pos.x,New_game->pos.y + 100 };
	Continue->texture_rect = { 0 , 514, 683,36 };
	Continue->active = true;
	Continue->movable = true;
	ui_elements.push_back(Continue);

	cont = (GuiText*)App->gui->CreateElement(text);
	cont->str = "Continue";
	cont->active = true;
	cont->movable = true;
	cont->pos = { Continue->pos.x + 550, Continue->pos.y + 2 };



	Settings = (GuiImage*)App->gui->CreateElement(image);
	Settings->pos = { Continue->pos.x,Continue->pos.y + 100 };
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

	Back = (GuiImage*)App->gui->CreateElement(image);
	Back->pos = { Mute->pos.x,Mute->pos.y + 100 };
	Back->texture_rect = { 0, 514, 683, 36 };
	Back->active = false;
	Back->movable = true;
	settings_elements.push_back(Back);

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
	up->pos = { Up->pos.x + 550, Up->pos.y + 2 };

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
	down->pos = { Down->pos.x + 550, Down->pos.y + 2 };

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
	right->pos = { Right->pos.x + 550, Right->pos.y + 2 };

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
	left->pos = { Left->pos.x + 550, Left->pos.y + 2 };

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
	move_up->pos = { Move_up->pos.x + 550, Move_up->pos.y + 2 };

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
	move_down->pos = { Move_down->pos.x + 550, Move_down->pos.y + 2 };

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
	move_right->pos = { Move_right->pos.x + 550, Move_right->pos.y + 2 };

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
	move_left->pos = { Move_left->pos.x + 550, Move_left->pos.y + 2 };

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
	menu->pos = { Menu->pos.x + 550, Menu->pos.y + 2 };

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
	action->pos = { Action->pos.x + 550, Action->pos.y + 2 };

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
	dash->pos = { Dash->pos.x + 550, Dash->pos.y + 2 };

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

	App->audio->PlayMusic("Audio/Music/Opening.ogg");



	selected = New_game;

	in_settings = false;
	in_controls = false;

	return ret;
}

bool Main_Screen::Update(float dt)
{
	bool ret = true;
	if (in_settings) {

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


		for (std::list<UIElement*>::const_iterator it = settings_elements.cbegin(); it != settings_elements.cend(); it++) {
			if (selected == it._Ptr->_Myval) {
				it._Ptr->_Myval->texture_rect = { 0,473,683,36 };
			}
			else {
				it._Ptr->_Myval->texture_rect = { 0, 514, 683, 36 };
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
			App->audio->PlayFx(fx);
			selected = Settings_Prev();
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
			App->audio->PlayFx(fx);
			selected = Settings_Next();

		}
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			App->audio->PlayFx(press_fx);
			if (selected == Controls) {
				in_settings = false;
				in_controls = true;
				selected = controls_elements.front();

			}
			if (selected == Mute) {
				//mute the app
			}
			if (selected == Back) {

				selected = ui_elements.front();
				in_settings = false;
				in_controls = false;
			}

		}


	}
	else if (in_controls) {

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

		for (std::list<UIElement*>::const_iterator it = controls_elements.cbegin(); it != controls_elements.cend(); it++) {
			if (selected == it._Ptr->_Myval) {
				it._Ptr->_Myval->texture_rect = { 0,473,683,36 };
			}
			else {
				it._Ptr->_Myval->texture_rect = { 0, 514, 683, 36 };
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
			App->audio->PlayFx(fx);
			selected = Controls_Prev();
			/*if (!IsInsideCam(selected)) {
			Scroll_Down();
			}*/
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
			App->audio->PlayFx(fx);
			selected = Controls_Next();
			/*if (!IsInsideCam(selected)) {
			Scroll_Up();
			}*/

		}
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			App->audio->PlayFx(press_fx);
			if (selected == Up) {
				// go to change controls scene

			}
			if (selected == Down) {
				//mute the app
			}
			if (selected == Right) {

			}
			if (selected == Left) {
				//mute the app
			}
			if (selected == Move_left) {
				//mute the app
			}
			if (selected == Move_up) {
				//mute the app
			}
			if (selected == Move_down) {
				//mute the app
			}
			if (selected == Move_right) {
				//mute the app
			}
			if (selected == Menu) {
				//mute the app
			}
			if (selected == Action) {
				//mute the app
			}
			if (selected == Dash) {
				//mute the app
			}
			if (selected == Back_controls) {
				in_settings = true;
				in_controls = false;
				selected = settings_elements.front();
			}


		}


	}
	else {

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
			}
			else {
				it._Ptr->_Myval->texture_rect = { 0, 514, 683, 36 };
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
			App->audio->PlayFx(fx);
			selected = Prev();
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
			App->audio->PlayFx(fx);
			selected = Next();

		}
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			App->audio->PlayFx(press_fx);
			if (selected == New_game) {
				// start a new game, for now:
				App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
			}
			if (selected == Continue) {
				//continue with the current game, for now:
				App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
			}
			if (selected == Settings) {
				in_settings = true;
				selected = settings_elements.front();
			}
			if (selected == Exit) {
				//close the app

			}
		}
	}






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
	bool ret = true;
	App->player->inMainScreen = false;
	App->tex->UnLoad(tex);

	ui_elements.clear();
	settings_elements.clear();
	controls_elements.clear();

	up->active=false;
	down->active=false;
	right->active=false;
	left->active=false;
	move_up->active=false;
	move_down->active = false;
	move_right->active = false;
	move_left->active = false;
	menu->active = false;
	action->active = false;
	dash->active = false;
	back_controls->active= false;

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