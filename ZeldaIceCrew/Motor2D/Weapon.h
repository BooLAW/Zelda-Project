#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "p2Defs.h"
#include "j1Player.h"

enum WEAPONTYPE {
	t_noweapon = 0,
	t_sword,
	t_bow,
	__LAST_WEAPONTYPE
};

class Weapon {
public:
	Weapon() { Start(); }
	virtual ~Weapon() {
		App->tex->UnLoad(graphics);
	}

public:
	virtual void Start() {};
	virtual void Attack() {};

	virtual void CleanUp() {
		App->tex->UnLoad(graphics);
	}

	virtual const SDL_Texture* GetTexture() {
		return graphics;
	}
	virtual void SetTexture(char* path) {
		graphics = App->tex->Load(path);
	}
	virtual void SetDir(uint dir) {
		curr_dir = dir;
	}

public:
	SDL_Texture* graphics;
	SDL_Rect sprites[Direction::LastDir][MAX_FRAMES];
	Animation anim[Direction::LastDir];

protected:
	uint curr_dir;

};

//struct NoWeapon : public Weapon {
//	void Start();
//	void Attack();
//};

struct Sword : public Weapon {
public:
	void Start();
	void Attack();
};

struct Bow : public Weapon {
public:
	void Start();
	void Attack();

};

#endif //!__WEAPON_H__