#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "EntityManager.h"
#include "Entity.h"

#define N_ITEMS 15

enum BLOCKTYPE {
	bush = 0,
	pot,
	statue,
	torch_bowl,
	torch_pillar,
	slabs,
	last_
};

enum BLOCKANIM {
	idle,
	broke,
	lit,

	last__

};

class Block : public Entity {
public:
	//fPoint position;
	uint reward_pool[N_ITEMS];
	BLOCKTYPE subtype;
	BLOCKANIM anim;
	SDL_Texture* temp;
	SDL_Rect sprites[last_][last__][8];
	Animation animations[last_][last__];
	bool picked = false;
	bool front = false;
	bool back = false;
	bool moving = false;

public:
	Block() {};
	Block(uint subtype);
	virtual ~Block() {};


	virtual bool Start();

	virtual void Spawn() {};

	virtual void Update(float dt);

	virtual void Draw();

	virtual void Reward();

public:
	//Block* CreateBlock(uint type, fPoint ipos);

	virtual bool isMovable() { return false; };
	//virtual bool isTalked() { return false; };
	virtual bool isLitable() { return false; };
	virtual bool isBreakable() { return false; };
	virtual bool isPickable() { return false; };
	//virtual bool isOpenable() { return false; };

	virtual void Move();
	virtual void Light() {};
	virtual void Break() {};
	virtual void Pick() {};
	virtual void Open() {};
	virtual void Throw() {};

	virtual void SetRewards() {};

	void SortRewardProbs() {
		uint total = 0;

		for (int i = 0; i < N_ITEMS; i++) {
			total += reward_pool[i];
		}

		if (total != 100) {
			for (int i = 0; i < N_ITEMS; i++) {
				reward_pool[i] = (reward_pool[i] * 100) / total;
			}
		}

	}

	virtual void CleanUp() {
		if (tex != nullptr)
			App->tex->UnLoad(tex);

		if (HitBox != nullptr)
			HitBox->to_delete = true;

	}

};

class Bush : public Block {
	//Collision box is 3/4 down, why?
	//Block moves down to Link position then the animation goes through
	bool Start();

	bool isBreakable() {
		return true;
	}

	bool isPickable() {
		return true;
	}

	void Break();
	void Throw();
	void Pick();
	void SetRewards();

};

class Pot : public Block {
	//Collision box is 3/4 down, why?
	//Block moves down to Link position then the animation goes through
	bool Start();

	bool isPickable() {
		return true;
	}

	bool isBreakable() {
		return true;
	}

	void Break();
	void Throw();
	void Pick();
	void SetRewards();


};

class Statue : public Block {
	bool Start();

	bool isPushable() {
		return true;
	}

	//void Move();

};

class Torch_Bowl : public Block {
	bool Start();

	bool isLitable() {
		return true;
	}

	void Light();
};

/*class Torch_Pillar : public Block {
bool Start();

bool isLitable() {
return true;
}

void Light();
};*/

class Slab : public Block {
	bool Start();

	bool isMovable() {
		return true;
	}

	//void Move();

};



#endif // !__BLOCK_H__