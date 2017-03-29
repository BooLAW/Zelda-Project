#ifndef __ITEM_H__
#define __ITEM_H__

#include "EntityManager.h"
#include "Entity.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Gui.h"


#include "j1Collision.h"

#define FLOATING_OFFSET 3.0f
#define FLOATING_SPEED 20.0f

class Entity;


enum ITEMTYPE {
	power_gauntlet = 0,
	pegasus_boots,
	heart_container,
	drop_heart,
	drop_bomb,
	drop_potion,
	drop_rupee,
	drop_fiverupee,
	drop_tenrupee
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

	virtual void PassToInventory();

	virtual void Update(float dt);
	virtual void Draw(float dt);

	virtual void CleanUp() {
		if (collider != nullptr)
			collider->to_delete = true;
		if (tex != nullptr)
			App->tex->UnLoad(tex);
		if (UI_tex != nullptr)
			App->tex->UnLoad(UI_tex);
	}

	virtual void Start();
	virtual void SetUpTexture() {};

	virtual void Upgrade() {};

	void SetPositions(fPoint point) {
		pos = point;
		draw_pos = point;
	}

protected:
	bool grabbed = false;

	uint price = NULL;
	GuiText* priceTag;

public:
	Collider*		collider;
	
	SDL_Texture*	UI_tex;
	SDL_Rect		UI_rect;

	fPoint draw_pos = pos;
	bool floating_up = false;

};

struct PowerGauntlet : public Item {
public:
	void SetUpTexture();
	void Upgrade();
};

struct PegasusBoots : public Item {
public:
	void SetUpTexture();
	void Upgrade();
};

struct HeartContainer : public Item {
public:
	void SetUpTexture();
	void Upgrade();
};

struct DropHeart : public Item {
	void SetUpTexture();
	void Upgrade();
};

struct DropPotion : public Item {
	void SetUpTexture();
	void Upgrade();
};

struct DropRupee : public Item {

	void SetUpTexture();
	void Upgrade();
};

struct DropFiveRupee : public Item {
	void SetUpTexture();
	void Upgrade();
};

struct DropTenRupee : public Item {
	void SetUpTexture();
	void Upgrade();
};


#endif // !__ITEM_H__