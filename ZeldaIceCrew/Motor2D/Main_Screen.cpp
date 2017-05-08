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
	bool ret = true;
	App->player->inMainScreen = true;
	//App->render->camera.w = 1920;
	//App->render->camera.h = 1200;

	GuiImage* background = (GuiImage*)App->gui->CreateElement(image);
	background->pos = { 0,0 };
	background->texture = App->tex->Load("Sprites/Main_Screen.png");
	background->texture_rect = { 0,0,1920,1200 };
	background->active = true;
	background->movable = true;


	New_game = (GuiImage*)App->gui->CreateElement(image);
	New_game->pos = { 400, 150 };
	New_game->texture_rect = { 0,422,454,187 };
	New_game->active = true;
	New_game->movable = true;
	ui_elements.push_back(New_game);

	

	Continue = (GuiImage*)App->gui->CreateElement(image);
	Continue->pos = { New_game->pos.x,New_game->pos.y+200 };
	Continue->texture_rect = { 0,422,454,187 };
	Continue->active = true;
	Continue->movable = true;
	ui_elements.push_back(Continue);

	

	Settings = (GuiImage*)App->gui->CreateElement(image);
	Settings->pos = { Continue->pos.x,Continue->pos.y + 200 };
	Settings->texture_rect = { 0,422,454,187 };
	Settings->active = true;
	Settings->movable = true;
	ui_elements.push_back(Settings);

	

	
	Exit = (GuiImage*)App->gui->CreateElement(image);
	Exit->pos = { Settings->pos.x,Settings->pos.y + 200 };
	Exit->texture_rect = { 0,422,454,187 };
	Exit->active = true;
	Exit->movable = true;
	ui_elements.push_back(Exit);

	
	App->audio->PlayMusic("Audio/Music/Opening.ogg");



	selected = New_game;














	return ret;
}

bool Main_Screen::Update(float dt)
{
	bool ret = true;

	for (std::list<UIElement*>::const_iterator it = ui_elements.cbegin(); it != ui_elements.cend(); it++) {
		if (selected == it._Ptr->_Myval) {
			it._Ptr->_Myval->texture_rect = { 0,649,455,188 };
		}
		else{
			it._Ptr->_Myval->texture_rect = { 0,422,454,187 };
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
		selected = Next();
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
		selected = Prev();
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		if (selected == New_game) {
			// start a new game, for now:
			App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
		}
		if (selected == Continue) {
			//continue with the current game, for now:
			App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
		}
		if (selected == Settings) {
			//open settings menu
			App->scene_manager->ChangeScene((Scene*)App->scene_manager->dungeon_scene);
		}
		if (selected == Exit) {
			//close the app

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
	return nullptr;
}
