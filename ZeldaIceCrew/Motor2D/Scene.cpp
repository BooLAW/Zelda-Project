#include "Scene.h"
#include "j1Map.h"

bool Scene::CleanUp()
{

	App->map->CleanUp();

	if (items.empty() == false) {
		for (std::list<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if(it._Ptr->_Myval != nullptr)
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
			if (it._Ptr->_Myval != nullptr)
				App->entitymanager->DestroyEnity((*it));
		}
		blocks.clear();
	}

	/*if (doorways.empty() == false) {
		for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr)
				it._Ptr->_Myval->CleanUp();
			//RELEASE(*it);
		}
		doorways.clear();
	}*/

	return true;
}

Item * Scene::AddItem(uint subtype, float x, float y)
{
	Item* ret = App->entitymanager->CreateItem(subtype);
	ret->pos = { x, y };

	items.push_back(ret);

	return ret;
}

Block * Scene::AddBlock(uint subtype, float x, float y)
{
	Block* nb = App->entitymanager->CreateBlock(subtype);
	nb->pos = { x, y };

	blocks.push_back(nb);

	return nb;
}

Doorway * Scene::AddDoorway(uint subtype, uint dir, int x, int y)
{
	Doorway* dw = App->entitymanager->CreateDoorway(subtype, dir);

	dw->SetRoomPos(x, y);
	//dw->pos = { (float)x, (float)y };

	doorways.push_back(dw);

	return dw;
}

Enemy* Scene::AddEnemy(int subtype, float x, float y)
{
	LOG("ADD ENEMY");
	Enemy* new_enemy = nullptr;
	new_enemy = App->entitymanager->CreateEnemy(subtype);
	new_enemy->pos = { x, y };

	this->enemies.push_back(new_enemy);

	return new_enemy;
}

bool Scene::IsEnemy(Enemy * en)
{
	bool ret = false;

	if (en != nullptr) {
		for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			if ((*it) == en)
				ret = true;
		}
	}

	return ret;
}
