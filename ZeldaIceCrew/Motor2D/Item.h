#ifndef __ITEM_H__
#define __ITEM_H__

#include "EntityManager.h"
#include "Entity.h"

class Entity;

enum ITEMTYPE {
	PowerGauntlet = 0,
	PegasusBoots,
	HeartContainer
};

class Item : public Entity {
public:
	Item() {}
	Item(uint subtype);
	virtual ~Item() {};


public:
	Item* CreateItem(uint type);

};


#endif // !__ITEM_H__