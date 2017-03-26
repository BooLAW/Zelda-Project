#include "Block.h"

Block::Block(uint subtype)
{


}

Block * Block::CreateBlock(uint type)
{
	Block* ret = nullptr;

	switch (type) {
	case bush:
		// ret = new Bush();
		break;
	case statue:
		// ret = new Statue();
		break;
	default:
		LOG("Unknown Block Type: %d", type);
		break;
	}

	ret->type = block;

	App->entitymanager->PushEntity(ret);

	return ret;
}
