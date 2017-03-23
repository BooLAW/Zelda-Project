#include "Enemy.h"

Enemy::Enemy(uint subtype)
{

}

bool Enemy::Start()
{
	bool ret = true;

	stats.Hp = 0;
	stats.Speed = 0;
	stats.Power = 0;

	stats.Flying = false;

	HitBox = new Collider({ 0, 0, 0, 0 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);
	AIType = no_move;	
	type = ENEMYTYPE::__LAST;

	return ret;
}

void Enemy::Update(float dt)
{
	Move();

	Attack();

	Draw();
}

bool Enemy::Move()
{
	bool ret = true;

	fPoint aux_pos = pos;

	switch (AIType) {
	case path:	
		break;
	case chase:
		break;
	case distance:
		break;
	case no_move:
		break;
	}

	if (aux_pos.x > pos.x)
		curr_dir = Left;
	else if (aux_pos.x < pos.x)
		curr_dir = Right;
	else if (aux_pos.y > pos.y)
		curr_dir = Down;
	else if (aux_pos.y < pos.y)
		curr_dir = Up;

	return ret;
}

bool Enemy::Attack()
{
	bool ret = true;

	if (DmgType[melee] == true) {
		HitBox->rect = animations[curr_dir].GetCurrentFrame();
		HitBox->SetPos(pos.x, pos.y);
	}

	return ret;
}

void Enemy::Draw()
{
	App->render->Blit(Entity::GetTexture(), pos.x, pos.y, &animations[curr_dir].GetCurrentFrame());
}

bool BSoldier::Start()
{
	bool ret = true;

	curr_dir = Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Down][0] = { 30, 251, 44, 68 };
		sprites[Down][1] = { 132, 249, 44, 70 };

		sprites[Up][0] = { 30, 357, 44, 52 };
		sprites[Up][1] = { 132, 357, 44, 52 };

		sprites[Left][0] = { 214, 465, 64, 54 };
		sprites[Left][1] = { 316, 465, 64, 54 };

		sprites[Right][0] = { 30, 465, 64, 54 };
		sprites[Right][1] = { 132, 465, 64, 54 };

		animations[Down].PushBack(sprites[Down][0]);
		animations[Down].PushBack(sprites[Down][1]);

		animations[Up].PushBack(sprites[Up][0]);
		animations[Up].PushBack(sprites[Up][1]);

		animations[Left].PushBack(sprites[Left][0]);
		animations[Left].PushBack(sprites[Left][1]);

		animations[Right].PushBack(sprites[Right][0]);
		animations[Right].PushBack(sprites[Right][1]);


	}

	stats.Hp = 3;
	stats.Speed = 1.5;
	stats.Power = 1;

	stats.Flying = false;

	for (int i = 0; i < LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = path;

	subtype = ENEMYTYPE::BlueSoldier;

	return ret;
}
