#include "HUD.h"
#include "Item.h"
#include "j1Player.h"
bool HUD::Start()
{

	map0 = App->tex->Load("Sprites/mace_knight_minimap.png");
	map1 = App->tex->Load("Sprites/id1.png");
	map2 = App->tex->Load("Sprites/id2.png");
	map3 = App->tex->Load("Sprites/id3.png");
	map4 = App->tex->Load("Sprites/id4.png");

	items = App->tex->Load("Sprites/Items32x32.png");
	max_keys = 5;
	bool ret = true;

	Minimap = (GuiImage*)App->gui->CreateElement(image);
	Minimap->pos = { 250 ,150 };
	Minimap->texture = App->tex->Load("Sprites/mace_knight_minimap.png");
	Minimap->texture_rect = { 0,0,500,235 };
	Minimap->active = false;
	Minimap->movable = true;

	link_point = (GuiImage*)App->gui->CreateElement(image);
	link_point->pos = { Minimap->pos.x + 200, Minimap->pos.y + 115 };
	link_point->texture_rect = { 1023,412,22,33 };
	link_point->active = false;
	link_point->movable = true;

	rupees = (GuiImage*)App->gui->CreateElement(GuiType::image);
	rupees->texture_rect = { 644,411,32,32 };
	rupees->active = true;
	rupees->pos = { 50,10 };
	rupees->max_prior = true;

	/*bombs = (GuiImage*)App->gui->CreateElement(GuiType::image);
	bombs->texture_rect = { 702,411,32,32 };
	bombs->active = true;
	bombs->pos = { 125,10 };
	bombs->max_prior = true;*/


	life_icon = (GuiImage*)App->gui->CreateElement(GuiType::image);
	life_icon->texture_rect = { 735,462,176,28 };
	life_icon->active = true;
	life_icon->pos = { 750,10 };
	life_icon->max_prior = true;

	rupees_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	rupees_num->active = true;
	rupees_num->movable = true;
	rupees_num->str = std::to_string(App->player->rupees);
	rupees_num->pos = { 50,40 };

	/*bombs_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	bombs_num->active = true;
	bombs_num->movable = true;
	bombs_num->str = std::to_string(App->player->bombs);
	bombs_num->pos = { 125,40 };*/


	inv = (Window*)App->gui->CreateElement(GuiType::window);
	inv->active = false;
	inv->pos = {  50,100 };
	inv->texture_rect = { 0,0,430,351 };
	inv->max_prior = true;

	descriptions_rect = (GuiImage*)App->gui->CreateElement(GuiType::image);
	descriptions_rect->movable = true;
	descriptions_rect->pos = { inv->pos.x, inv->pos.y + inv->texture_rect.h + 1 };
	descriptions_rect->texture_rect = { 697,591,434,115 };
	descriptions_rect->active = false;
	descriptions_rect->max_prior = true;

	item_description = (GuiText*)App->gui->CreateElement(GuiType::text);
	item_description->active = false;
	item_description->movable = true;
	item_description->pos = { descriptions_rect->pos.x + 15, descriptions_rect->pos.y + 5 };
	item_description->max_prior = true;

	stats_rect = (GuiImage*)App->gui->CreateElement(GuiType::image);
	stats_rect->movable = true;
	stats_rect->active = false;
	stats_rect->pos = { descriptions_rect->pos.x + descriptions_rect->texture_rect.w + 1,descriptions_rect->pos.y };
	stats_rect->texture_rect = { 498,223,218,116 };
	stats_rect->max_prior = true;

	speed = (GuiImage*)App->gui->CreateElement(GuiType::image);
	speed->pos = { stats_rect->pos.x + 10, stats_rect->pos.y + 5 };
	speed->active = false;
	speed->movable = true;
	speed->texture = App->hud->items;
	speed->texture_rect = { 0, 326, 32, 32 };
	speed->max_prior = true;

	speed_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	speed_num->active = false;
	speed_num->movable = true;
	speed_num->pos = { speed->pos.x + 40,speed->pos.y };
	speed_num->max_prior = true;

	power = (GuiImage*)App->gui->CreateElement(GuiType::image);
	power->pos = { stats_rect->pos.x + 10, stats_rect->pos.y + speed->texture_rect.h + 20 };
	power->active = false;
	power->movable = true;
	power->texture = App->hud->items;
	power->texture_rect = { 40, 326, 32, 32 };
	power->max_prior = true;

	power_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	power_num->active = false;
	power_num->movable = true;
	power_num->pos = { power->pos.x + 40,power->pos.y };
	power_num->max_prior = true;

	weapon_rect = (GuiImage*)App->gui->CreateElement(GuiType::image);
	weapon_rect->pos = { 900,700 };
	weapon_rect->active = true;
	weapon_rect->movable = true;
	weapon_rect->texture_rect = { 539,402,46,48 };
	weapon_rect->max_prior = true;

	pl_weapon= (GuiImage*)App->gui->CreateElement(GuiType::image);
	pl_weapon->pos.x = weapon_rect->pos.x + 10;
	pl_weapon->pos.y = weapon_rect->pos.y + 10;
	pl_weapon->active = true;
	pl_weapon->movable = true;
	pl_weapon->texture = App->hud->items;
	pl_weapon->texture_rect = App->player->curr_weapon->UI_rect;
	pl_weapon->max_prior = true;


	dialog_rect = (GuiImage*)App->gui->CreateElement(GuiType::image);
	dialog_rect->texture_rect = { 625,733,613,77 };
	dialog_rect->active = false;
	dialog_rect->pos = { power->pos.x - 450,power->pos.y };

	dialog = (GuiText*)App->gui->CreateElement(GuiType::text);
	dialog->active = false;
	dialog->movable = true;
	dialog->pos = { dialog_rect->pos.x + 10, dialog_rect->pos.y + 10 };

	GenerateHP();

	if (!App->player->inventory.empty()) {
		for (std::list<Item*>::const_iterator it = App->player->inventory.cbegin(); it != App->player->inventory.cend(); it++) {
			if (!(App->player->Find_inv(it._Ptr->_Myval))) {
				GuiImage* img = (GuiImage*)App->gui->CreateElement(GuiType::image);
				img->texture = it._Ptr->_Myval->UI_tex;
				img->texture_rect = it._Ptr->_Myval->UI_rect;
				img->max_prior = true;
				inv->AddElement(img);
			}
		}
	}

	Menu = (GuiImage*)App->gui->CreateElement(image);
	Menu->texture = App->tex->Load("Sprites/Options_Menu.png");
	Menu->pos = { 250,100 };
	Menu->texture_rect = {0,0,484,560};
	Menu->active = false;
	Menu->movable = true;

	Continue = (GuiImage*)App->gui->CreateElement(image);
	Continue->pos = { Menu->pos.x+80,Menu->pos.y+100 };
	Continue->texture_rect = { 108,680,336,36 };
	Continue->active = false;
	Continue->movable = true;
	menu.push_back(Continue);

	titlescreen = (GuiImage*)App->gui->CreateElement(image);
	titlescreen->pos = { Continue->pos.x,Continue->pos.y + 100 };
	titlescreen->texture_rect = { 108,680,336,36 };
	titlescreen->active = false;
	titlescreen->movable = true;
	menu.push_back(titlescreen);

	Exit = (GuiImage*)App->gui->CreateElement(image);
	Exit->pos = { titlescreen->pos.x,titlescreen->pos.y + 100 };
	Exit->texture_rect = { 108,680,336,36 };
	Exit->active = false;
	Exit->movable = true;
	menu.push_back(Exit);

	cont = (GuiText*)App->gui->CreateElement(text);
	cont->pos = { Continue->pos.x + 50, Continue->pos.y + 2 };
	cont->str = "Continue";
	cont->active = false;
	cont->movable = true;

	title = (GuiText*)App->gui->CreateElement(text);
	title->pos = { titlescreen->pos.x + 50, titlescreen->pos.y + 2 };
	title->str = "Main Menu";
	title->active = false;
	title->movable = true;

	exit = (GuiText*)App->gui->CreateElement(text);
	exit->pos = { Exit->pos.x + 50, Exit->pos.y + 2 };
	exit->str = "Exit";
	exit->active = false;
	exit->movable = true;

	GenerateKeys();

	menu_selected = Continue;
	minimap = false;
	Minimap->active = false;
	link_point->active = false;

	
	inv->SetOffset(30, 30);

	return ret;
}

bool HUD::Update(float dt)
{
	
	bool ret = true;
	
	if (App->scene_manager->dungeon_id == 0) {
		Minimap->texture = map0;
		Minimap->texture_rect = { 0,0,500,235 };
	}
	if (App->scene_manager->dungeon_id == 1) {
		Minimap->texture = map1;
		Minimap->texture_rect = { 0,0,325,266 };
	}
	if (App->scene_manager->dungeon_id == 2) {
		Minimap->texture = map2;
		Minimap->texture_rect = { 0,0,667,187 };
	}
	if (App->scene_manager->dungeon_id == 3) {
		Minimap->texture = map3;
		Minimap->texture_rect = { 0,0,416,188 };

	}
	if (App->scene_manager->dungeon_id == 4) {
		Minimap->texture = map4;
		Minimap->texture_rect = { 0,0,340,278 };

	}

	rupees_num->str = std::to_string(App->player->rupees);
	//bombs_num->str = std::to_string(App->player->bombs);
	speed_num->str = std::to_string(App->player->pl_speed.x);
	power_num->str = std::to_string(App->player->power);
	pl_weapon->texture_rect = App->player->curr_weapon->UI_rect;
	UpdateKeys();

	if (App->player->inMainScreen) {
		rupees->active = false;
//		bombs->active = false;
		life_icon->active = false;
		rupees_num->active = false;
		//bombs_num->active = false;
		for (std::list<GuiImage*>::const_iterator it = lifes.cbegin(); it != lifes.cend(); it++) {
			it._Ptr->_Myval->active = false;
		}
		pl_weapon->active = false;
		weapon_rect->active = false;
		Menu->active = false;
		Continue->active = false;
		titlescreen->active = false;
		Exit->active = false;
		cont->active = false;
		title->active = false;
		exit->active = false;
		menu_selected = nullptr;
		Minimap->active = false;
		link_point->active = false;
		Disable_keys();

	}

	else {
		Enable_keys();
		rupees->active = true;
		//bombs->active = true;
		life_icon->active = true;
		rupees_num->active = true;
	//	bombs_num->active = true;
		for (std::list<GuiImage*>::const_iterator it = lifes.cbegin(); it != lifes.cend(); it++) {
			it._Ptr->_Myval->active = true;
		}
		pl_weapon->active = true;
		weapon_rect->active = true;

		if (App->player->talking) {
			dialog_rect->active = true;
		}
		else {
			dialog_rect->active = false;
		}
		if (!App->player->inMainScreen) {
			if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
				if (!Minimap->active) {
					Minimap->active = true;
					link_point->active = true;
					App->Pause();
				}
				else {
					Minimap->active = false;
					link_point->active = false;
					App->UnPause();
				}
			}
		}
		if (inv->active) {
			descriptions_rect->active = true;
			stats_rect->active = true;
			speed->active = true;
			speed_num->active = true;
			power->active = true;
			power_num->active = true;
			//weapons->active = true;
			if (!inv->Empty()) {
				if (inv->Selected() != nullptr) {
					item_description->active = true;
					item_description->str = inv->Selected()->obj->description;
				}

			}
		}
		else {
			inv->Disable();
			descriptions_rect->active = false;
			item_description->active = false;
			stats_rect->active = false;
			speed->active = false;
			speed_num->active = false;
			power->active = false;
			power_num->active = false;
			
		}
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			if (!Menu->active) {
				inv->Disable();
				descriptions_rect->active = false;
				item_description->active = false;
				stats_rect->active = false;
				speed->active = false;
				speed_num->active = false;
				power->active = false;
				power_num->active = false;
				minimap = false;
				

				menu_selected = Continue;
				App->Pause();
				Menu->active = true;
				Continue->active = true;
				titlescreen->active = true;
				Exit->active = true;
				cont->active = true;
				title->active = true;
				exit->active = true;

			}
			else {
				App->UnPause();
				menu_selected = Continue;
				Menu->active = false;
				Continue->active = false;
				titlescreen->active = false;
				Exit->active = false;
				cont->active = false;
				title->active = false;
				exit->active = false;
			}
		}
				if (Menu->active) {
					for (std::list<UIElement*>::const_iterator it = menu.cbegin(); it != menu.cend(); it++) {
						if (menu_selected == it._Ptr->_Myval) {
							it._Ptr->_Myval->texture_rect = { 109,601,336,36 };
						}
						else {
							it._Ptr->_Myval->texture_rect = { 108,680,336,36 };
						}
					}
					
						if (App->input->GetKey(SDL_SCANCODE_UP)==KEY_DOWN) {
							menu_selected = menu_prev();
						}
						if (App->input->GetKey(SDL_SCANCODE_DOWN)==KEY_DOWN) {
							menu_selected = menu_next();
				}
						if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
							if (menu_selected == Continue) {
								App->UnPause();
								Menu->active = false;
								Continue->active = false;
								titlescreen->active = false;
								Exit->active = false;
								cont->active = false;
								title->active = false;
								exit->active = false;
							}
							if (menu_selected == titlescreen) {
								App->player->inMainScreen = true;
								if (App->IsPaused()) {
									App->UnPause();
								}
								App->scene_manager->ChangeScene((Scene*)App->scene_manager->main_screen);
							}
							if (menu_selected == Exit) {
								ret = false;
							}

						}
			}
		UpdateHP();
	}
	return ret;
}

bool HUD::CleanUp()
{
	menu_selected = nullptr;
	App->tex->UnLoad(items);
	App->tex->UnLoad(Menu->texture);
	menu.clear();
	lifes.clear();
	pl_keys.clear();
	return true;
}



void HUD::GenerateHP()
{
	iPoint heart_pos = { 750,50 };

	for (uint i = 0; i <= App->player->max_life_points; i++) {
		if (i <= App->player->curr_life_points) {
			if ((i % 2 == 0) && (i != 0)) {
				GuiImage* img;
				img = (GuiImage*)App->gui->CreateElement(GuiType::image);
				img->active = true;
				img->texture_rect = { 897,418,28,28 };
				img->pos = heart_pos;;
				heart_pos += {30, 0};
				lifes.push_back(img);
			}

			if ((i == App->player->curr_life_points) && (i % 2 != 0)) {
				GuiImage* img;
				img = (GuiImage*)App->gui->CreateElement(GuiType::image);
				img->active = true;
				img->texture_rect = { 940,416,28,28 };
				img->pos = heart_pos;
				heart_pos += {30, 0};
				lifes.push_back(img);
			}
		}

		if ((i >= App->player->curr_life_points) && (i<App->player->max_life_points)) {
			if ((i % 2 == 0)) {
				GuiImage* img;
				img = (GuiImage*)App->gui->CreateElement(GuiType::image);
				img->active = true;
				img->texture_rect = { 986,416,28,28 };
				img->pos = heart_pos;
				heart_pos += {30, 0};
				lifes.push_back(img);
			}

		}

	}
}

void HUD::GenerateKeys()
{
	iPoint pos = {rupees->pos.x+ 75 ,rupees->pos.y+5};
	for (uint i = 0; i < max_keys; i++) {
		GuiImage* img = (GuiImage*)App->gui->CreateElement(image);
		img->pos = pos;
		img->texture_rect = { 939,455,28,32 };
		img->active = true;
		img->movable = true;
		pl_keys.push_back(img);
		pos.x += 30;
	}
}

void HUD::UpdateKeys()
{
	int i = 0;
	for (std::list<UIElement*>::const_iterator it = pl_keys.cbegin(); it != pl_keys.cend(); it++) {
		if (i < App->player->keys) {
			it._Ptr->_Myval->texture_rect = { 977,455,28,32 };
		}
		else {
			it._Ptr->_Myval->texture_rect = { 939,455,28,32 };
		}
		i++;
	}
}

void HUD::Disable_keys()
{
	for (std::list<UIElement*>::const_iterator it = pl_keys.cbegin(); it != pl_keys.cend(); it++) {
		it._Ptr->_Myval->active = false;
	}
}

void HUD::Enable_keys()
{
	for (std::list<UIElement*>::const_iterator it = pl_keys.cbegin(); it != pl_keys.cend(); it++) {
		it._Ptr->_Myval->active = true;
	}
}

void HUD::UpdateHP()
{
	for (std::list<GuiImage*>::const_iterator it = lifes.cbegin(); it != lifes.cend(); it++) {
		App->gui->elements.remove(it._Ptr->_Myval);
	}
	lifes.clear();

	GenerateHP();
}

UIElement * HUD::menu_next()
{
	if (menu_selected != nullptr) {
		if (!menu.empty()) {
			if (menu_selected == menu.back()) {
				return menu.back();
			}
			else {
				for (std::list<UIElement*>::const_iterator it = menu.cbegin(); it != menu.cend(); it++) {
					if (menu_selected == it._Ptr->_Myval) {
						if (menu_selected == menu.back()) {
							return menu.back();
						}
						else {
							it++;
							if (it._Ptr != nullptr)
								return it._Ptr->_Myval;
							else
								return menu.back();
						}
					}
				}
			}
		}
	}
}

UIElement * HUD::menu_prev()
{
	if (menu_selected != nullptr) {
		if (!menu.empty()) {
			if (menu_selected == menu.front()) {
				return menu.front();
			}
			for (std::list<UIElement*>::const_iterator it = menu.cend(); it != menu.cbegin(); it--) {
				if (menu_selected == it._Ptr->_Myval) {
					if (menu_selected == menu.front()) {
						return menu.front();
					}
					else {
						it--;
						if (it._Ptr != nullptr)
							return it._Ptr->_Myval;
						else
							return menu.back();
					}
				}


			}
		}
	}
}

void HUD::AddItem(Item* obj)
{

	if (obj != nullptr) {
		GuiImage* img = (GuiImage*)App->gui->CreateElement(GuiType::image);
		img->texture_rect = obj->UI_rect;
		img->texture = items;
		img->active = false;
		img->obj = obj;

		if (inv->Empty()) {
			inv->Start_Sel({ 594,402,47,47 });
			App->hud->inv->AddElement(img);
		}
		else {
			App->hud->inv->AddElement(img);
		}
	}
}

void HUD::AddWeapon(Item* wep)
{
	if (wep != nullptr) {
		GuiImage* img = (GuiImage*)App->gui->CreateElement(GuiType::image);
		img->texture_rect = wep->UI_rect;
		img->texture = items;
		img->active = false;
		//img->obj = wep;

		/*if (inv->Empty()) {
			inv->Start_Sel({ 594,402,47,47 });
			App->hud->weapons->AddElement(img);
		}*/
		
			//App->hud->weapons->AddElement(img);
		
	}
}
