#include "j1Player.h"
#include "j1Input.h"
#include "j1Collision.h"
#include "j1Map.h"
#include "ModuleParticles.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DungeonScene.h"
#include "VillageScene.h"
#include "ShopScene.h"
#include "HouseScene.h"
j1Player::j1Player()
{
}

j1Player::~j1Player()
{
}

bool j1Player::Awake()
{
	bool ret = true;
	LOG("Player Awake Start");

	return ret;
}

bool j1Player::Start()
{
	bool ret = true;
	LOG("Player Start");

	// Setting Up all SDL_Rects x is every 102p, y is every 110p
	//Idle
	{
		sprites[Idle][Up][0] = {link_x*3, link_y*2, link_width, link_height };
		sprites[Idle][Down][0] = {link_x*3, link_y, link_width, link_height };
		sprites[Idle][Left][0] = {link_x*3, link_y*4, link_width, link_height };
		sprites[Idle][Right][0] = { link_x*3, link_y*3, link_width, link_height };

	}

	//Idle Shield
	{
		sprites[Idle_Shield][Up][0] = { link_x * 3, link_y * 6, link_width, link_height };
		sprites[Idle_Shield][Down][0] = { link_x * 3, link_y * 5, link_width, link_height };
		sprites[Idle_Shield][Left][0] = { link_x * 3, link_y * 8, link_width, link_height };
		sprites[Idle_Shield][Right][0] = { link_x * 3, link_y * 7, link_width, link_height };
	}

	//Walk
	{
		sprites[Walk][Up][0] = { 0, link_y*2, link_width, link_height};
		sprites[Walk][Up][1] = { link_x, link_y*2, link_width, link_height };
		sprites[Walk][Up][2] = { link_x*2 , link_y*2, link_width, link_height };
		sprites[Walk][Up][3] = { link_x*3, link_y*2, link_width, link_height };
		sprites[Walk][Up][4] = { link_x*4, link_y*2, link_width, link_height };
		sprites[Walk][Up][5] = { link_x*5, link_y*2, link_width, link_height };
		sprites[Walk][Up][6] = { link_x*6, link_y*2, link_width, link_height };

		sprites[Walk][Down][0] = { 0 ,  link_y, link_width, link_height };
		sprites[Walk][Down][1] = { link_x, link_y, link_width, link_height };
		sprites[Walk][Down][2] = { link_x*2, link_y, link_width, link_height };
		sprites[Walk][Down][3] = { link_x*3, link_y, link_width, link_height };
		sprites[Walk][Down][4] = { link_x*4, link_y, link_width, link_height };
		sprites[Walk][Down][5] = { link_x*5, link_y, link_width, link_height };
		sprites[Walk][Down][6] = { link_x*6, link_y, link_width, link_height };

		sprites[Walk][Right][0] = { 0  ,link_y*3,link_width,link_height };
		sprites[Walk][Right][1] = { link_x,link_y*3,link_width,link_height };
		sprites[Walk][Right][2] = { link_x*2,link_y*3,link_width,link_height };
		sprites[Walk][Right][3] = { link_x*3,link_y*3,link_width,link_height };
		sprites[Walk][Right][4] = { link_x*4,link_y*3,link_width,link_height };
		sprites[Walk][Right][5] = { link_x*5,link_y*3,link_width,link_height };
		sprites[Walk][Right][6] = { link_x*6,link_y*3,link_width,link_height };

		sprites[Walk][Left][0] = { 0  ,link_y*4,link_width,link_height };
		sprites[Walk][Left][1] = { link_x,link_y*4,link_width,link_height };
		sprites[Walk][Left][2] = { link_x*2,link_y*4,link_width,link_height };
		sprites[Walk][Left][3] = { link_x*3,link_y*4,link_width,link_height };
		sprites[Walk][Left][4] = { link_x*4,link_y*4,link_width,link_height };
		sprites[Walk][Left][5] = { link_x*5,link_y*4,link_width,link_height };
		sprites[Walk][Left][6] = { link_x*6,link_y*4,link_width,link_height };
	}

	//Walk with blue Shield
	{
	
		sprites[Walk_Shield][Up][0] = { 0, link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][1] = { link_x, link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][2] = { link_x * 2 , link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][3] = { link_x * 3, link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][4] = { link_x * 4, link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][5] = { link_x * 5, link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][6] = { link_x * 6, link_y * 6, link_width, link_height };

		sprites[Walk_Shield][Down][0] = { 0 ,  link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][1] = { link_x, link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][2] = { link_x * 2, link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][3] = { link_x * 3, link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][4] = { link_x * 4, link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][5] = { link_x * 5, link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][6] = { link_x * 6, link_y*5, link_width, link_height };

		sprites[Walk_Shield][Right][0] = { 0  ,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][1] = { link_x,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][2] = { link_x * 2,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][3] = { link_x * 3,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][4] = { link_x * 4,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][5] = { link_x * 5,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][6] = { link_x * 6,link_y * 7,link_width,link_height };

		sprites[Walk_Shield][Left][0] = { 0  ,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][1] = { link_x,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][2] = { link_x * 2,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][3] = { link_x * 3,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][4] = { link_x * 4,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][5] = { link_x * 5,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][6] = { link_x * 6,link_y * 8,link_width,link_height };
	
	}
	//Pick-up Object
	//y coordinate for object depends on animation

	{
		sprites[Pickup][Down][0] = { link_x*11, link_y, link_width, link_height };
		sprites[Pickup][Down][1] = { link_x*12, link_y, link_width, link_height };
		sprites[Pickup][Down][2] = { link_x*13, link_y, link_width, link_height };
		sprites[Pickup][Down][3] = { link_x*14, link_y, link_width, link_height };
		sprites[Pickup][Down][4] = { link_x*15, link_y, link_width, link_height };
		sprites[Pickup][Down][5] = { link_x*16, link_y, link_width, link_height };

		sprites[Pickup][Up][0] = { link_x*11, link_y*2, link_width, link_height };
		sprites[Pickup][Up][1] = { link_x*12, link_y*2, link_width, link_height };
		sprites[Pickup][Up][2] = { link_x*13, link_y*2, link_width, link_height };
		sprites[Pickup][Up][3] = { link_x*14, link_y*2, link_width, link_height };	
		sprites[Pickup][Up][4] = { link_x*15, link_y*2, link_width, link_height };
		sprites[Pickup][Up][5] = { link_x*16, link_y*2, link_width, link_height };

		sprites[Pickup][Left][4] = { link_x * 11, link_y * 4, link_width, link_height };
		sprites[Pickup][Left][3] = { link_x * 12, link_y * 4, link_width, link_height };
		sprites[Pickup][Left][2] = { link_x * 13, link_y * 4, link_width, link_height };
		sprites[Pickup][Left][1] = { link_x * 14, link_y * 4, link_width, link_height };
		sprites[Pickup][Left][0] = { link_x*15, link_y*4, link_width, link_height };
		sprites[Pickup][Left][5] = { link_x*16, link_y*4, link_width, link_height };

		sprites[Pickup][Right][0] = { link_x*11, link_y*3, link_width, link_height };
		sprites[Pickup][Right][1] = { link_x*12, link_y*3, link_width, link_height };	
		sprites[Pickup][Right][2] = { link_x*13, link_y*3, link_width, link_height };	
		sprites[Pickup][Right][3] = { link_x*14, link_y*3, link_width, link_height };	
		sprites[Pickup][Right][4] = { link_x*15, link_y*3, link_width, link_height };
		sprites[Pickup][Right][5] = { link_x*16, link_y*3, link_width, link_height };
	}

	//Push Object
	{

		sprites[Push][Down][0] = { link_x*19, link_y, link_width, link_height };
		sprites[Push][Down][1] = { link_x * 18, link_y, link_width, link_height };
		sprites[Push][Down][2] = { link_x * 17, link_y, link_width, link_height };

		sprites[Push][Up][0] = { link_x * 19, link_y * 2, link_width, link_height };
		sprites[Push][Up][1] = { link_x * 18, link_y * 2, link_width, link_height };
		sprites[Push][Up][2] = { link_x*17, link_y*2, link_width, link_height };
			
		sprites[Push][Left][0] = { link_x * 19, link_y*4, link_width, link_height };
		sprites[Push][Left][1] = { link_x*18, link_y*4, link_width, link_height };
		sprites[Push][Left][2] = { link_x * 17, link_y*4, link_width, link_height };
		sprites[Push][Left][3] = { link_x*20, link_y*4, link_width, link_height };

		sprites[Push][Right][0] = { link_x * 19, link_y * 3, link_width, link_height };
		sprites[Push][Right][1] = { link_x * 18, link_y * 3, link_width, link_height };
		sprites[Push][Right][2] = { link_x*17, link_y*3, link_width, link_height };
		sprites[Push][Right][3] = { link_x*20, link_y*3, link_width, link_height };


	}
	//Pull Object
	{
	

	
	}

	//Sword Charge Idle

	//Sword Charge Walk

	// !_SDL_Rects

	// Load Textures

	Link_Movement = App->tex->Load("Sprites/Link_Movement.png");

	// !_Textures

	// Animations Settup

	// Idle
	{
		animations[Idle][Up].PushBack(sprites[Idle][Up][0]);
		animations[Idle][Down].PushBack(sprites[Idle][Down][0]);
		animations[Idle][Left].PushBack(sprites[Idle][Left][0]);
		animations[Idle][Right].PushBack(sprites[Idle][Right][0]);
	}

	//Idle Shield
	{
		animations[Idle_Shield][Up].PushBack(sprites[Idle_Shield][Up][0]);
		animations[Idle_Shield][Down].PushBack(sprites[Idle_Shield][Down][0]);
		animations[Idle_Shield][Left].PushBack(sprites[Idle_Shield][Left][0]);
		animations[Idle_Shield][Right].PushBack(sprites[Idle_Shield][Right][0]);
	}

	// Walking
	{

		// Walking UP 
		{
			animations[Walk][Up].PushBack(sprites[Walk][Up][0]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][1]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][2]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][3]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][4]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][5]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][6]);
			animations[Walk][Up].speed = PL_WALK_FPS;
		}

		// Walking DOWN
		{
			animations[Walk][Down].PushBack(sprites[Walk][Down][0]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][1]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][2]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][3]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][4]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][5]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][6]);
			animations[Walk][Down].speed = PL_WALK_FPS;
		}

		// Walking LEFT
		{
			animations[Walk][Left].PushBack(sprites[Walk][Left][0]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][1]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][2]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][3]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][4]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][5]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][6]);
			animations[Walk][Left].speed = PL_WALK_FPS;
		}

		// Walking RIGHT
		{
			animations[Walk][Right].PushBack(sprites[Walk][Right][0]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][1]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][2]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][3]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][4]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][5]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][6]);
			animations[Walk][Right].speed = PL_WALK_FPS;
		}

		// Walking Shield UP 
		{
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][0]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][1]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][2]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][3]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][4]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][5]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][6]);
			animations[Walk_Shield][Up].speed = PL_WALK_FPS;
		}

		// Walking Shield DOWN
		{
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][0]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][1]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][2]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][3]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][4]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][5]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][6]);
			animations[Walk_Shield][Down].speed = PL_WALK_FPS;
		}

		// Walking Shield LEFT
		{
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][0]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][1]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][2]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][3]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][4]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][5]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][6]);
			animations[Walk_Shield][Left].speed = PL_WALK_FPS;
		}

		// Walking Shield RIGHT
		{
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][0]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][1]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][2]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][3]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][4]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][5]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][6]);
			animations[Walk_Shield][Right].speed = PL_WALK_FPS;
		}

	}

	// Pick up Objects
	{

		// Pickup UP 
		{
			animations[Pickup][Up].PushBack(sprites[Pickup][Up][0]);
			animations[Pickup][Up].PushBack(sprites[Pickup][Up][1]);
			animations[Pickup][Up].PushBack(sprites[Pickup][Up][2]);
			animations[Pickup][Up].PushBack(sprites[Pickup][Up][3]);
			animations[Pickup][Up].PushBack(sprites[Pickup][Up][4]);
			animations[Pickup][Up].PushBack(sprites[Pickup][Up][5]);
			animations[Pickup][Up].speed = 0.2f;
		}

		// Pickup DOWN
		{
			animations[Pickup][Down].PushBack(sprites[Pickup][Down][0]);
			animations[Pickup][Down].PushBack(sprites[Pickup][Down][1]);
			animations[Pickup][Down].PushBack(sprites[Pickup][Down][2]);
			animations[Pickup][Down].PushBack(sprites[Pickup][Down][3]);
			animations[Pickup][Down].PushBack(sprites[Pickup][Down][4]);
			animations[Pickup][Down].PushBack(sprites[Pickup][Down][5]);
			animations[Pickup][Down].speed = 0.2f;
		}

		// Pickup LEFT
		{
			animations[Pickup][Left].PushBack(sprites[Pickup][Left][0]);
			animations[Pickup][Left].PushBack(sprites[Pickup][Left][1]);
			animations[Pickup][Left].PushBack(sprites[Pickup][Left][2]);
			animations[Pickup][Left].PushBack(sprites[Pickup][Left][3]);
			animations[Pickup][Left].PushBack(sprites[Pickup][Left][4]);
			animations[Pickup][Left].PushBack(sprites[Pickup][Left][5]);
			animations[Pickup][Left].speed = 0.2f;
		}

		// Pickup RIGHT
		{
			animations[Pickup][Right].PushBack(sprites[Pickup][Right][0]);
			animations[Pickup][Right].PushBack(sprites[Pickup][Right][1]);
			animations[Pickup][Right].PushBack(sprites[Pickup][Right][2]);
			animations[Pickup][Right].PushBack(sprites[Pickup][Right][3]);
			animations[Pickup][Right].PushBack(sprites[Pickup][Right][4]);
			animations[Pickup][Right].PushBack(sprites[Pickup][Right][5]);
			animations[Pickup][Right].speed = 0.2f;
		}
	}


	// Push Objects

	{

		// Push UP 
		{
			animations[Push][Up].PushBack(sprites[Push][Up][0]);
			animations[Push][Up].PushBack(sprites[Push][Up][1]);
			animations[Push][Up].PushBack(sprites[Push][Up][2]);
			animations[Push][Up].speed = 0.2f;
		}

		// Push DOWN
		{
			animations[Push][Down].PushBack(sprites[Push][Down][0]);
			animations[Push][Down].PushBack(sprites[Push][Down][1]);
			animations[Push][Down].PushBack(sprites[Push][Down][2]);
			animations[Push][Down].speed = 0.2f;
		}

		// Push LEFT
		{
			animations[Push][Left].PushBack(sprites[Push][Left][0]);
			animations[Push][Left].PushBack(sprites[Push][Left][1]);
			animations[Push][Left].PushBack(sprites[Push][Left][2]);
			animations[Push][Left].PushBack(sprites[Push][Left][3]);
			animations[Push][Left].speed = 0.2f;
		}

		// Push RIGHT
		{
			animations[Push][Right].PushBack(sprites[Push][Right][0]);
			animations[Push][Right].PushBack(sprites[Push][Right][1]);
			animations[Push][Right].PushBack(sprites[Push][Right][2]);
			animations[Push][Right].PushBack(sprites[Push][Right][3]);
			animations[Push][Right].speed = 0.2f;
		}

	}

	// Sword Slash
	{
		// Slash Down
		{
			animations[Slash][Down].PushBack(sprites[Slash][Down][0]);
			animations[Slash][Down].PushBack(sprites[Slash][Down][1]);
			animations[Slash][Down].PushBack(sprites[Slash][Down][2]);
			animations[Slash][Down].PushBack(sprites[Slash][Down][3]);
			animations[Slash][Down].PushBack(sprites[Slash][Down][4]);
			animations[Slash][Down].PushBack(sprites[Slash][Down][5]);
		}

		// Slash Up
		{
			animations[Slash][Up].PushBack(sprites[Slash][Up][0]);
			animations[Slash][Up].PushBack(sprites[Slash][Up][1]);
			animations[Slash][Up].PushBack(sprites[Slash][Up][2]);
			animations[Slash][Up].PushBack(sprites[Slash][Up][3]);
			animations[Slash][Up].PushBack(sprites[Slash][Up][4]);
			animations[Slash][Up].PushBack(sprites[Slash][Up][5]);
			animations[Slash][Up].PushBack(sprites[Slash][Up][6]);
			animations[Slash][Up].PushBack(sprites[Slash][Up][7]);
			animations[Slash][Up].PushBack(sprites[Slash][Up][8]);
		}

		// Slash Left
		{
			animations[Slash][Left].PushBack(sprites[Slash][Left][0]);
			animations[Slash][Left].PushBack(sprites[Slash][Left][1]);
			animations[Slash][Left].PushBack(sprites[Slash][Left][2]);
			animations[Slash][Left].PushBack(sprites[Slash][Left][3]);
			animations[Slash][Left].PushBack(sprites[Slash][Left][4]);
			animations[Slash][Left].PushBack(sprites[Slash][Left][5]);
			animations[Slash][Left].PushBack(sprites[Slash][Left][6]);
			animations[Slash][Left].PushBack(sprites[Slash][Left][7]);
			animations[Slash][Left].PushBack(sprites[Slash][Left][8]);
		}

		// Slash Right
		{
			animations[Slash][Right].PushBack(sprites[Slash][Right][0]);
			animations[Slash][Right].PushBack(sprites[Slash][Right][1]);
			animations[Slash][Right].PushBack(sprites[Slash][Right][2]);
			animations[Slash][Right].PushBack(sprites[Slash][Right][3]);
			animations[Slash][Right].PushBack(sprites[Slash][Right][4]);
			animations[Slash][Right].PushBack(sprites[Slash][Right][5]);
			animations[Slash][Right].PushBack(sprites[Slash][Right][6]);
			animations[Slash][Right].PushBack(sprites[Slash][Right][7]);
			animations[Slash][Right].PushBack(sprites[Slash][Right][8]);
		}
	
	}

	animations[Walk][Down].PushBack(sprites[Idle][Down][0]);
	animations[Walk][Left].PushBack(sprites[Idle][Left][0]);
	animations[Walk][Right].PushBack(sprites[Idle][Right][0]);

	// animations speed settup
	//This was bad because not all animations are played back in the same speed, every animation requires a speed setup
	{
		for (int n_dir = Direction::FirstDir; n_dir < Direction::LastDir; n_dir++) {
			animations[Pickup][n_dir].speed = 0.09f;
		}
		for (int n_dir = Direction::FirstDir; n_dir < Direction::LastDir; n_dir++) {
			animations[Slash][n_dir].speed = 0.0002f;
		}
	}

	sword_fx = App->audio->LoadFx("Audio/Fx/Fighter_sword_1.wav");
	low_hp = App->audio->LoadFx("Audio/Fx/low_hp.wav");
	die_fx = App->audio->LoadFx("Audio/Fx/link_dies.wav");
	open_inv_fx = App->audio->LoadFx("Audio/Fx/menu_open.wav");
	close_inv_fx = App->audio->LoadFx("Audio/Fx/menu_close.wav");
	hurt = App->audio->LoadFx("Audio/FX/link_hurt");
	// !_Animations


	SDL_Rect WeaponRect = { FARLANDS.x, FARLANDS.y, WPN_COL_W, WPN_COL_H };
	weapon_coll = App->collisions->AddCollider(WeaponRect, COLLIDER_PL_WEAPON);

	// Variable Settup

	link_coll = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 32, 32 }, COLLIDER_PLAYER, this);

	pl_speed.x = 2.5;
	pl_speed.y = 2.5;

	power = 1;

	curr_dir = Down;

	// !_Variables
	
	// Weapon SetUp

	AddWeapon(t_sword);

	curr_weapon = weapons.begin()._Ptr->_Myval;
	for (int i = 0; i < LastDir; i++) {
		animations[Weapon_atk][i] = curr_weapon->anim[i];
		animations[Weapon_atk][i] = curr_weapon->anim[i];
	}
	

	// !_Weapon SetUp

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;
	//if (alive == false)
	//{
	//	DyingRestart();
	//		action_blit = PickUp;//change to wake Up animation when we have it
	//	return ret;
	//}
	

	// Logic
	if (action == false) {
		//Movement
		{
			if (App->input->GetKey(SDL_SCANCODE_W) && App->input->GetKey(SDL_SCANCODE_A)) {
				if (App->map->TileCheck(pos.x - pl_speed.x, pos.y- pl_speed.y, Up_L) == 0) //change dir
				{
					pos.y -= pl_speed.y * sqrt(2) / 2;
					pos.x -= pl_speed.x * sqrt(2) / 2;
				}
				if (anim_override == false)
					action_blit = Walk;
			}
			else if (App->input->GetKey(SDL_SCANCODE_A) && App->input->GetKey(SDL_SCANCODE_S)) {
				if (App->map->TileCheck(pos.x - pl_speed.x, pos.y + pl_speed.y, Down_L) == 0) //change dir
				{
					pos.y += pl_speed.y * sqrt(2) / 2;
					pos.x -= pl_speed.x * sqrt(2) / 2;
				
				}

				if (anim_override == false)
					action_blit = Walk;

			}
			else if (App->input->GetKey(SDL_SCANCODE_S) && App->input->GetKey(SDL_SCANCODE_D)) {
				if (App->map->TileCheck(pos.x + pl_speed.x, pos.y + pl_speed.y, Down_R) == 0)//change dir
				{
					pos.y += pl_speed.y * sqrt(2) / 2;
					pos.x += pl_speed.x * sqrt(2) / 2;

				}


				if (anim_override == false)
					action_blit = Walk;

			}
			else if (App->input->GetKey(SDL_SCANCODE_D) && App->input->GetKey(SDL_SCANCODE_W)) {
				if (App->map->TileCheck(pos.x + pl_speed.x, pos.y - pl_speed.y, Up_R) == 0)//change dir
				{
					pos.y -= pl_speed.y * sqrt(2) / 2;
					pos.x += pl_speed.x * sqrt(2) / 2;
				}


				if (anim_override == false)
					action_blit = Walk;


			}
			else if (App->input->GetKey(SDL_SCANCODE_W)) {
				if (App->map->TileCheck(pos.x, pos.y - pl_speed.y, Up) == 0)
				{
					pos.y -= pl_speed.y;
				}


				if (anim_override == false)
					action_blit = Walk;
				if (dir_override == false)
					curr_dir = Up;

			}
			else if (App->input->GetKey(SDL_SCANCODE_A)) {
				if (App->map->TileCheck(pos.x - pl_speed.x, pos.y, Left) == 0)
				{
					pos.x -= pl_speed.x;
				}


				if (anim_override == false)
					action_blit = Walk;
				if (dir_override == false)
					curr_dir = Left;
			}
			else if (App->input->GetKey(SDL_SCANCODE_S))
			{
				if (App->map->TileCheck(pos.x, pos.y + pl_speed.y, Down) == 0)
				{
					pos.y += pl_speed.y;
					
				}


				if (anim_override == false)
					action_blit = Walk;
				if (dir_override == false)
					curr_dir = Down;
			}
			else if (App->input->GetKey(SDL_SCANCODE_D))
			{
				if (App->map->TileCheck(pos.x + pl_speed.x, pos.y, Right) == 0)
				{
					pos.x += pl_speed.x;
					
				}


				if (anim_override == false)
					action_blit = Walk;
				if (dir_override == false)
					curr_dir = Right;
			}
			else {
				if (anim_override == false)
					action_blit = Idle;
			}

			last_pos = pos;
			// Direction/Atk
			// This inherently bad, you are ignoring 6 more buttons (X Y L R SELECT START)
			//It would work for gamepad, but not for keyboard
			//Objects will go here too, then they might trigger action or nah

			{
				if(!App->hud->inv->active){
					if (anim_override == false) {

						if (App->input->GetKey(SDL_SCANCODE_UP)) {
							curr_dir = Up;
							action_blit = Weapon_atk;
							if (curr_weapon != nullptr)
								curr_weapon->Attack();
							App->audio->PlayFx(sword_fx);
							dir_override = true;
							anim_override = true;
							pl_speed.x = pl_speed.x / PL_SPD_ATK;
							pl_speed.y = pl_speed.y / PL_SPD_ATK;
						}
						else if (App->input->GetKey(SDL_SCANCODE_DOWN)) {
							curr_dir = Down;
							action = false;
							action_blit = Weapon_atk;
							if (curr_weapon != nullptr)
								curr_weapon->Attack();
							App->audio->PlayFx(sword_fx);
							dir_override = true;
							anim_override = true;
							pl_speed.x = pl_speed.x / PL_SPD_ATK;
							pl_speed.y = pl_speed.y / PL_SPD_ATK;
						}
						else if (App->input->GetKey(SDL_SCANCODE_RIGHT)) {
							curr_dir = Right;
							action_blit = Weapon_atk;
							if (curr_weapon != nullptr)
								curr_weapon->Attack();
							App->audio->PlayFx(sword_fx);
							dir_override = true;
							anim_override = true;
							pl_speed.x = pl_speed.x / PL_SPD_ATK;
							pl_speed.y = pl_speed.y / PL_SPD_ATK;
						}
						else if (App->input->GetKey(SDL_SCANCODE_LEFT)) {
							curr_dir = Left;
							action_blit = Weapon_atk;
							if (curr_weapon != nullptr)
								curr_weapon->Attack();
							App->audio->PlayFx(sword_fx);
							dir_override = true;
							anim_override = true;
							pl_speed.x = pl_speed.x / PL_SPD_ATK;
							pl_speed.y = pl_speed.y / PL_SPD_ATK;
						}
					}

				}
				else {
					if (App->input->GetKey(SDL_SCANCODE_UP)==KEY_DOWN) {
						App->hud->inv->Move_Sel_up();
					}
					else if (App->input->GetKey(SDL_SCANCODE_DOWN)==KEY_DOWN) {
						App->hud->inv->Move_Sel_down();
					}
					else if (App->input->GetKey(SDL_SCANCODE_RIGHT)==KEY_DOWN) {
						App->hud->inv->Move_Sel_forward();
					}
					else if (App->input->GetKey(SDL_SCANCODE_LEFT)==KEY_DOWN) {
						App->hud->inv->Move_Sel_backwards();
					}
				}
			}
		}
	}

	if (Slashing == true) {
		curr_weapon->Attack();
		if (action_blit != Weapon_atk) {
			Slashing = false;
			weapon_coll->SetPos(FARLANDS.x, FARLANDS.y);
		}
	}

	// Actions
	{

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
		change_weapon = Q_Change;
	}
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		change_weapon = E_Change;
	}

	if (change_weapon == true && action_blit != Weapon_atk) {
		std::list<Weapon*>::iterator aux_it = std::find(weapons.begin(), weapons.end(), curr_weapon);

		switch (change_weapon) {
		case Q_Change:
			if (aux_it == weapons.begin()) {
				aux_it = weapons.end();
				aux_it--;
			}
			else
				aux_it--;
			break;
		case E_Change:
			if (++aux_it == weapons.end()) {
				aux_it = weapons.begin();
			}
			break;

		}

		curr_weapon = aux_it._Ptr->_Myval;

		for (int i = 0; i < LastDir; i++) {
			animations[Weapon_atk][i] = curr_weapon->anim[i];
			animations[Weapon_atk][i] = curr_weapon->anim[i];
		}

		change_weapon = No_Change;

	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && anim_override == false) {
			//for now perform an action to see animation
			//requires a detector for usage: villager = talk, bush or bomb or pot... = pickup and then throw, lever or rock = pull or push...
			action = true;
			action_blit = Pickup;
		}

	}

			//Idle
	{	
		//if(App->input->GetKey(SDL_SCANCODE))action_blit = Idle;
	}


	// !_Logic

	// Graphics
		if (action == false){
			//Movement or any action that does not stop movement

			if (shield == true && (action_blit == Idle || action_blit == Walk)) //add cases for actions that can be done with or without shield
				action_blit++;
			
			App->render->toDraw(Link_Movement, pos.y - PL_OFFSET_Y + animations[action_blit][curr_dir].GetCurrentFrame().h, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());
			//!_Movement ""

			if (anim_override == true && animations[action_blit][curr_dir].Finished()) {
				anim_override = false;
				dir_override = false;
				animations[action_blit][curr_dir].Reset();
				action_blit = Idle;
				pl_speed.x = pl_speed.x * PL_SPD_ATK;
				pl_speed.y = pl_speed.y * PL_SPD_ATK;
			}
		}
	

	//Actions
		else if (action == true) {

			if (animations[action_blit][curr_dir].Finished() && App->input->GetKey(SDL_SCANCODE_SPACE) != KEY_REPEAT) {
				action = false;
				LOG("ACTIO=N FALSE");
				animations[action_blit][curr_dir].Reset();
				App->render->toDraw(Link_Movement, pos.y - PL_OFFSET_Y + animations[Idle][curr_dir].GetCurrentFrame().h, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[Idle][curr_dir].GetCurrentFrame());
			}
			else {
				App->render->toDraw(Link_Movement, pos.y - PL_OFFSET_Y + animations[action_blit][curr_dir].GetCurrentFrame().h, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());

				if (animations[action_blit][curr_dir].Finished() && App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
					animations[action_blit][curr_dir].Reset();
			}

		}
	//!_Actions	
	
			if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) {
				if (!App->hud->inv->active) {
					App->hud->inv->active = true;
					App->audio->PlayFx(open_inv_fx);
				}
				else{

					App->hud->inv->active = false;
					App->hud->inv->Disable();
					App->audio->PlayFx(close_inv_fx);
			}
		}
	//!_Graphics


	// MODIFY COLLISION -------------------------------------------------
		link_coll->SetPos(pos.x , pos.y + 16);
		/*if ((App->player->curr_life_points <= 2)&&(App->player->curr_life_points!=0)) {
			App->audio->PlayFx(low_hp);
		}*/
		if (App->player->curr_life_points == 0) {
			//Here he should change the scene to the room scene
			DyingRestart();
			App->audio->PlayFx(die_fx);
		}

	if (App->debug_mode == true) {
			inmortal = true;
	}

	if (inmortal == true) {
		App->render->DrawQuad({(int)pos.x - 2, (int)pos.y - 8, 36, 56 }, 255, 255, 255, 80);
		if(App->debug_mode == false)
			if (inmortal_timer.ReadMs() >= inmortal_time)
				inmortal = false;
	}

	return ret;
}

bool j1Player::PostUpdate(float dt)
{
	bool ret = true;


	return ret;
}

bool j1Player::CleanUp()
{
	bool ret = true;
	LOG("Player CleanUp Start");

	// Unloading All Textures
	App->tex->UnLoad(Link_Movement);
	if (link_coll != nullptr)
		link_coll->to_delete = true;
	if (weapon_coll != nullptr)
		weapon_coll->to_delete = true;

	for (std::list<Weapon*>::iterator it = weapons.begin(); it != weapons.end(); it++) {
		if (it._Ptr->_Myval != nullptr)
			it._Ptr->_Myval->CleanUp();
	}

	weapons.clear();

	return ret;
}

void j1Player::UpgradeSPD(float x)
{
	pl_speed.x += x;
	pl_speed.y += x;

	if (pl_speed.x > MAX_SPD) {
		pl_speed.x = MAX_SPD;
		pl_speed.y = MAX_SPD;
	}

}

void j1Player::UpgradePWR(int x)
{
	power += x;

	if (power > MAX_PWR)
		power = MAX_PWR;

}

void j1Player::UpgradeHP(int x)
{
	max_life_points += x;
	
	if (max_life_points > MAX_HP)
		max_life_points = MAX_HP;
}

void j1Player::AddWeapon(uint weapon_t)
{
	Weapon* w = nullptr;
	switch (weapon_t) {
	case t_sword:
		w = new Sword();
		break;
	case t_bow:
		w = new Bow();
		break;
	}

	if (w != nullptr) {
		//if (std::find(weapons.begin(), weapons.end(), w) != weapons.end()) {
			w->Start();
			weapons.push_back(w);
		//}
	}

}

void j1Player::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void j1Player::MovePos(float x, float y)
{
	pos.x += x;
	pos.y += y;
}

bool j1Player::SetPosTile(int x, int y)
{
	bool ret = true;

	pos.x = App->map->MapToWorld(x, y).x;
	pos.y = App->map->MapToWorld(x, y).y;

	return ret;
}

Point<float> j1Player::GetPos()
{
	return pos;
}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	if (link_coll == c1  && (c2->type == COLLIDER_WALL || c2->type == COLLIDER_BUSH) && link_coll != nullptr)
	{
		
		if (pos.y + PLAYER_COLL_Y_OFFSET >= c2->rect.y + c2->rect.h)
		{
			pos.y = c2->rect.y + c2->rect.h;
		}

		else if (pos.y + c1->rect.h - PLAYER_COLL_Y_OFFSET <= c2->rect.y)
		{
			pos.y = c2->rect.y - c1->rect.h;
		}
		else if (c1->rect.x + c1->rect.w >= c2->rect.x && c1->rect.x <= c2->rect.x)
		{
			pos.x = c2->rect.x - c1->rect.w ;
		}
		else if (pos.x  <= c2->rect.x + c2->rect.w)
		{
			//polish this one 
			pos.x = c2->rect.x + c2->rect.w ;
		}
	}

	// Hit collision
	if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_ENEMY && alive == true)
	{
		if (curr_life_points == 0)
			alive = false;

		//Add extra particles?
		//App->explosion->AddExplosion(App->explosion->Player, position.x - 30, position.y - 30, { 0, 0 }, { 0, 0, 105, 115 }, COLLIDER_EXPLOSION);
		//function to restart in the house()
	}
	if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_TO_DUNGEON && alive == true)
		App->scene_manager->village_scene->to_dungeon = true;
	if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_TO_SHOP && alive == true)
		App->scene_manager->village_scene->to_shop = true;
	if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_TO_HOUSE && alive == true)
		App->scene_manager->village_scene->to_house = true;

	if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_TO_OVERWORLD_HOUSE && alive == true)
		App->scene_manager->house_scene->to_overworld = true;
	if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_TO_OVERWORLD_SHOP && alive == true)
		App->scene_manager->shop_scene->to_overworld = true;

	if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_DUNGEON_UP && alive == true)
		App->scene_manager->dungeon_scene->up = true;
	if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_DUNGEON_DOWN && alive == true)
		App->scene_manager->dungeon_scene->down = true;
	if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_DUNGEON_LEFT && alive == true)
		App->scene_manager->dungeon_scene->left = true;
	if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_DUNGEON_RIGHT && alive == true)
		App->scene_manager->dungeon_scene->right = true;

		//Add extra particles?
		//App->explosion->AddExplosion(App->explosion->Player, position.x - 30, position.y - 30, { 0, 0 }, { 0, 0, 105, 115 }, COLLIDER_EXPLOSION);
		//function to restart in the house()

}
void j1Player::DyingRestart()
{
	alive = true;
	pos = ORIGIN_RESTART;
	App->scene_manager->ChangeScene((Scene*)App->scene_manager->house_scene);
	App->hud->inv->CleanUp();
	max_life_points = 6;
	power = 1;
	rupees = floor(rupees / 2);
	bombs = 0;
	arrows = 0;
	curr_life_points = max_life_points;
	//add more features to discuss by the designer
	action = true;
}

void j1Player::PlayerInmortal(float time)
{
	inmortal = true;
	inmortal_time = time;
	inmortal_timer.Start();
}

bool j1Player::Find_inv(Item* item)
{
	for (std::list<Item*>::const_iterator it = inventory.cbegin(); it != inventory.cend(); it++) {
		if (item->Subtype() == it._Ptr->_Myval->Subtype()) {
			return true;
		}

	}
	return false;

}

bool j1Player::Find_weapon(Item* item)
{
	for (std::list<Weapon*>::const_iterator it = weapons.cbegin(); it !=weapons.cend(); it++) {
		if (item->Subtype() == it._Ptr->_Myval->Subtype()) {
			return true;
		}

	}
	return false;

}

