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
			Upgrade();
			PassToInventory();
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
