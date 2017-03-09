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
Entity::Entity(ENTITYTYPE _t, SDL_Texture * _tex, SDL_Rect * _rect, iPoint _pos)
{
	type = _t;
	tex = _tex;
	rect = _rect;
	pos.x = _pos.x;
	pos.y = _pos.y;
}


Entity:: ~Entity() {
}
bool EntityManager::Update(float dt) {

	for (int i = 0; i < entities.size(); i++) {
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
	case bush:
		ret = new Bush();
		break;
	default:
		break;
	}
	
	if (ret != nullptr) {
		entities.push_back(ret);
	}
	else {
		LOG("ERROR CREATING ENTITY type: %d", type);
	}

	return ret;
}

void EntityManager::DestroyEntities()
{
	for (uint i = 0; i < entities.size(); i++) {
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
//ITEM
void Item::Update(float dt) {
	
}
//!ITEM

//BUSH
void Bush::Update(float dt) {

}
//!BUSH