#include "HUD.h"
#include "Item.h"
#include "j1Player.h"
bool HUD::Start()
{
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
	rupees_num->str = std::to_string(App->player->rupees);
	rupees_num->pos = { 50,40 };

	bombs_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	bombs_num->active = true;
	bombs_num->str = std::to_string(App->player->bombs);
	bombs_num->pos = { 125,40 };

	arrows_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	arrows_num->active = true;
	arrows_num->str = std::to_string(App->player->arrows);
	arrows_num->pos = { 200,40 };

	inv = (Window*)App->gui->CreateElement(GuiType::window);
	inv->active = false;
	inv->pos = { 50,100 };
	inv->texture_rect = {0,0,430,351};


	GenerateHP();

	if (!App->player->inventory.empty()) {
		for (std::list<Item*>::const_iterator it = App->player->inventory.cbegin(); it != App->player->inventory.cend(); it++) {
			GuiImage* img = (GuiImage*)App->gui->CreateElement(GuiType::image);
			img->texture = it._Ptr->_Myval->UI_tex;
			img->texture_rect = it._Ptr->_Myval->UI_rect;

			inv->AddElement(img);
		}
	}

	inv->SetOffset(30,30);

	return ret;
}

bool HUD::Update(float dt)
{
	rupees_num->str = std::to_string(App->player->rupees);
	bombs_num->str = std::to_string(App->player->bombs);
	arrows_num->str = std::to_string(App->player->arrows);

	UpdateHP();
	
	return true;
}

bool HUD::CleanUp()
{
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

		if ((i>=App->player->curr_life_points)&&(i<App->player->max_life_points)) {
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
		img->texture = obj->UI_tex;
		img->active = false;
		App->hud->inv->AddElement(img);
	}
}
