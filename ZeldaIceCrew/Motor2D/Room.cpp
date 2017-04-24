#include "Room.h"

void Room::Start()
{
}

void Room::Update(float dt)
{
	active = PlayerInside();

	if (PlayerInside() == true && App->player->room != coords) {
		App->player->room = coords;
	}

	EnemyActive(active);

	if (doorways.empty() == false) {
		for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr) {
				it._Ptr->_Myval->Update(dt);
			}
		}
	}

}

void Room::CleanUp()
{
	if (items.empty() == false) {
		for (std::list<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				parent->DestroyItem((*it));
		}
		items.clear();
	}
	if (enemies.empty() == false) {
		for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				parent->DestroyEnemy((*it));
		}
		enemies.clear();
	}

	if (blocks.empty() == false) {
		for (std::list<Block*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
			if (it._Ptr->_Myval != nullptr) {
				parent->DestroyBlock((*it));
			}
		}
		blocks.clear();
	}

	if (doorways.empty() == false) {
		for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr) {
				it._Ptr->_Myval->CleanUp();
				RELEASE(it._Ptr->_Myval);
			}
		}
		doorways.clear();
	}
}

bool Room::isInside(SDL_Rect r)
{
	if (r.x > room_rect.x && r.x < room_rect.x + room_rect.w)
		if (r.y > room_rect.y && r.y < room_rect.y + room_rect.h)
			return true;

	return false;
}

bool Room::PlayerInside()
{
	return isInside(App->player->mov_coll->rect);
}

Item * Room::AddItem(uint subtype, float x, float y)
{
	Item* ret = nullptr;

	ret = App->entitymanager->CreateItem(subtype);
	ret->pos = { x + ROOM_W * coords.x, y + ROOM_H * coords.y};

	items.push_back(ret);

	return ret;
}

Enemy * Room::AddEnemy(uint subtype, float x, float y)
{
	Enemy* ret = nullptr;

	ret = App->entitymanager->CreateEnemy(subtype);
	ret->pos = { x + coords.x * ROOM_W, y + coords.y * ROOM_H };

	enemies.push_back(ret);

	return ret;
}

Block * Room::AddBlock(uint subtype, float x, float y)
{
	Block* ret = nullptr;

	ret = App->entitymanager->CreateBlock(subtype);
	ret->pos = { x + ROOM_W * coords.x, y + ROOM_H * coords.y };

	blocks.push_back(ret);

	return ret;
}

Doorway * Room::AddDungeonDoorway(uint subtype, uint dir, float x, float y)
{
	return nullptr;
}

Doorway * Room::AddSceneDoorway(uint subtype, uint dir, float x, float y)
{
	return nullptr;
}

Doorway * Room::AddCamDoorway(uint subtype, uint dir, float x, float y)
{
	return nullptr;
}

void Room::EnemyActive(bool flag)
{
	for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
		it._Ptr->_Myval->active = flag;
	}
}

Scene * Room::GetParentScene()
{
	return parent;
}

void Room::SetParentScene(Scene * scene)
{
	parent = scene;
}
