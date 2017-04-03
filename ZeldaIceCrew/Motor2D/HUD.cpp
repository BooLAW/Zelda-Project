#include "HUD.h"
#include "Item.h"
#include "j1Player.h"
bool HUD::Start()
{

	items = App->tex->Load("Sprites/Items32x32.png");
	bool ret = true;

	rupees = (GuiImage*)App->gui->CreateElement(GuiType::image);
	rupees->texture_rect = { 644,411,32,32 };
	rupees->active = true;
	rupees->pos = { 50,10 };

	bombs = (GuiImage*)App->gui->CreateElement(GuiType::image);
	bombs->texture_rect = { 702,411,32,32 };
	bombs->active = true;
	bombs->pos = { 125,10 };

	arrows = (GuiImage*)App->gui->CreateElement(GuiType::image);
	arrows->texture_rect = { 766,412,57,32 };
	arrows->active = true;
	arrows->pos = { 200,10 };

	life_icon = (GuiImage*)App->gui->CreateElement(GuiType::image);
	life_icon->texture_rect = { 735,462,176,28 };
	life_icon->active = true;
	life_icon->pos = { 750,10 };

	rupees_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	rupees_num->active = true;
	rupees_num->movable = true;
	rupees_num->str = std::to_string(App->player->rupees);
	rupees_num->pos = { 50,40 };

	bombs_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	bombs_num->active = true;
	bombs_num->movable = true;
	bombs_num->str = std::to_string(App->player->bombs);
	bombs_num->pos = { 125,40 };

	arrows_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	arrows_num->active = true;
	arrows_num->movable = true;
	arrows_num->str = std::to_string(App->player->arrows);
	arrows_num->pos = { 200,40 };

	inv = (Window*)App->gui->CreateElement(GuiType::window);
	inv->active = false;
	inv->pos = { 50,100 };
	inv->texture_rect = { 0,0,430,351 };

	descriptions_rect = (GuiImage*)App->gui->CreateElement(GuiType::image);
	descriptions_rect->movable = true;
	descriptions_rect->pos = { inv->pos.x, inv->pos.y + inv->texture_rect.h + 1 };
	descriptions_rect->texture_rect = { 697,591,434,115 };
	descriptions_rect->active = false;

	item_description = (GuiText*)App->gui->CreateElement(GuiType::text);
	item_description->active = false;
	item_description->movable = true;
	item_description->pos = { descriptions_rect->pos.x + 15, descriptions_rect->pos.y + 5 };

	stats_rect = (GuiImage*)App->gui->CreateElement(GuiType::image);
	stats_rect->movable = true;
	stats_rect->active = false;
	stats_rect->pos = { descriptions_rect->pos.x + descriptions_rect->texture_rect.w + 1,descriptions_rect->pos.y };
	stats_rect->texture_rect = { 498,223,218,116 };

	speed = (GuiImage*)App->gui->CreateElement(GuiType::image);
	speed->pos = { stats_rect->pos.x + 10, stats_rect->pos.y + 5 };
	speed->active = false;
	speed->movable = true;
	speed->texture = App->hud->items;
	speed->texture_rect = { 0, 326, 32, 32 };

	speed_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	speed_num->active = false;
	speed_num->movable = true;
	speed_num->pos = { speed->pos.x + 40,speed->pos.y };

	power = (GuiImage*)App->gui->CreateElement(GuiType::image);
	power->pos = { stats_rect->pos.x + 10, stats_rect->pos.y + speed->texture_rect.h + 20 };
	power->active = false;
	power->movable = true;
	power->texture = App->hud->items;
	power->texture_rect = { 40, 326, 32, 32 };

	power_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	power_num->active = false;
	power_num->movable = true;
	power_num->pos = { power->pos.x + 40,power->pos.y };

	weapon_rect = (GuiImage*)App->gui->CreateElement(GuiType::image);
	weapon_rect->pos = { 900,500 };
	weapon_rect->active = true;
	weapon_rect->movable = true;
	weapon_rect->texture_rect = { 539,402,46,48 };

	pl_weapon= (GuiImage*)App->gui->CreateElement(GuiType::image);
	pl_weapon->pos.x = weapon_rect->pos.x + 10;
	pl_weapon->pos.y = weapon_rect->pos.y + 10;
	pl_weapon->active = true;
	pl_weapon->movable = true;
	pl_weapon->texture = App->hud->items;
	pl_weapon->texture_rect = App->player->curr_weapon->UI_rect;




	GenerateHP();

	if (!App->player->inventory.empty()) {
		for (std::list<Item*>::const_iterator it = App->player->inventory.cbegin(); it != App->player->inventory.cend(); it++) {
			GuiImage* img = (GuiImage*)App->gui->CreateElement(GuiType::image);
			img->texture = it._Ptr->_Myval->UI_tex;
			img->texture_rect = it._Ptr->_Myval->UI_rect;

			inv->AddElement(img);
		}
	}


	
	inv->SetOffset(30, 30);

	return ret;
}

bool HUD::Update(float dt)
{
	rupees_num->str = std::to_string(App->player->rupees);
	bombs_num->str = std::to_string(App->player->bombs);
	arrows_num->str = std::to_string(App->player->arrows);
	speed_num->str = std::to_string(App->player->pl_speed.x);
	power_num->str = std::to_string(App->player->power);
	pl_weapon->texture_rect = App->player->curr_weapon->UI_rect;
	if (inv->active) {
		descriptions_rect->active = true;
		stats_rect->active = true;
		speed->active = true;
		speed_num->active = true;
		power->active = true;
		power_num->active = true;
		if(!inv->Empty()){
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
	UpdateHP();

	return true;
}

bool HUD::CleanUp()
{
	App->tex->UnLoad(items);
	lifes.clear();
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

void HUD::UpdateHP()
{
	for (std::list<GuiImage*>::const_iterator it = lifes.cbegin(); it != lifes.cend(); it++) {
		App->gui->elements.remove(it._Ptr->_Myval);
	}
	lifes.clear();

	GenerateHP();
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
