#include "Weapon.h"
#include "ModuleParticles.h"

void Bow::Start()
{
	SetTexture("Sprites/Link_Movement.png");

	sprites[Down][0] = { link_x * 16, link_y * 9, link_width, link_height };
	sprites[Down][1] = { link_x * 17, link_y * 9, link_width, link_height };
	sprites[Down][2] = { link_x * 18, link_y * 9, link_width, link_height };

	sprites[Up][0] = { link_x * 16, link_y * 10, link_width, link_height };
	sprites[Up][1] = { link_x * 17, link_y * 10, link_width, link_height };
	sprites[Up][2] = { link_x * 18, link_y * 10, link_width, link_height };

	sprites[Right][0] = { link_x * 16, link_y * 11, link_width, link_height };
	sprites[Right][1] = { link_x * 17, link_y * 11, link_width, link_height };
	sprites[Right][2] = { link_x * 18, link_y * 11, link_width, link_height };

	sprites[Left][0] = { link_x * 16, link_y * 12, link_width, link_height };
	sprites[Left][1] = { link_x * 17, link_y * 12, link_width, link_height };
	sprites[Left][2] = { link_x * 18, link_y * 12, link_width, link_height };

	for (int i = 0; i < LastDir; i++) {
		for(int k = 0; k < 3; k++)
			anim[i].PushBack(sprites[i][k]);
		anim[i].speed = 0.1;
	}

	curr_dir = App->player->curr_dir;

};

void Bow::Attack()
{

	curr_dir = App->player->curr_dir;

	fPoint pos = App->player->GetPos();

	switch (curr_dir) {
	case Up:
		pos.x += 8;
		break;
	case Down:
		pos.x += 8;
		pos.y += 32;
		break;
	case Left:
		pos.y += 4;
		break;
	case Right:
		pos.x += App->player->link_coll->rect.w;
		pos.y += 4;
		break;
	}

	App->particle->CreateParticle(p_arrow, pos.x, pos.y, curr_dir);

};

void Sword::Start()
{
	SetTexture("Sprites/Link_Movement.png");

	sprites[Down][0] = { link_x * 7, link_y * 9, link_width, link_height };
	sprites[Down][1] = { link_x * 8, link_y * 9, link_width, link_height };
	sprites[Down][2] = { link_x * 9, link_y * 9, link_width, link_height };
	sprites[Down][3] = { link_x * 10, link_y * 9, link_width, link_height };
	sprites[Down][4] = { link_x * 11, link_y * 9, link_width, link_height };
	sprites[Down][5] = { link_x * 12, link_y * 9, link_width, link_height };

	sprites[Up][0] = { link_x * 7, link_y * 10, link_width, link_height };
	sprites[Up][1] = { link_x * 8, link_y * 10, link_width, link_height };
	sprites[Up][2] = { link_x * 9, link_y * 10, link_width, link_height };
	sprites[Up][3] = { link_x * 10, link_y * 10, link_width, link_height };
	sprites[Up][4] = { link_x * 11, link_y * 10, link_width, link_height };
	sprites[Up][5] = { link_x * 12, link_y * 10, link_width, link_height };
	sprites[Up][6] = { link_x * 13, link_y * 10, link_width, link_height };
	sprites[Up][7] = { link_x * 14, link_y * 10, link_width, link_height };
	sprites[Up][8] = { link_x * 15, link_y * 10, link_width, link_height };

	sprites[Left][8] = { link_x * 7, link_y * 12, link_width, link_height };
	sprites[Left][7] = { link_x * 8, link_y * 12, link_width, link_height };
	sprites[Left][6] = { link_x * 9, link_y * 12, link_width, link_height };
	sprites[Left][5] = { link_x * 10, link_y * 12, link_width, link_height };
	sprites[Left][4] = { link_x * 11, link_y * 12, link_width, link_height };
	sprites[Left][3] = { link_x * 12, link_y * 12, link_width, link_height };
	sprites[Left][2] = { link_x * 13, link_y * 12, link_width, link_height };
	sprites[Left][1] = { link_x * 14, link_y * 12, link_width, link_height };
	sprites[Left][0] = { link_x * 15, link_y * 12, link_width, link_height };

	sprites[Right][0] = { link_x * 7, link_y * 11, link_width, link_height };
	sprites[Right][1] = { link_x * 8, link_y * 11, link_width, link_height };
	sprites[Right][2] = { link_x * 9, link_y * 11, link_width, link_height };
	sprites[Right][3] = { link_x * 10, link_y * 11, link_width, link_height };
	sprites[Right][4] = { link_x * 11, link_y * 11, link_width, link_height };
	sprites[Right][5] = { link_x * 12, link_y * 11, link_width, link_height };
	sprites[Right][6] = { link_x * 13, link_y * 11, link_width, link_height };
	sprites[Right][7] = { link_x * 14, link_y * 11, link_width, link_height };
	sprites[Right][8] = { link_x * 15, link_y * 11, link_width, link_height };


	for (int i = 0; i < LastDir; i++) {
		if (i == Down)
			for (int k = 0; k < 6; k++)
				anim[Down].PushBack(sprites[Down][k]);
		else
			for (int k = 0; k < 9; k++)
				anim[i].PushBack(sprites[i][k]);
		
		anim[i].speed = 0.4;
	}

	anim[Down].speed = anim[Down].speed * 6 / 9;

	curr_dir = App->player->curr_dir;
}

void Sword::Attack()
{
	curr_dir = App->player->curr_dir;

	App->player->Slashing = true;

	switch (curr_dir) {
		case Up:
			App->player->weapon_coll->rect = { (int)App->player->GetPos().x, (int)App->player->link_coll->rect.y - App->player->link_coll->rect.h, WPN_COL_H, WPN_COL_W };
			break;
		case Down:
			App->player->weapon_coll->rect = { (int)App->player->GetPos().x, (int)App->player->link_coll->rect.y + App->player->link_coll->rect.h - 8, WPN_COL_H, WPN_COL_W };
			break;
		case Left:
			App->player->weapon_coll->rect = { (int)App->player->GetPos().x - WPN_COL_W, (int)App->player->GetPos().y + WPN_COL_OFFSET_Y, WPN_COL_W, WPN_COL_H };
			break;
		case Right:
			App->player->weapon_coll->rect = { (int)App->player->GetPos().x + App->player->link_coll->rect.w, (int)App->player->GetPos().y + WPN_COL_OFFSET_Y, WPN_COL_W, WPN_COL_H };
			break;
	}

}
