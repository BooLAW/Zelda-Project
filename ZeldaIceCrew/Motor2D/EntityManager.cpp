#include "EntityManager.h"
#include "j1Player.h"
#include "p2Log.h"
#include "j1Render.h"

//Constructor and destructor
EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {



}
Entity::Entity() {
}
Entity::Entity(ENTITYTYPE t) {
	type = t;
}
Entity:: ~Entity() {
}
bool EntityManager::Update(float dt) {

	for (int i = 0; i < entities.Count(); i++) {
		entities[i]->Update(dt);
	}
	return true;
}
Entity* EntityManager::CreateEntity(ENTITYTYPE type) {

	Entity* ret = nullptr;

	switch (type) {
	case item:
		ret = new Item();
		break;
	}

	if (ret != nullptr) {
		entities.PushBack(ret);
	}
	else {
		LOG("ERROR CREATING ENTITY type: %d", type);
	}

	return ret;
}

void EntityManager::DestroyEntities()
{
	for (uint i = 0; i < entities.Count(); i++) {
		if (entities[i] != nullptr) {
			delete entities[i];
		}
	}
}

void Entity::Update(float dt) {


}

bool Entity::Draw()
{
	bool ret = NULL;



	return ret;

} // will return NULL if there's an error

void Item::Update(float dt) {
	
}
