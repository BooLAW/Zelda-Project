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
	//App->render->camera.w = 1920;
	//App->render->camera.h = 1200;

	background = (GuiImage*)App->gui->CreateElement(image);
	background->pos = { 0,0 };
	background->texture = App->tex->Load("Sprites/TitleScreen.png");
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
	new_game->pos = { New_game->pos.x + 550, New_game->pos.y+2 };

	

	Continue = (GuiImage*)App->gui->CreateElement(image);
	Continue->pos = { New_game->pos.x,New_game->pos.y+100 };
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
	Controls->pos = {250,350};
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


	App->audio->PlayMusic("Audio/Music/Opening.ogg");



	selected = New_game;


	return ret;
}

bool Main_Screen::Update(float dt)
{
	bool ret = true;
	if (in_settings) {
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
				// go to change controls scene
				
			}
			if (selected == Mute) {
				//mute the app
			}
			if (selected == Back) {

				selected = ui_elements.front();
				in_settings = false;
			}
		
		}


	}
	else{
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
		else{ 
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
			for (std::list<UIElement*>::const_iterator it =ui_elements.cend(); it != ui_elements.cbegin(); it--) {
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

bool Main_Screen::CleanUp()
{
	App->player->inMainScreen = false;
	bool ret = true;
	
	for (std::list<UIElement*>::const_iterator it = ui_elements.cbegin(); it != ui_elements.cend(); it++) {
		App->gui->DeleteElement(it._Ptr->_Myval);
	}
	ui_elements.clear();
	App->gui->DeleteElement(background);
	App->gui->DeleteElement(new_game);
	App->gui->DeleteElement(cont);
	App->gui->DeleteElement(settings);
	App->gui->DeleteElement(exit);

	for (std::list<UIElement*>::const_iterator it = settings_elements.cbegin(); it != settings_elements.cend(); it++) {
		App->gui->DeleteElement(it._Ptr->_Myval);
	}
	App->gui->DeleteElement(controls);
	App->gui->DeleteElement(mute);
	App->gui->DeleteElement(back);
	return ret;
}
