#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "EntityManager.h"
#include "Entity.h"

class Entity;



enum BLOCKTYPE {
	bush = 0,
	pot,
	statue,
	torch_bowl,
	torch_pilar,
	slabs,
	last_
};

class Block : public Entity {
public:
	Block() {};
	Block(uint subtype);
	virtual ~Block() {};



public:
	Block* CreateBlock(uint type);

	virtual bool isPushable() { return true; };
	virtual bool isPullable() { return true; };
	virtual bool isTalked() { return true; };
	virtual bool isLit() { return true; };
	virtual bool isBreakable() { return true; };
	virtual bool isPickable() { return true; };
	virtual bool isOpenable() { return true; };
};

class Bush : public Block {
	//Start que passi tota la info que toca, 
	bool isBreakabled() {
		return false;
	}

	bool isPickable() {
		return true;
	}
};

class Pot : public Block {
	bool isPickable() {
		return true;
	}
};

class Statue : public Block {
	bool isPushable() {
		return true;
	}
};

class Torch_Bowl : public Block {
	bool isLit() {
		return true;
	}
};

class Torch_Pillar : public Block {
	bool isLit() {
		return true;
	}
};

class Slab : public Block {
	bool isPushable() {
		return true;
	}

	bool isPullable() {
		return true;
	}
};
#endif // !__BLOCK_H__
