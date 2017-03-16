#include "Drop.h"

Drop::Drop(uint subtype)
{
}

Drop * Drop::CreateDrop(uint type)
{
	Drop* ret = nullptr;

	switch (type) {
	case rupee:
		// ret = new Rupee();
		break;
	case heart:
		// ret = new Heart();
	default:
		LOG("Unknown Drop Type: %d", type);
		break;
	}

	ret->type = drop;

	App->entitymanager->PushEntity(ret);

	return ret;
}
