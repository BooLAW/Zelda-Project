#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "EntityManager.h"
#include "Entity.h"
#include "j1Textures.h"
class Entity;


//
//enum BLOCKTYPE {
//	bush = 0,
//	pot,
//	statue,
//	torch_bowl,
//	torch_pillar,
//	slabs,
//	last_
//};
//
//class Block : public Entity {
//public:
//	iPoint position;
//
//
//public:
//	Block() {};
//	Block(uint subtype, iPoint pos);
//	virtual ~Block() {};
//
//
//
//public:
//	Block* CreateBlock(uint type);
//
//	virtual bool isPushable() { return false; };
//	virtual bool isPullable() { return false; };
//	virtual bool isTalked() { return false; };
//	virtual bool isLitable() { return false; };
//	virtual bool isBreakable() { return false; };
//	virtual bool isPickable() { return false; };
//	virtual bool isOpenable() { return false; };
//
//	virtual void Push() {};
//	virtual void Pull() {};
//	virtual void Light() {};
//	virtual void Break() {};
//	virtual void Pick() {};
//	virtual void Open() {};
//	virtual void Throw() {};
//};
//
//class Bush : public Block {
//	SDL_Rect size = { 0,0,40,40 };
//	//Collision box is 3/4 down, why?
//	//Block moves down to Link position then the animation goes through
//
//	bool isBreakable() {
//		return true;
//	}
//
//	bool isPickable() {
//		return true;
//	}
//
//	void Pick();
//	void Throw();
//	void Break();
//};
//
//class Pot : public Block {
//	SDL_Rect size = { 0,0,40,40 };
//	//Collision box is 3/4 down, why?
//	//Block moves down to Link position then the animation goes through
//
//	bool isPickable() {
//		return true;
//	}
//
//	bool isBreakable() {
//		return true;
//	}
//
//	void Pick();
//	void Throw();
//	void Break();
//};
//
//class Statue : public Block {
//	SDL_Rect size = { 0,0,40,80 };
//
//	bool isPushable() {
//		return true;
//	}
//
//};
//
//class Torch_Bowl : public Block {
//	SDL_Rect size = { 0,0,40,40 };
//
//	bool isLitable() {
//		return true;
//	}
//
//	void Light();
//};
//
//class Torch_Pillar : public Block {
//	SDL_Rect size = { 0,0,40,80 };
//
//	bool isLitable() {
//		return true;
//	}
//
//	void Light();
//};
//
//class Slab : public Block {
//	SDL_Rect size = { 0,0,40,40 };
//
//	bool isPushable() {
//		return true;
//	}
//
//	bool isPullable() {
//		return true;
//	}
//
//	void Move_Block();
//};
#endif // !__BLOCK_H__