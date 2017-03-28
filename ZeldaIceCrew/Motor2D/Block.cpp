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

void Slab::Push() {
	//Changes position, does not require input but movement
	//position


}

void Statue::Push() {
	//Changes position, does not require input but movement
	//position


}

void Slab::Pull() {
	//Changes position, by pulling, requires input
}

void Torch_Bowl::Light() {
	//changes the spire blitted, from idle to lit


}

void Torch_Pillar::Light() {
	//changes the spire blitted, from idle to lit


}

void Bush::Break() {
	//triggers break animation (for whatever reason) and calls destructor


}

void Pot::Break() {
	//triggers break animation (for whatever reason) and calls destructor


}

void Bush::Pick() {
	//triggers pick animation, then put pick state


}

void Pot::Pick() {
	//triggers pick animation, then put pick state


}

void Bush::Throw() {
	//throws if something is held

}

void Pot::Throw() {
	//throws if something is held

}
