#include "Item.h"

Item::Item(uint subtype)
{
	
}

void Item::PassToInventory()
{
	if (HitBox != nullptr) {
		HitBox->to_delete = true;
		HitBox->SetPos(0, 0);
	}
	if (tex != nullptr)
		App->tex->UnLoad(tex);

	if (priceTag != nullptr)
		priceTag->active = false;
	if (this->type == weapon) {

		App->hud->AddWeapon(this);
	}
	App->player->inventory.push_back(this);
	App->hud->AddItem(this);
	grabbed = true;

}

void Item::Update(float dt)
{
	//LOG("ITEM UPDATE");

		if (grabbed == false) {
			if (HitBox != nullptr) {
				if (HitBox->rect.x != pos.x || HitBox->rect.y != pos.y)
					HitBox->SetPos(pos.x, pos.y);

				if (type == ENTITYTYPE::drop) {
					drop_timer.Start();
					drop_timer.SetFlag(true);
					if (drop_timer.Read() > 5000) {
						App->scene_manager->GetCurrentScene()->DestroyItem(this);
					}
				}

				if (HitBox->CheckCollision(App->player->link_coll->rect)) {
					if (type == drop) {
						Upgrade();
						App->scene_manager->GetCurrentScene()->DestroyItem(this);
						App->audio->PlayFx(this->fx);
					}
					else{
						if (App->input->GetKey(App->input->controls[ACTION])) {
							if (App->player->rupees >= this->price) {
								App->player->rupees -= price;
								App->audio->PlayFx(this->fx);
								App->gui->DeleteElement(this->priceTag);
								if (type == ENTITYTYPE::drop) {
									Upgrade();
									App->scene_manager->GetCurrentScene()->DestroyItem(this);
								}
								else {
									if (App->player->Find_inv(this)) {
										Upgrade();
										App->scene_manager->GetCurrentScene()->DestroyItem(this);
									}
									else if (App->player->Find_weapon(this)) {
										App->scene_manager->GetCurrentScene()->DestroyItem(this);
									}
									else {
										Upgrade();
										PassToInventory();
									}
								}
							}
						}
				}
				}
			}
			if (set == false) {
				draw_pos = pos;
				set = true;
			}

		}
	

	if (priceTag != nullptr)
		priceTag->pos = { (int)this->pos.x, (int)this->pos.y};

	Draw(dt);

}

void Item::Draw(float dt)
{
	if (floating_up)
		draw_pos.y -= FLOATING_SPEED * dt;
	else
		draw_pos.y += FLOATING_SPEED * dt;

	if (draw_pos.x != pos.x)
		draw_pos.x = pos.x;

	if (draw_pos.y > pos.y + FLOATING_OFFSET)
		floating_up = true;
	if (draw_pos.y < pos.y - FLOATING_OFFSET)
		floating_up = false;

	if(HitBox != nullptr)
		App->render->toDraw(tex, draw_pos.y + this->HitBox->rect.h ,draw_pos.x, draw_pos.y, &rect);
}

void Item::CleanUp()
{


	if (HitBox != nullptr)
		HitBox->to_delete = true;
	if (tex != nullptr)
		App->tex->UnLoad(tex);

	if (priceTag != nullptr)
		priceTag->active = false;

	//App->scene_manager->GetCurrentScene()->DestroyItem(this);
}

void Item::Start()
{

	SetUp();
	
	draw_pos = pos;

	if(tex != nullptr)
		HitBox = App->collisions->AddCollider({ 0, 0, rect.w, rect.h }, COLLIDER_ITEM);

	priceTag = (GuiText*)App->gui->CreateElement(GuiType::text);
	priceTag->movable = false;
}

void PowerGauntlet::Upgrade()
{
	App->player->UpgradePWR(5);
}

void PowerGauntlet::SetUp()
{
	subtype = power_gauntlet;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 36, 0, 32, 32 };
	UI_tex = App->hud->items;
	UI_rect = { 40, 326, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "You feel the power";
}

void PegasusBoots::SetUp()
{
	subtype = pegasus_boots;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 0, 0, 32, 32 };
	UI_tex = App->hud->items;
	UI_rect = { 0, 326, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "Light and comfortable";
}

void PegasusBoots::Upgrade()
{
	App->player->UpgradeSPD(0.25);
}

void HeartContainer::SetUp()
{
	subtype = heart_container;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 0, 146, 32, 32 };
	UI_tex = App->hud->items;
	UI_rect = { 180, 362, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/heart_container_1.wav");
	description = "You feel... more resistant";

}

void HeartContainer::Upgrade()
{
	App->player->UpgradeHP(2);
}

void DropHeart::SetUp()
{
	subtype = drop_heart;
	type = ENTITYTYPE::drop;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 180, 40, 32, 26 };
	fx = App->audio->LoadFx("Audio/Fx/heart.wav");
	
	UI_tex = nullptr;

}

void DropHeart::Upgrade()
{
	App->player->curr_life_points += 2;
	if (App->player->curr_life_points > App->player->max_life_points)
		App->player->curr_life_points = App->player->max_life_points;
}

void DropPotion::SetUp()
{
	subtype = drop_potion;
	type = ENTITYTYPE::drop;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 144, 146, 28, 32 };

}

void DropPotion::Upgrade()
{
	App->player->curr_life_points += 6;
	if (App->player->curr_life_points > App->player->max_life_points)
		App->player->curr_life_points = App->player->max_life_points;
}

void DropRupee::SetUp()
{
	subtype = drop_rupee;
	type = ENTITYTYPE::drop;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 116, 254, 16, 28 };
	fx = App->audio->LoadFx("Audio/Fx/Rupee1.wav");

}

void DropRupee::Upgrade()
{
	App->player->rupees += 1;
	if (App->player->rupees > App->player->max_rupees)
		App->player->rupees = App->player->max_rupees;

}

void DropFiveRupee::SetUp()
{
	subtype = drop_fiverupee;
	type = ENTITYTYPE::drop;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 224, 254, 16, 28 };
	fx = App->audio->LoadFx("Audio/Fx/Rupee1.wav");
}

void DropFiveRupee::Upgrade()
{
	App->player->rupees += 5;
	if (App->player->rupees > App->player->max_rupees)
		App->player->rupees = App->player->max_rupees;
}

void DropTenRupee::SetUp()
{
	subtype = drop_tenrupee;
	type = ENTITYTYPE::drop;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 332, 254, 16, 28 };
	fx = App->audio->LoadFx("Audio/Fx/Rupee1.wav");
}

void DropTenRupee::Upgrade()
{
	App->player->rupees += 10;
	if (App->player->rupees > App->player->max_rupees)
		App->player->rupees = App->player->max_rupees;
}


void ItemBow::SetUp()
{
	subtype = weapon_bow;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 362, 74, 32, 32 };
	UI_tex = App->hud->items;
	UI_rect = { 362, 326, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	
}

void ItemBow::Upgrade()
{
	if (!App->player->Find_weapon(this)) {
		App->player->weapons.clear();
		App->player->AddWeapon(t_bow);
		App->player->curr_weapon = App->player->weapons.front();
	}
}

void ItemSword::SetUp()
{
	subtype = weapon_sword;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 252, 41, 32, 32 };
	UI_tex = App->hud->items;
	UI_rect = rect;
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "";
}

void ItemSword::Upgrade()
{
	if (!App->player->Find_weapon(this)) {
		App->player->weapons.clear();
		App->player->AddWeapon(t_sword);
		App->player->curr_weapon = App->player->weapons.front();
	}
}


void BossKey::Update(float dt)
{

	if (App->scene_manager->GetCurrentScene()->GetRoom(coords.x, coords.y)->NoEnemies() == true) {

		if (grabbed == false) {
			if (HitBox != nullptr) {
				if (HitBox->rect.x != pos.x || HitBox->rect.y != pos.y)
					HitBox->SetPos(pos.x, pos.y);

				if (HitBox->CheckCollision(App->player->link_coll->rect)) {
					if (App->player->rupees >= this->price) {
						App->player->rupees -= price;
						App->audio->PlayFx(this->fx);
						App->gui->DeleteElement(this->priceTag);
						if (type == ENTITYTYPE::drop) {
							Upgrade();
							App->scene_manager->GetCurrentScene()->DestroyItem(this);
						}
						else {
							if (App->player->Find_inv(this)) {
								Upgrade();
								App->scene_manager->GetCurrentScene()->DestroyItem(this);
							}
							else if (App->player->Find_weapon(this)) {
								App->scene_manager->GetCurrentScene()->DestroyItem(this);
							}
							else {
								Upgrade();
								//PassToInventory();
							}
						}
					}
				}
			}
			if (set == false) {
				draw_pos = pos;
				set = true;
			}

		}


		if (priceTag != nullptr)
			priceTag->pos = { (int)this->pos.x, (int)this->pos.y };

		Draw(dt);
	}
}

void BossKey::SetUp()
{
	subtype = boss_key;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 362, 144, 32, 34 };
	UI_tex = tex;
	UI_rect = { 360, 470, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void BossKey::Upgrade()
{
	App->player->curr_life_points = App->player->max_life_points;
	App->player->completed_maps[App->scene_manager->dungeon_id] = true;
	App->player->keys++;
	App->SaveGame("save_game.xml");
	App->scene_manager->toChangeScene((Scene*)App->scene_manager->main_screen);
}

void GoldenGauntlet::SetUp()
{
	subtype = gold_gauntlet;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 36, 36, 34, 35 };
	UI_tex = tex;
	UI_rect = { 36, 360, 34, 35 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "Empowered by the Din";
}

void GoldenGauntlet::Upgrade()
{
	App->player->UpgradePWR(15);
	App->player->UpgradeSPD(-0.25);
}

void WindCape::SetUp()
{
	subtype = wind_cape;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 34, 36, 34, 35 };
	UI_tex = tex;
	UI_rect = { 34, 360, 34, 35 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "By Nayru's light!";
}

void WindCape::Upgrade()
{
	App->player->UpgradePWR(-5);
	App->player->UpgradeSPD(0.5);
}

void MagicHammer::SetUp()
{
	subtype = magic_hammer;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 36, 108, 34, 35 };
	UI_tex = tex;
	UI_rect = { 36, 432, 34, 34 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "Now with a 100% less magic!";
}

void MagicHammer::Upgrade()
{
	App->player->UpgradePWR(15);
	App->player->UpgradeHP(-2);
}

void MagicSphere::SetUp()
{
	subtype = magic_sphere;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 108, 0, 34, 34 };
	UI_tex = tex;
	UI_rect = { 108, 324, 34, 34 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "Now with a 100% more magic!";
}

void MagicSphere::Upgrade()
{
	App->player->UpgradeHP(4);
	App->player->UpgradeSPD(-0.25);
}

void VanguardEmblem::SetUp()
{
	subtype = vanguard_emblem;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 37, 72, 34, 34 };
	UI_tex = tex;
	UI_rect = { 36, 396, 34, 34 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "A badge for true heroes";
}

void VanguardEmblem::Upgrade()
{
	App->player->UpgradeHP(4);
	App->player->UpgradePWR(-5);
}

void SmallShield::SetUp()
{
	subtype = small_shield;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 0, 72, 34, 34 };
	UI_tex = tex;
	UI_rect = { 0, 396, 34, 34 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void SmallShield::Upgrade()
{
	App->player->UpgradePWR(-5);
	App->player->UpgradeSPD(0.5);
	description = "The faster you go... the weaker you hit?";
}

void GoldenShield::SetUp()
{
	subtype = small_shield;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 72, 72, 34, 34 };
	UI_tex = tex;
	UI_rect = { 72, 396, 34, 34 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void GoldenShield::Upgrade()
{
	float aux = App->player->pl_speed.x;

	App->player->pl_speed.x = App->player->pl_speed.y = ((float)App->player->power * 0.083);

	if (App->player->pl_speed.x > MAX_SPD) {
		App->player->pl_speed.x = MAX_SPD;
		App->player->pl_speed.y = MAX_SPD;
	}
	if (App->player->pl_speed.x < MIN_SPD) {
		App->player->pl_speed = { MIN_SPD, MIN_SPD };
	}

	App->player->power = (int)(round(aux / 0.083));

	if (App->player->power > MAX_PWR)
		App->player->power = MAX_PWR;
	if (App->player->power < MIN_PWR)
		App->player->power = MIN_PWR;

}

void MagicMirror::SetUp()
{
	subtype = small_shield;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 216, 0, 34, 34 };
	UI_tex = tex;
	UI_rect = { 216, 324, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void MagicMirror::Upgrade()
{

	float aux = App->player->max_life_points;

	App->player->max_life_points = App->player->power / 5;

	App->player->power = (int)aux * 5;

	if (App->player->power > MAX_PWR)
		App->player->power = MAX_PWR;
	if (App->player->power < MIN_PWR)
		App->player->power = MIN_PWR;


	if (App->player->max_life_points > MAX_HP)
		App->player->max_life_points = MAX_HP;
	if (App->player->max_life_points < MIN_HP)
		App->player->max_life_points = MIN_HP;
}

void BagOfRupees::SetUp()
{
	subtype = bag_of_rupees;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 289, 109, 34, 34 };
	UI_tex = tex;
	UI_rect = { 289, 432, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "Get Greedier";
}

void BagOfRupees::Upgrade()
{
	App->player->max_rupees = 300;
}

void OddMushroom::SetUp()
{
	subtype = odd_mushroom;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 324, 72, 34, 34 };
	UI_tex = tex;
	UI_rect = { 324, 396, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void OddMushroom::Upgrade()
{
	float a_s = App->player->pl_speed.x * 0.083;
	float a_p = App->player->power;
	float a_h = App->player->max_life_points * 5;

	float a_temp;

	uint rnd = rand() % 2;
	
	switch (rnd) {
	case 0:
		std::swap(a_s, a_p);
		std::swap(a_p, a_h);
		break;
	case 1:
		std::swap(a_h, a_p);
		std::swap(a_p, a_s);
		break;
	}

	a_s = a_s / 0.083;
	a_h = a_h / 5;

	App->player->pl_speed.x = a_s;
	App->player->pl_speed.y = a_s;
	App->player->power = a_p;
	App->player->max_life_points = a_h;

	if (App->player->power > MAX_PWR)
		App->player->power = MAX_PWR;
	if (App->player->power < MIN_PWR)
		App->player->power = MIN_PWR;

	if (App->player->pl_speed.x > MAX_SPD) {
		App->player->pl_speed.x = MAX_SPD;
		App->player->pl_speed.y = MAX_SPD;
	}
	if (App->player->pl_speed.x < MIN_SPD) {
		App->player->pl_speed = { MIN_SPD, MIN_SPD };
	}

	if (App->player->max_life_points > MAX_HP)
		App->player->max_life_points = MAX_HP;
	if (App->player->max_life_points < MIN_HP)
		App->player->max_life_points = MIN_HP;

}

void MysteriousDust::SetUp()
{
	subtype = mysterious_dust;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 72, 216, 32, 34 };
	UI_tex = tex;
	UI_rect = { 180, 470, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void MysteriousDust::Upgrade()
{
	uint rnd_s = rand() % 3;
	int rnd_up = rand() % 2;

	rnd_up == 0 ? rnd_up = -1 : rnd_up = 1;

	switch (rnd_s) {
	case 0:
		App->player->UpgradeHP(rnd_up * 2);
		break;
	case 1:
		App->player->UpgradePWR(rnd_up * 5);
		break;
	case 2:
		App->player->UpgradeSPD(rnd_up * 0.25);
		break;
	}
	description = "You feel.. fuzzy :S";

}

void IconOfValor::SetUp()
{
	subtype = icon_of_valor;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 216, 72, 34, 34 };
	UI_tex = tex;
	UI_rect = { 216, 396, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "An icon of true Valor";
}

void IconOfValor::Upgrade()
{
	App->player->UpgradeHP(2);
	App->player->UpgradePWR(5);
	App->player->UpgradeSPD(0.25);

}

void IconOfWisdom::SetUp()
{
	subtype = icon_of_wisdom;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 252, 72, 32, 34 };
	UI_tex = tex;
	UI_rect = { 252, 396, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "An icon of true Wisdom";

}

void IconOfWisdom::Upgrade()
{
	float aux = App->player->power + App->player->max_life_points * 5 + ceil(App->player->pl_speed.x / 0.083);

	aux = ceil(aux / 3);

	App->player->power = aux;
	App->player->max_life_points = round(aux / 5);
	App->player->pl_speed.x = aux * 0.083;
	App->player->pl_speed.y = aux * 0.083;

	if (App->player->power > MAX_PWR)
		App->player->power = MAX_PWR;
	if (App->player->power < MIN_PWR)
		App->player->power = MIN_PWR;

	if (App->player->pl_speed.x > MAX_SPD) {
		App->player->pl_speed.x = MAX_SPD;
		App->player->pl_speed.y = MAX_SPD;
	}
	if (App->player->pl_speed.x < MIN_SPD) {
		App->player->pl_speed = { MIN_SPD, MIN_SPD };
	}

	if (App->player->max_life_points > MAX_HP)
		App->player->max_life_points = MAX_HP;
	if (App->player->max_life_points < MIN_HP)
		App->player->max_life_points = MIN_HP;

}

void IconOfPower::SetUp()
{
	subtype = icon_of_power;
	type = ENTITYTYPE::item;
	if (App->scene_manager->dungeon_id == 1) {
		tex = App->tex->Load("Sprites/Items32x32Retro.png");
	}
	else {
		tex = App->tex->Load("Sprites/Items32x32.png");
	}
	rect = { 180, 72, 34, 34 };
	UI_tex = tex;
	UI_rect = { 180, 396, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "An icon of true Power";

}

void IconOfPower::Upgrade()
{
	float aux = App->player->power;

	if (App->player->power < App->player->pl_speed.x / 0.083) {
		aux = App->player->pl_speed.x;
		if (aux / 0.083 < App->player->max_life_points * 5) {
			aux = App->player->max_life_points;
			App->player->UpgradeHP(4);
		}
		else {
			App->player->UpgradeSPD(0.5);
		}
	}
	else {
		if (aux < App->player->max_life_points * 5) {
			aux = App->player->max_life_points;
			App->player->UpgradeHP(4);
		}
		else {
			App->player->UpgradePWR(15);
		}
	}

}
