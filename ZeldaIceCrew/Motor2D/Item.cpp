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
	if (collider != nullptr)
		collider->to_delete = true;
	if (tex != nullptr)
		App->tex->UnLoad(tex);

	App->player->inventory.push_back(this);
	App->hud->AddItem(this);

	App->scene_manager->GetCurrentScene()->DestroyItem(this);

	grabbed = true;

}

void Item::Update(float dt)
{
	if (grabbed == false) {
		if (collider != nullptr)
			if (collider->rect.x != pos.x || collider->rect.y != pos.y)
				collider->SetPos(pos.x, pos.y);

		if (collider->CheckCollision(App->player->link_coll->rect)) {
			if (App->player->rupees >= this->price) {
				App->player->rupees -= price;
				Upgrade();
				App->audio->PlayFx(this->fx);
				if (type == ENTITYTYPE::drop)
				{
					App->entitymanager->DestroyEnity(this);
				
					/*Scene* curr_scene = App->scene_manager->GetCurrentScene();
					if (curr_scene == App->scene_manager->village_scene)
						App->scene_manager->village_scene->items.erase();
					else if (curr_scene == App->scene_manager->village_scene)
					{
						App->scene_manager->village_scene->items.erase(),
					}*/
				}
				else
					PassToInventory();
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

	App->render->Blit(tex, draw_pos.x, draw_pos.y, &rect);
}

void Item::CleanUp()
{
	if (collider != nullptr)
		collider->to_delete = true;
	if (tex != nullptr)
		App->tex->UnLoad(tex);
	if (UI_tex != nullptr)
		App->tex->UnLoad(UI_tex);

	App->scene_manager->GetCurrentScene()->DestroyItem(this);
}

void Item::Start()
{

	SetUp();
	
	if(tex != nullptr)
		collider = App->collisions->AddCollider({ 0, 0, rect.w, rect.h }, COLLIDER_ITEM);

	priceTag = (GuiText*)App->gui->CreateElement(GuiType::text);

}

void PowerGauntlet::Upgrade()
{
	App->player->UpgradePWR(1);
}


void PowerGauntlet::SetUp()
{
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 36, 0, 32, 32 };
	UI_tex = App->tex->Load("Sprites/Items32x32.png");
	UI_rect = { 40, 326, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");

}

void PegasusBoots::SetUp()
{
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 0, 0, 32, 32 };
	UI_tex = App->tex->Load("Sprites/Items32x32.png");
	UI_rect = { 0, 326, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void PegasusBoots::Upgrade()
{
	App->player->UpgradeSPD(1);
}

void HeartContainer::SetUp()
{

	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 0, 146, 32, 32 };
	UI_tex = App->tex->Load("Sprites/Items32x32.png");
	UI_rect = { 180, 362, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/heart_container_1.wav");

}

void HeartContainer::Upgrade()
{
	App->player->UpgradeHP(2);
}

void DropHeart::SetUp()
{
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
	type = ENTITYTYPE::drop;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 116, 254, 16, 28 };

}

void DropRupee::Upgrade()
{
	App->player->rupees += 1;
	if (App->player->rupees > App->player->max_rupees)
		App->player->rupees = App->player->max_rupees;

}

void DropFiveRupee::SetUp()
{
	type = ENTITYTYPE::drop;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 224, 254, 16, 28 };
}

void DropFiveRupee::Upgrade()
{
	App->player->rupees += 5;
	if (App->player->rupees > App->player->max_rupees)
		App->player->rupees = App->player->max_rupees;
}

void DropTenRupee::SetUp()
{
	type = ENTITYTYPE::drop;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 332, 254, 16, 28 };
}

void DropTenRupee::Upgrade()
{
	App->player->rupees += 10;
	if (App->player->rupees > App->player->max_rupees)
		App->player->rupees = App->player->max_rupees;
}

void ItemBow::SetUp()
{
	type = ENTITYTYPE::item;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 362, 74, 32, 32 };
	UI_tex = App->tex->Load("Sprites/Items32x32.png");
	UI_rect = { 362, 326, 32, 32 };
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void ItemBow::Upgrade()
{
	App->player->AddWeapon(t_bow);
}

void ItemSword::SetUp()
{
	type = ENTITYTYPE::item;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 252, 41, 32, 32 };
	UI_tex = tex;
	UI_rect = rect;
	fx = App->audio->LoadFx("Audio/Fx/item_get_1.wav");
}

void ItemSword::Upgrade()
{
	App->player->AddWeapon(t_sword);
}
