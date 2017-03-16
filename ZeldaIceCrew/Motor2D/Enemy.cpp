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
