#include "Room.h"

void Room::Start()
{
}

void Room::Update(float dt)
{

	active = PlayerInside();

	if (PlayerInside() == true) {
		App->player->room = coords;
	}

	if (active == true) {

		if (enemies.empty() == false) {
			for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
			{
				if (it._Ptr->_Myval != nullptr) {
					it._Ptr->_Myval->Update(dt);
				}
			}
		}

		if (items.empty() == false) {
			for (std::list<Item*>::iterator it = items.begin(); it != items.end(); it++)
			{
				if (it._Ptr->_Myval != nullptr) {
					it._Ptr->_Myval->Update(dt);
				}
			}
		}

		if (blocks.empty() == false) {
			for (std::list<Block*>::iterator it = blocks.begin(); it != blocks.end(); it++)
			{
				if (it._Ptr->_Myval != nullptr) {
					it._Ptr->_Myval->Update(dt);
				}
			}
		}

		if (doorways.empty() == false) {
			for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++)
			{
				if (it._Ptr->_Myval != nullptr) {
					it._Ptr->_Myval->Update(dt);
				}
			}
		}
	}
}

void Room::CleanUp()
{
	if (items.empty() == false) {
		for (std::list<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				App->entitymanager->DestroyEnity((*it));
		}
		items.clear();
	}
	if (enemies.empty() == false) {
		for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				App->entitymanager->DestroyEnity((*it));
		}
		enemies.clear();
	}

	if (blocks.empty() == false) {
		for (std::list<Block*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
			if (it._Ptr->_Myval != nullptr) {
				it._Ptr->_Myval->CleanUp();
				RELEASE(it._Ptr->_Myval);
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
	ret->pos = { x, y };

	items.push_back(ret);

	return ret;
}

Enemy * Room::AddEnemy(uint subtype, float x, float y)
{
	Enemy* ret = nullptr;

	ret = App->entitymanager->CreateEnemy(subtype);
	ret->pos = { x, y };

	enemies.push_back(ret);

	return ret;
}

Block * Room::AddBlock(uint subtype, float x, float y)
{
	Block* ret = nullptr;

	ret = App->entitymanager->CreateBlock(subtype);
	ret->pos = { x, y };

	blocks.push_back(ret);

	return ret;
}

Doorway * Room::AddDoorway(uint subtype, uint dir, float x, float y)
{
	Doorway* ret = nullptr;

	switch (subtype) {
	case dw_dungeon:
		ret = new DwDungeon();
		break;
	case dw_scene:
		ret = new DwScene();
		break;
	}

	ret->Start();
	ret->SetUp(dir);

	ret->SetPos(x + room_rect.w * coords.x, y + room_rect.h * coords.y);

	doorways.push_back(ret);

	return ret;

}

Scene * Room::GetParentScene()
{
	return parent;
}

void Room::SetParentScene(Scene * scene)
{
	parent = scene;
}
