#include "Item.h"
#include "j1App.h"
#include "j1Map.h"
#include "SceneManager.h"
#include "HouseScene.h"
#include "VillageScene.h"

Item::Item(uint subtype)
{
	
}

void Item::PassToInventory()
{
	if (HitBox != nullptr)
		HitBox->to_delete = true;
	if (tex != nullptr)
		App->tex->UnLoad(tex);

	if (priceTag != nullptr)
		priceTag->active = false;

	App->player->inventory.push_back(this);
	App->hud->AddItem(this);
	grabbed = true;

}

void Item::Update(float dt)
{
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
						App->entitymanager->DestroyEnity(this);
					}
					else {
						if (App->player->Find_inv(this)) {
							Upgrade();
							App->entitymanager->DestroyEnity(this);
						}
						else if (App->player->Find_weapon(this)) {
							App->entitymanager->DestroyEnity(this);
						}
						else {
							Upgrade();
							PassToInventory();
						}
					}
				}
			}
		}
		if (set == false) {
			draw_pos = pos;
			set = true;
		}

		Draw(dt);
	}

	if (priceTag != nullptr)
		priceTag->pos = { (int)this->pos.x, (int)this->pos.y};

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

	App->scene_manager->GetCurrentScene()->DestroyItem(this);
}

void Item::Start()
{

	SetUp();
	
	if(tex != nullptr)
		HitBox = App->collisions->AddCollider({ 0, 0, rect.w, rect.h }, COLLIDER_ITEM);

	priceTag = (GuiText*)App->gui->CreateElement(GuiType::text);
	priceTag->movable = false;
}

void PowerGauntlet::Upgrade()
{
	App->player->UpgradePWR(1);
}

void PowerGauntlet::SetUp()
{
	subtype = power_gauntlet;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 36, 0, 32, 32 };
	UI_tex = App->hud->items;
	UI_rect = { 40, 326, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "Gauntlet test description";
}

void PegasusBoots::SetUp()
{
	subtype = pegasus_boots;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 0, 0, 32, 32 };
	UI_tex = App->hud->items;
	UI_rect = { 0, 326, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "Boots test description";
}

void PegasusBoots::Upgrade()
{
	App->player->UpgradeSPD(1);
}

void HeartContainer::SetUp()
{
	subtype = heart_container;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 0, 146, 32, 32 };
	UI_tex = App->hud->items;
	UI_rect = { 180, 362, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/heart_container_1.wav");

}

void HeartContainer::Upgrade()
{
	App->player->UpgradeHP(2);
}

void DropHeart::SetUp()
{
	subtype = drop_heart;
	type = ENTITYTYPE::drop;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 180, 40, 32, 26 };
	fx = App->audio->LoadFx("Audio/Fx/heart.wav");
	
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
	tex = App->tex->Load("Sprites/Items32x32.png");
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
	tex = App->tex->Load("Sprites/Items32x32.png");
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
	tex = App->tex->Load("Sprites/Items32x32.png");
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
	tex = App->tex->Load("Sprites/Items32x32.png");
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
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 362, 74, 32, 32 };
	UI_tex = App->hud->items;
	UI_rect = { 362, 326, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void ItemBow::Upgrade()
{
	if (!App->player->Find_weapon(this)) {
		App->player->AddWeapon(t_bow);
	}
}

void ItemSword::SetUp()
{
	subtype = weapon_sword;
	type = ENTITYTYPE::item;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 252, 41, 32, 32 };
	UI_tex = App->hud->items;
	UI_rect = rect;
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
	description = "";
}

void ItemSword::Upgrade()
{
	if (!App->player->Find_weapon(this)) {
		App->player->AddWeapon(t_sword);
	}
}


void BossKey::SetUp()
{
	subtype = boss_key;
	type = ENTITYTYPE::item;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 362, 144, 32, 34 };
	UI_tex = tex;
	UI_rect = { 360, 470, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void BossKey::Upgrade()
{
	App->player->curr_life_points = App->player->max_life_points;
	App->scene_manager->toChangeScene(App->scene_manager->house_scene);
}
