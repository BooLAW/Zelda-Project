#include "Scene.h"

bool Scene::CleanUp()
{
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
		blocks.clear();
	}
	return true;
}

Enemy* Scene::AddEnemy(int subtype, float x, float y)
{
	Enemy* new_enemy = nullptr;
	new_enemy = App->entitymanager->CreateEnemy(subtype);
	new_enemy->pos = { x, y };

	enemies.push_back(new_enemy);

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
