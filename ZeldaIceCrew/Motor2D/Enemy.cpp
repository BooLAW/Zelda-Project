#include "Enemy.h"

Enemy::Enemy(uint subtype)
{

}

Enemy * Enemy::CreateEnemy(ENEMYTYPE type)
{
	Enemy* ret = nullptr;

	switch (type) {
	case BSoldier:
		// ret = new BSoldier();
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

	memset(DmgType, NULL, __LAST_DMGTYPE);
	AIType = no_move;	

	return ret;
}
