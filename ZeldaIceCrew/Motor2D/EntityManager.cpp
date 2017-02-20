#include "EntityManager.h"
#include "p2Log.h"

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

	if (type == player) {
		ret = new Player();
	}
	else if (type == item) {
		ret = new Item();
	}
	if (ret != nullptr) {
		entities.PushBack(ret);
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
void  Player::Update(float dt) {
	

}
void Item::Update(float dt) {
	
}
