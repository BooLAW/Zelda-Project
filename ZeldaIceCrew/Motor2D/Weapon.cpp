#include "Weapon.h"
#include "ModuleParticles.h"

void Bow::Start()
{
	SetTexture("Sprites/Link_Movement.png");

	sprites[Up][0] = { 0, 0, 32, 32 };
	sprites[Up][1] = { 0, 0, 32, 32 };
	sprites[Up][2] = { 0, 0, 32, 32 };

	sprites[Down][0] = { 0, 0, 32, 32 };
	sprites[Down][1] = { 0, 0, 32, 32 };
	sprites[Down][2] = { 0, 0, 32, 32 };

	sprites[Left][0] = { 0, 0, 32, 32 };
	sprites[Left][1] = { 0, 0, 32, 32 };
	sprites[Left][2] = { 0, 0, 32, 32 };

	sprites[Right][0] = { 0, 0, 32, 32 };
	sprites[Right][1] = { 0, 0, 32, 32 };
	sprites[Right][2] = { 0, 0, 32, 32 };

	for (int i = 0; i < LastDir; i++) {
		for(int k = 0; k < MAX_FRAMES; k++)
			anim[i].PushBack(sprites[i][k]);
		anim[i].speed = 0.4f;
	}


	curr_dir = App->player->curr_dir;

};

void Bow::Attack()
{

	curr_dir = App->player->curr_dir;

	App->particle->CreateParticle(p_arrow, App->player->GetPos().x, App->player->GetPos().y, curr_dir);

};
