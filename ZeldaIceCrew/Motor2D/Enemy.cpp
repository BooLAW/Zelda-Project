#include "Enemy.h"

Enemy::Enemy(uint subtype)
{

}

Enemy * Enemy::CreateEnemy(ENEMYTYPE subtype)
{
	Enemy* ret = nullptr;

	switch (type) {
	case BlueSoldier:
		ret = new BSoldier();
		break;
	default:
		LOG("Unknown Enemy Type: %d", type);
		break;
	}

	ret->type = enemy;

	App->entitymanager->PushEntity(ret);

	return ret;
}

bool Enemy::Start()
{
	bool ret = true;

	stats.Hp = 0;
	stats.Speed = 0;
	stats.Power = 0;

	stats.Flying = false;

	HitRect = { 0, 0, 16, 16 };

	HitBox = new Collider(HitRect, COLLIDER_ENEMY);

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

	switch (AIType) {
	case path:
		pos.x++;
		break;
	case chase:
		break;
	case distance:
		break;
	case no_move:
		break;

	}

	return ret;
}

bool BSoldier::Start()
{
	bool ret = true;

	curr_dir = Down;

	Entity::SetTexture(App->tex->Load("Sprites/Npcs.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Down][0] = { 3, 3, 16, 21 };
		sprites[Down][1] = { 3, 3, 16, 21 };
		sprites[Down][2] = { 3, 3, 16, 21 };
		sprites[Down][3] = { 3, 3, 16, 21 };

		sprites[Up][0] = { 3, 3, 16, 21 };
		sprites[Up][1] = { 3, 3, 16, 21 };
		sprites[Up][2] = { 3, 3, 16, 21 };
		sprites[Up][3] = { 3, 3, 16, 21 };

		sprites[Left][0] = { 3, 3, 16, 21 };
		sprites[Left][1] = { 3, 3, 16, 21 };
		sprites[Left][2] = { 3, 3, 16, 21 };
		sprites[Left][3] = { 3, 3, 16, 21 };

		sprites[Right][0] = { 3, 3, 16, 21 };
		sprites[Right][1] = { 3, 3, 16, 21 };
		sprites[Right][2] = { 3, 3, 16, 21 };
		sprites[Right][3] = { 3, 3, 16, 21 };

		animations[Down].PushBack(sprites[Down][0]);
		animations[Down].PushBack(sprites[Down][1]);
		animations[Down].PushBack(sprites[Down][2]);
		animations[Down].PushBack(sprites[Down][3]);

		animations[Up].PushBack(sprites[Up][0]);
		animations[Up].PushBack(sprites[Up][1]);
		animations[Up].PushBack(sprites[Up][2]);
		animations[Up].PushBack(sprites[Up][3]);

		animations[Left].PushBack(sprites[Left][0]);
		animations[Left].PushBack(sprites[Left][1]);
		animations[Left].PushBack(sprites[Left][2]);
		animations[Left].PushBack(sprites[Left][3]);

		animations[Right].PushBack(sprites[Right][0]);
		animations[Right].PushBack(sprites[Right][1]);
		animations[Right].PushBack(sprites[Right][2]);
		animations[Right].PushBack(sprites[Right][3]);
	}

	stats.Hp = 3;
	stats.Speed = 1.5;
	stats.Power = 1;

	stats.Flying = false;

	HitRect = { (int)pos.x, (int)pos.y - 5, 16, 16 };

	HitBox = new Collider(HitRect, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = path;

	subtype = ENEMYTYPE::BlueSoldier;

	return ret;
}
