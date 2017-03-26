#include "Item.h"

Item::Item(uint subtype)
{


}

Item * Item::CreateItem(uint type)
{
	Item* ret = nullptr;

	switch (type) {
	case PowerGauntlet:
		// ret = new PowerGauntlet();
		break;
	case PegasusBoots:
		// ret = new PegasusBoots();
		break;
	case HeartContainer:
		// ret = new HeartContainer();
		break;
	default:
		LOG("Unknown Item Type: %d", type);
		break;
	}

	ret->type = item;

	App->entitymanager->PushEntity(ret);

	return ret;
}
