#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "EntityManager.h"
#include "Entity.h"

class Entity;

enum BLOCKTYPE {
	bush = 0,
	statue
};

class Block : public Entity {
public:
	Block() {};
	Block(uint subtype);
	virtual ~Block() {};



public:
	Block* CreateBlock(uint type);

};

#endif // !__BLOCK_H__
