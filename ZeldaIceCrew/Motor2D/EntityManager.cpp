#include "EntityManager.h"
#include "j1Player.h"
#include "p2Log.h"
#include "j1Render.h"

//Constructor and destructor
EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {



}

Entity* EntityManager::CreateEntity(uint type, uint subtype) {

	Entity* ret = nullptr;

	switch (type) {
	case item:
		ret = new Item(subtype);
		break;
	case drop:
		ret = new Drop(subtype);
		break;
	case block:
		ret = new Block(subtype);
		break;
	case enemy:
		ret = new Enemy(subtype);
		break;
	case bomb:
		ret = new Bomb();
		break;
	case unknown:
		ret = nullptr;
		LOG("Trying to create an Unknown Entity Type ID: %d", type);
		break;
	}

	ret->type = type;

	if (ret != nullptr) {
		entities.push_back(ret);
	}
	else {
		LOG("ERROR CREATING ENTITY type: %d", type);
	}

	return ret;
}


bool EntityManager::Update(float dt) {

	for (int i = 0; i < entities.size(); i++) {
		entities[i]->Update(dt);
	}
	return true;
}


void EntityManager::DestroyEntities()
{
	for (uint i = 0; i < entities.size(); i++) {
		if (entities[i] != nullptr) {
			delete entities[i];
		}
	}
} 

