#include "Item.h"
#include "j1App.h"
#include "j1Map.h"

Item::Item(uint subtype)
{
	
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
					CleanUp();
				else
					PassToInventory();
			}
		}

		Draw(dt);
	}
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

	collider = App->collisions->AddCollider({ 0, 0, App->map->data.tile_width, App->map->data.tile_height }, COLLIDER_ITEM);

	SetUpTexture();

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
	rect = { 180, 40, 28, 26 };
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
	rect = { 144, 146, 28, 32 };
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
	rect = { 144, 146, 28, 32 };
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
	rect = { 144, 146, 28, 32 };
}

void DropTenRupee::Upgrade()
{
	App->player->rupees += 10;
	if (App->player->rupees > App->player->max_rupees)
		App->player->rupees = App->player->max_rupees;
}
