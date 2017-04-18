#include "Scene.h"
#include "j1Map.h"

bool Scene::CleanUp()
{

	App->map->CleanUp();

	if (rooms.empty() == false) {
		for (std::list<Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr)
				it._Ptr->_Myval->CleanUp();
			RELEASE(*it);
		}
		rooms.clear();
	}

	return true;
}

Room * Scene::GetRoom(int x, int y)
{
	Room* ret = nullptr;

	for (std::list<Room*>::iterator it = rooms.begin(); it != rooms.end(); it++) {
		if (it._Ptr->_Myval->coords.x == x && it._Ptr->_Myval->coords.y == y) {
			ret = it._Ptr->_Myval;
			break;
		}
	}

	return ret;
}

Item * Scene::AddItem(uint subtype, int coord_x, int coord_y, float x, float y)
{
	Room* r = GetRoom(coord_x, coord_y);
	
	Item* ret = nullptr;

	if (r != nullptr) {

		ret = App->entitymanager->CreateItem(subtype);
		ret->pos = { x + r->coords.x * ROOM_W , y + r->coords.y * ROOM_H };

		r->items.push_back(ret);
	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Block * Scene::AddBlock(uint subtype, int coord_x, int coord_y, float x, float y)
{
	Room* r = GetRoom(coord_x, coord_y);

	Block* ret = nullptr;

	if (r != nullptr) {

		ret = App->entitymanager->CreateBlock(subtype);
		ret->pos = { x + r->coords.x * ROOM_W , y + r->coords.y * ROOM_H };

		r->blocks.push_back(ret);
	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Doorway * Scene::AddDoorway(uint subtype, int coord_x, int coord_y, uint dir, int x, int y)
{
	Room* r = GetRoom(coord_x, coord_y);

	Doorway* ret = nullptr;

	if (r != nullptr) {

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

		ret->SetRoomPos(x, y);

		r->doorways.push_back(ret);
	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Enemy* Scene::AddEnemy(int subtype, int coord_x, int coord_y, float x, float y)
{
	LOG("ADD ENEMY");
	Room* r = GetRoom(coord_x, coord_y);

	Enemy* ret = nullptr;

	if (r != nullptr) {

		ret = App->entitymanager->CreateEnemy(subtype);
		ret->pos = { x + r->coords.x * ROOM_W , y + r->coords.y * ROOM_H };

		r->enemies.push_back(ret);
	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

bool Scene::IsEnemy(Enemy * en)
{
	bool ret = false;

	if (en != nullptr) {
		for(std::list<Room*>::iterator r_it = rooms.begin(); r_it != rooms.end(); r_it++)
			for (std::list<Enemy*>::iterator it = r_it._Ptr->_Myval->enemies.begin(); it != r_it._Ptr->_Myval->enemies.end(); it++) {
				if ((*it) == en)
					ret = true;
			}
	}

	return ret;
}
