#include "Bomb.h"

Bomb * Bomb::CreateBomb()
{
	Bomb* ret = nullptr;

	ret = new Bomb();

	ret->type = bomb;

	App->entitymanager->PushEntity(ret);

	return ret;
}
