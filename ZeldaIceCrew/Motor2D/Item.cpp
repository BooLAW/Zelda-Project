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

void Item::Start()
{

	SetUpTexture();
	
	if(tex != nullptr)
		collider = App->collisions->AddCollider({ 0, 0, rect.w, rect.h }, COLLIDER_ITEM);

	priceTag = (GuiText*)App->gui->CreateElement(GuiType::text);

}

void PowerGauntlet::Upgrade()
{
	App->player->UpgradePWR(1);
}


void PowerGauntlet::SetUpTexture()
{
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 36, 0, 32, 32 };
	UI_tex = App->tex->Load("Sprites/Items32x32.png");
	UI_rect = { 40, 326, 32, 32 };
}

void PegasusBoots::SetUpTexture()
{
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 0, 0, 32, 32 };
	UI_tex = App->tex->Load("Sprites/Items32x32.png");
	UI_rect = { 0, 326, 32, 32 };
}

void PegasusBoots::Upgrade()
{
	App->player->UpgradeSPD(1);
}

void HeartContainer::SetUpTexture()
{
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 0, 146, 32, 32 };
	UI_tex = App->tex->Load("Sprites/Items32x32.png");
	UI_rect = { 180, 362, 32, 32 };
	
}

void HeartContainer::Upgrade()
{
	App->player->UpgradeHP(2);
}

void DropHeart::SetUpTexture()
{
	type = ENTITYTYPE::drop;
	tex = App->tex->Load("Sprites/Items32x32.png");
	rect = { 180, 40, 32, 26 };
}

void DropHeart::Upgrade()
{
	App->player->curr_life_points += 2;
	if (App->player->curr_life_points > App->player->max_life_points)
		App->player->curr_life_points = App->player->max_life_points;
}

void DropPotion::SetUpTexture()
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

void DropRupee::SetUpTexture()
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

void DropFiveRupee::SetUpTexture()
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

void DropTenRupee::SetUpTexture()
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
