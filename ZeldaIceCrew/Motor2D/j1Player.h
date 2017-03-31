#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1App.h"
#include "EntityManager.h"
#include "HUD.h"
#include "Item.h"
#include "j1Audio.h"

#define MAX_SPRITE_FRAMES 30

#define PL_OFFSET 12
#define PL_OFFSET_X 33
#define PL_OFFSET_Y 35

#define MAX_SPD 5
#define MAX_HP 24
#define MAX_PWR 99

#define PL_WALK_FPS 0.8f

#define link_width 99
#define link_height 107
#define link_y 110
#define link_x 102

#define WPN_COL_W 24
#define WPN_COL_H 32
#define WPN_COL_OFFSET_X 8
#define WPN_COL_OFFSET_Y 8

struct Collider;
class Item;

enum Direction {
	FirstDir = 0,
	Up,
	Left,
	Right,
	Down,
	Up_R,
	Up_L,
	Down_R,
	Down_L,
	LastDir
};

class j1Player : public j1Module {
public:
	enum Sprites {
		__FIRST = 0,
		Idle,
		Idle_Shield,
		Walk,		
		Walk_Shield,
		S_Charge_Idle,
		S_Charge_Walk,
		Pickup,
		Pull,
		Push,
		Slash,
		Unknown,
		__LAST
	};
	

private:
	Point<float> pos;
	Point<float> last_pos;
	Point<float> pl_speed;

	SDL_Texture* Link_Movement = nullptr;

	// All player sprites / animations
	Animation animations[Sprites::__LAST][Direction::LastDir];
	SDL_Rect sprites[Sprites::__LAST][Direction::LastDir][MAX_SPRITE_FRAMES];


public:
	j1Player();
	virtual ~j1Player();

private:
	bool Awake();
	bool Start();
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:
	// Upgrading
	void UpgradeSPD(float x);
	void UpgradePWR(int x);
	void UpgradeHP(int x);

	void SetPos(float x, float y);
	void MovePos(float x, float y);
	bool SetPosTile(int x, int y);
	Point<float> GetPos();
	void DyingRestart();
	// base stats saving file
	// --status flags 
	bool alive = true;
	bool shield = true;
	bool sword = false;  // as a flag to draw link with the sword sprite
	bool action = false; // Actions: Throw, Pull, Slash,...
	bool inmortal = false;					 // --status VARs
	
	unsigned int curr_dir;
	uint max_life_points = 6;
	uint curr_life_points = 6;
	uint power = 1;
	uint rupees = 50;
	uint max_rupees = 99;
	uint bombs = 50;
	uint arrows = 100;
	j1PerfTimer inmortal_timer;
	std::list<Item*> inventory;
	//audio
	uint sword_fx;
	uint low_hp;
	uint die_fx;
	uint hurt;
	uint open_inv_fx;
	uint close_inv_fx;
	int action_blit;
	bool dir_override = false; // Overrides directions expressed if there is an action that keeps movement but changes view direction being done at the time
	bool anim_override = false;

	Collider* link_coll;
	Collider* weapon_coll;

};

#endif // !__PLAYER_H__
