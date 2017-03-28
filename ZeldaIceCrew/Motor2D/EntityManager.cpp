#include "EntityManager.h"
#include "j1Player.h"
#include "p2Log.h"
#include "j1Render.h"

//Constructor and destructor
EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {



}

Enemy * EntityManager::CreateEnemy(uint subtype)
{
	Enemy* ret = nullptr;

	switch (subtype) {
	case BlueSoldier:
		ret = new BSoldier();
		break;
	default:
		LOG("Unknown Enemy Type: %d", subtype);
		break;
	}

	ret->type = enemy;

	ret->Start();

	App->entitymanager->PushEntity(ret);

	return ret;
}


bool EntityManager::Update(float dt) {

	for (int i = 0; i < entities.size(); i++) {
		entities[i]->Update(dt);
	}
	return true;
}

void EntityManager::PushEntity(Entity * ent)
{
	if (ent != nullptr)
		entities.push_back(ent);
	else
		LOG("Error Pushing Entity to Entities List");
}


void EntityManager::DestroyEntities()
{
	for (uint i = 0; i < entities.size(); i++) {
		if (entities[i] != nullptr) {
			entities[i]->CleanUp();
			delete entities[i];
		}
	}
}

void EntityManager::DestroyEnity(Entity * ent)
{
	ent->CleanUp();

	std::deque<Entity*>::iterator aux = std::find(entities.begin(), entities.end(), ent);

	entities.erase(aux);
}

void EntityManager::OnCollision(Collider * c1, Collider * c2)
{
	
}

