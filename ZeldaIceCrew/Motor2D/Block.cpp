#include "Block.h"

Block::Block(uint subtype, iPoint pos)
{



}

Block * Block::CreateBlock(uint type)
{
	Block* ret = nullptr;

	switch (type) {
	case bush:
		ret = new Bush();
		break;
	case statue:
		ret = new Statue();
		break;
	case pot:
		ret = new Pot();
		break;
	case torch_bowl:
		ret = new Torch_Bowl();
		break;
	case torch_pillar:
		ret = new Torch_Pillar();
		break;
	case slabs:
		ret = new Slab();
		break;
	default:
		LOG("Unknown Block Type: %d", type);
		break;
	}

	ret->type = block;

	App->entitymanager->PushEntity(ret);

	return ret;
}

void Block::Push() {
	//Changes position
	//position


}

void Block::Light() {
	//changes the spire blitted, from idle to lit


}

void Block::Break() {
	//triggers break animation (for whatever reason) and calls destructor


}

void Block::Pick() {
	//triggers pick animation, then put pick state


}

void Block::Open() {
	//triggers open animation, then put open state which can't be opened or closed and gives an item or wahtever it is supposed to give


}