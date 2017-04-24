#include "Scene.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1Input.h"


bool Scene::Update(float dt)
{
	return stdUpdate(dt);
}

bool Scene::stdUpdate(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;

	if (App->map->active)
		App->map->Draw();

	int i = 0;

	for (std::list<Room*>::iterator it = rooms.begin(); it != rooms.end(); it++) {
		if (it._Ptr->_Myval != nullptr) {
			//LOG("ROOM_UPDATE N� %d", i);
			it._Ptr->_Myval->Update(dt);
			i++;
		}
	}

	return true;
}

bool Scene::CleanUp()
{
	return stdCleanUp();
}

bool Scene::stdCleanUp()
{
	App->map->CleanUp();

	if (rooms.empty() == false) {
		for (std::list<Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr) {
				it._Ptr->_Myval->CleanUp();
				DestroyRoom(it._Ptr->_Myval);
			}
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

Room * Scene::GetCurrentRoom()
{
	return GetRoom(App->player->room.x, App->player->room.y);
}

void Scene::DestroyItem(Item * ent)
{
	if (ent != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++)
			for (std::list<Item*>::iterator it = room_it._Ptr->_Myval->items.begin(); it != room_it._Ptr->_Myval->items.end(); it++) {
				if (it._Ptr->_Myval == ent) {
					it._Ptr->_Myval->to_delete = true;
					room_it._Ptr->_Myval->items.erase(it);
					//App->entitymanager->DestroyEnity(ent);
				}
			}
	}


}

void Scene::DestroyEnemy(Enemy * ent)
{
	if (ent != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++)
			for (std::list<Enemy*>::iterator it = room_it._Ptr->_Myval->enemies.begin(); it != room_it._Ptr->_Myval->enemies.end(); it++) {
				if (it._Ptr->_Myval == ent) {
					//App->entitymanager->DestroyEnity(ent);
					it._Ptr->_Myval->to_delete = true;
					room_it._Ptr->_Myval->enemies.erase(it);
				}
			}
	}
}
void Scene::DestroyBlock(Block * ent)
{
	if (ent != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++)
			for (std::list<Block*>::iterator it = room_it._Ptr->_Myval->blocks.begin(); it != room_it._Ptr->_Myval->blocks.end(); it++) {
				if (it._Ptr->_Myval == ent) {
					it._Ptr->_Myval->to_delete = true;
					room_it._Ptr->_Myval->blocks.erase(it);
					//App->entitymanager->DestroyEnity(ent);
				}
			}
	}
}
void Scene::DestroyDoorway(Doorway * ent)
{
	if (ent != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++) {
			if (room_it._Ptr->_Myval != nullptr);
			for (std::list<Doorway*>::iterator it = room_it._Ptr->_Myval->doorways.begin(); it != room_it._Ptr->_Myval->doorways.end(); it++) {
				if (it._Ptr->_Myval == ent) {
					//ent->CleanUp();
					room_it._Ptr->_Myval->doorways.erase(it);
				}
			}
		}
	}
}
void Scene::DestroyRoom(Room * ent)
{
	if (ent != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++)
			if (room_it._Ptr->_Myval == ent) {
				rooms.erase(room_it);
			}
	}

}
;

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
		case dw_scene:
			ret = new DwScene();
			break;
		case dw_cam:
			break;
		}

		ret->Start();
		ret->SetUp(dir);

		ret->SetPos(x + ROOM_W * coord_x, y + ROOM_H * coord_y);

		r->doorways.push_back(ret);
	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Doorway * Scene::AddDungeonDoorway(uint dir, int coord_x, int coord_y)
{
	Room* r = GetRoom(coord_x, coord_y);

	Doorway* ret = nullptr;

	if (r != nullptr) {

		ret = new DwDungeon();

		ret->Start();
		ret->SetUp(dir);

		ret->SetPos(coord_x, coord_y);

		r->doorways.push_back(ret);

	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Enemy* Scene::AddEnemy(int subtype, int coord_x, int coord_y, float x, float y)
{
	//LOG("ADD ENEMY");
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

Room * Scene::AddRoom(int coord_x, int coord_y, int w, int h)
{
	Room* ret = nullptr;

	ret = new Room();

	ret->coords.x = coord_x;
	ret->coords.y = coord_y;
	ret->room_rect = { coord_x * w, coord_y * h , w, h };

	ret->SetParentScene(this);

	rooms.push_back(ret);

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

void Scene::AllEnemyActive(bool flag)
{
	for (std::list<Room*>::iterator r_it = rooms.begin(); r_it != rooms.end(); r_it++) {
		for (std::list<Enemy*>::iterator it = (*r_it)->enemies.begin(); it != (*r_it)->enemies.end(); it++) {
			it._Ptr->_Myval->active = flag;
		}
	}
};
