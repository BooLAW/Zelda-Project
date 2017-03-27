#ifndef __ITEM_H__
#define __ITEM_H__

#include "EntityManager.h"
#include "Entity.h"
#include "j1App.h"
#include "j1Textures.h"

#include "j1Collision.h"

#define FLOATING_OFFSET 3.0f
#define FLOATING_SPEED 20.0f

class Entity;

enum ITEMTYPE {
	power_gauntlet = 0,
	pegasus_boots,
	heart_container
};

class Item : public Entity {
public:
	Item() {}
	Item(uint subtype);
	virtual ~Item() {
		this->Clear();
	};

public:
	virtual void Clear() {
		if (collider != nullptr)
			collider->to_delete = true;
		if (UI_tex != nullptr)
			App->tex->UnLoad(UI_tex);
		if (tex != nullptr)
			App->tex->UnLoad(tex);
	}

	virtual void PassToInventory() {
		if (collider != nullptr)
			collider->to_delete = true;
		if (tex != nullptr)
			App->tex->UnLoad(tex);

		// App->player->inventory.push_back(this);

		grabbed = true;

	}

	virtual void Update(float dt);
	virtual void Draw(float dt);

	virtual void Start() {};

	virtual void Upgrade() {};

	void SetPositions(fPoint point) {
		pos = point;
		draw_pos = point;
	}

private:
	bool grabbed = false;

public:
	Collider*		collider;
	
	SDL_Texture*	UI_tex;
	SDL_Rect		UI_rect;

	fPoint draw_pos = pos;
	bool floating_up = false;

};

struct PowerGauntlet : public Item {
public:
	void Start();
	void Upgrade();
};

#endif // !__ITEM_H__