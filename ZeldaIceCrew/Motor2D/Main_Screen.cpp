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

	GuiImage* background = (GuiImage*)App->gui->CreateElement(image);
	background->pos = { 0,0 };
	background->texture = App->tex->Load("Sprites/Main_Screen,png");
	background->texture_rect = { 0,0,1920,1200 };
	background->active = true;
	background->movable = true;


	GuiImage* New_game = (GuiImage*)App->gui->CreateElement(image);
	New_game->pos = { 400,250 };
	New_game->texture_rect = { 0,422,454,187 };
	New_game->active = true;
	New_game->movable = true;
	ui_elements.push_back(New_game);

	GuiText* new_game = (GuiText*)App->gui->CreateElement(text);
	new_game->str = "New Game";
	new_game->pos = { New_game->pos.x + 50, New_game->pos.y + 50 };
	new_game->active = true;

	GuiImage* Continue = (GuiImage*)App->gui->CreateElement(image);
	Continue->pos = { New_game->pos.x,New_game->pos.y+100 };
	Continue->texture_rect = { 0,422,454,187 };
	Continue->active = true;
	Continue->movable = true;
	ui_elements.push_back(Continue);

	GuiText* cont = (GuiText*)App->gui->CreateElement(text);
	cont->str = "Continue";
	cont->pos = { Continue->pos.x + 50, Continue->pos.y + 50 };
	cont->active = true;

	GuiImage* Exit = (GuiImage*)App->gui->CreateElement(image);
	Exit->pos = { Continue->pos.x,Continue->pos.y + 100 };
	Exit->texture_rect = { 0,422,454,187 };
	Exit->active = true;
	Exit->movable = true;
	ui_elements.push_back(Exit);

	GuiText* exit = (GuiText*)App->gui->CreateElement(text);
	exit->str = "Exit";
	exit->pos = { Exit->pos.x + 50, Exit->pos.y + 50 };
	exit->active = true;

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








	return ret;
}
