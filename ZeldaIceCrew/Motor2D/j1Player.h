#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1App.h"
#include "EntityManager.h"
#include "HUD.h"
#include "p2Defs.h"
#include "Item.h"
#include "Weapon.h"
#include "j1Audio.h"
#include "DialogueManager.h"
#include "j1FileSystem.h"
#include"NPC.h"

#define MAX_SPRITE_FRAMES 30

#define N_MAPS 5

#define DASH_SPD 1.77

#define PL_OFFSET 12
#define PL_OFFSET_X 33
#define PL_OFFSET_Y 51

#define MAX_SPD 4
#define MAX_HP 24
#define MAX_PWR 100

#define ORIGIN_SPD 2.5
#define ORIGIN_HP 6
#define ORIGIN_PWR 30

#define MIN_SPD 1.5
#define MIN_HP 2
#define MIN_PWR 15

#define PL_WALK_FPS 0.2f

#define link_width 99
#define link_height 107
#define link_y 110
#define link_x 102

#define WPN_COL_W 24
#define WPN_COL_H 32
#define WPN_COL_OFFSET_X 8
#define WPN_COL_OFFSET_Y 8

#define PL_FARLANDS iPoint({-5000, -5000});

#define PL_SPD_ATK 6

struct Collider;
class Item;
class Weapon;

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
		Hold_sth,
		Pull,
		Push,
		Weapon_atk,
		Slash,
		Sleep_Wake_up,
		Wake_up,
		Die,
		Light,
		Dash,
		Unknown,
		__LAST
	};
	
	enum Controls {
		UP = 0,
		DOWN,
		RIGHT,
		LEFT,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		ACTION,
		MENU,
		WPN_NEXT,
		WPN_PREV,
		__LAST_CONTROLS
	};

public:
	Point<float> pos;
	Point<float> last_pos;
	int controls[__LAST_CONTROLS];

private:
	SDL_Texture* Link_Movement = nullptr;
	SDL_Texture* Link_retro = nullptr;
	SDL_Texture* Link_cave = nullptr;
	SDL_Texture* Link_pink = nullptr;
	SDL_Texture* curr_texture = nullptr;

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
	//Update Functions
	void Movement();
	void Slash_();
	void PickUp_();
	void ChangeWeapon();
	void AddWeapon(uint weapon_t);
	
	void SetToNewGame();

	bool Save(pugi::xml_node& data) const;
	bool Load(pugi::xml_node& data);

	bool LoadPlayer(int id,bool new_game);

	pugi::xml_node LoadXML(pugi::xml_document& config_file,bool new_game) const;

	void HitPlayer(int dmg);

	bool want_to_die = false;

	void SetPos(float x, float y);
	void MovePos(float x, float y);
	bool SetPosTile(int x, int y);
	Point<float> GetPos();
	void DyingRestart();
	bool Find_inv(Item *item);
	bool Find_weapon(Item* item);
	void PlayerInmortal(float time);
	void Talk();

	int CheckSpace(float new_x, float new_y);

	// base stats saving file
	// --status flags 
	bool alive = true;
	bool shield = true;
	bool sword = false;  // as a flag to draw link with the sword sprite
	bool action = false; // Actions: Throw, Pull, Slash,...	
						 // --status VARs
	uint diw_anim_bool = 0;
	bool firstText = true;
	Npc* toTalk = nullptr;
	unsigned int curr_dir;
	uint		 walk_dir;
	bool inMainScreen;
	uint max_life_points = 6;
	int curr_life_points = 6;
	uint power = 1;
	uint rupees = 50;
	uint max_rupees = 99;
	uint bombs = 0;
	//uint arrows = 100;
	std::list<Item*> inventory;
	Point<float> pl_speed;
	j1PerfTimer inmortal_timer;
	float inmortal_time = 0;
	bool inmortal = false;
	bool camera_follow = false; 
	bool talking = false;
	iPoint room;
	uint keys = 0;
	//Completed Maps
	bool map1_comp = false;
	bool map2_comp = false;
	bool map3_comp = false;
	bool map4_comp = false;
	bool map5_comp = false;
	uint controller_index = 0;

	bool completed_maps[N_MAPS];

	j1Timer w_a_timer;

	Collider* mov_coll = nullptr;

  // Weapon Related
	bool Slashing = false;
	enum { 
		No_Change = 0,
		Q_Change,
		E_Change
	} change_weapon = No_Change;

	Weapon* curr_weapon;
	std::list<Weapon*> weapons;

	//audio
	uint sword_fx;
	uint low_hp;
	uint die_fx;
	uint hurt;
	uint open_inv_fx;
	uint close_inv_fx;
	uint dash_fx;
  // !_audio
  
	int action_blit;
	bool dir_override = false; // Overrides directions expressed if there is an action that keeps movement but changes view direction being done at the time
	bool anim_override = false;
	bool push[5];
	bool pull[5];
	bool action_test = false;
	uint best_arena_score;
	uint last_arena_score;
	uint ticking_effect = 0;

	Collider* link_coll;
	Collider* weapon_coll;
	Collider* action_coll;
};

#endif // !__PLAYER_H__
