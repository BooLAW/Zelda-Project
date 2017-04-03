#ifndef __ITEM_H__
#define __ITEM_H__

#include "EntityManager.h"
#include "Entity.h"
#include "j1App.h"
#include "j1Textures.h"
#include "HUD.h"
#include "j1Gui.h"
#include "SceneManager.h"

#include "j1Collision.h"

#define FLOATING_OFFSET 3.0f
#define FLOATING_SPEED 20.0f

class Entity;
class GuiText;

enum ITEMTYPE {
	power_gauntlet = 0,
	pegasus_boots,
	heart_container,
	boss_key,
	__FIRSTDROP,
	drop_heart,
	drop_bomb,
	drop_potion,
	drop_rupee,
	drop_fiverupee,
	drop_tenrupee,
	__LASTDROP,
	__FIRSTWEAPON,
	weapon_sword,
	weapon_bow,
	__LASTWEAPON,
	__LASTITEMTYPE
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

	virtual void CleanUp();

	virtual void Start();
	virtual void SetUp() {};

	void SetPrice(uint p) {
		price = p;

		price > 0 ? priceTag->str = std::to_string(price) : priceTag->str = "";
	}

	virtual void Upgrade() {};
	virtual ITEMTYPE Subtype() {
		return subtype;
	};
	void SetPositions(fPoint point) {
		pos = point;
		draw_pos = point;
	}

protected:
	bool grabbed = false;

	ITEMTYPE subtype;

	uint price = NULL;
	GuiText* priceTag;

public:
	Collider*		collider;
	
	SDL_Texture*	UI_tex = nullptr;
	SDL_Rect		UI_rect;
	uint fx;
	fPoint draw_pos = pos;
	bool floating_up = false;
	bool set = false;
	std::string description;

};

struct PowerGauntlet : public Item {
public:
	void SetUp();
	void Upgrade();
};

struct PegasusBoots : public Item {
public:
	void SetUp();
	void Upgrade();
};

struct HeartContainer : public Item {
public:
	void SetUp();
	void Upgrade();
};

struct BossKey : public Item {
public:
	void SetUp();
	void Upgrade();
};

struct DropHeart : public Item {
	void SetUp();
	void Upgrade();
};

struct DropPotion : public Item {
	void SetUp();
	void Upgrade();
};

struct DropRupee : public Item {

	void SetUp();
	void Upgrade();
};

struct DropFiveRupee : public Item {
	void SetUp();
	void Upgrade();
};

struct DropTenRupee : public Item {
	void SetUp();
	void Upgrade();
};

struct ItemSword : public Item {
	void SetUp();
	void Upgrade();
};

struct ItemBow : public Item {
	void SetUp();
	void Upgrade();
};


#endif // !__ITEM_H__