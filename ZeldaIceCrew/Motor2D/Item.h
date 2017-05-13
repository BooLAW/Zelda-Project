#ifndef __ITEM_H__
#define __ITEM_H__

#include "EntityManager.h"
#include "j1Textures.h"
#include "HUD.h"
#include "j1Gui.h"
#include "SceneManager.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "Entity.h"

#define FLOATING_OFFSET 3.0f
#define FLOATING_SPEED 20.0f

class Entity;
class GuiText;

enum ITEMTYPE {
	power_gauntlet = 0,
	pegasus_boots,
	heart_container,
	gold_gauntlet,
	wind_cape,
	magic_hammer,
	small_shield,
	vanguard_emblem,
	magic_sphere,
	magic_mirror,
	bag_of_rupees,
	icon_of_power,
	icon_of_wisdom,
	icon_of_valor,
	golden_shield,
	mysterious_dust,
	odd_mushroom,
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
	t_rand_item,
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
		if (HitBox != nullptr)
			HitBox->to_delete = true;
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
	
	SDL_Texture*	UI_tex = nullptr;
	SDL_Rect		UI_rect;
	uint fx;
	fPoint draw_pos = pos;
	bool floating_up = false;
	bool set = false;
	std::string description;
	iPoint coords;

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

struct GoldenGauntlet : public Item {
public:
	void SetUp();
	void Upgrade();
};

struct WindCape : public Item {
	void SetUp();
	void Upgrade();
};

struct MagicHammer : public Item {
	void SetUp();
	void Upgrade();
};

struct SmallShield : public Item {
	void SetUp();
	void Upgrade();
};

struct VanguardEmblem : public Item {
	void SetUp();
	void Upgrade();
};

struct MagicSphere : public Item {
	void SetUp();
	void Upgrade();
};

struct MagicMirror : public Item {
	void SetUp();
	void Upgrade();
};

struct GoldenShield : public Item {
	void SetUp();
	void Upgrade();
};

struct MysteriousDust : public Item {
	void SetUp();
	void Upgrade();
};

struct OddMushroom : public Item {
	void SetUp();
	void Upgrade();
};

struct BagOfRupees : public Item {
	void SetUp();
	void Upgrade();
};

struct IconOfPower : public Item {
	void SetUp();
	void Upgrade();
};

struct IconOfWisdom : public Item {
	void SetUp();
	void Upgrade();
};

struct IconOfValor : public Item {
	void SetUp();
	void Upgrade();
};

struct BossKey : public Item {
public:
	void Update(float dt);
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