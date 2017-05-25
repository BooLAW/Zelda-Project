#include "j1Player.h"
#include "j1Input.h"
#include "j1Collision.h"
#include "j1Map.h"
#include "ModuleParticles.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DungeonScene.h"
#include "VillageScene.h"
#include "MathHelpers.h"
#include <list>
#include <fstream>

j1Player::j1Player()
{
	name = "player";
}

j1Player::~j1Player()
{
}

bool j1Player::Awake()
{
	bool ret = true;
	//LOG("Player Awake Start");

	

	return ret;
}

bool j1Player::Start()
{
	
	bool ret = true;
	LOG("Player Start");
	//CONTROLS
	keys = 0;
	rupees = 50;
	controller_index = 0;
	dash_fx = App->audio->LoadFx("Audio/Fx/break.wav");
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

	//Link Wake up
	{
		sprites[Wake_up][Down][0] = { 0  ,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][1] = { link_x,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][2] = { link_x * 2,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][3] = { link_x * 3,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][4] = { link_x * 4,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][5] = { link_x * 5,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][6] = { link_x * 6,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][7] = { link_x * 7,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][8] = { link_x * 8,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][9] = { link_x * 9,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][10] = { link_x * 10,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][11] = { link_x * 11,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][12] = { link_x * 12,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][13] = { link_x * 13,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][14] = { link_x * 14,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][15] = { link_x * 15,link_y * 8,link_width,link_height };
		sprites[Wake_up][Down][16] = { link_x * 16,link_y * 8,link_width,link_height };
		



	}

	// Dash
	{

		sprites[Dash][Up][0] =		{ link_x * 12, link_y * 6, link_width, link_height };
		sprites[Dash][Up][1] =		{ link_x * 13, link_y * 6, link_width, link_height };
		sprites[Dash][Up][2] =		{ link_x * 14, link_y * 6, link_width, link_height };
		sprites[Dash][Up][3] =		{ link_x * 15, link_y * 6, link_width, link_height };
		sprites[Dash][Up][4] =		{ link_x * 16, link_y * 6, link_width, link_height };
		sprites[Dash][Up][5] = { link_x * 16, link_y * 6, link_width, link_height };

		sprites[Dash][Down][0] =	{ link_x * 12, link_y * 5, link_width, link_height };
		sprites[Dash][Down][1] =	{ link_x * 13, link_y * 5, link_width, link_height };
		sprites[Dash][Down][2] =	{ link_x * 14, link_y * 5, link_width, link_height };
		sprites[Dash][Down][3] =	{ link_x * 15, link_y * 5, link_width, link_height };
		sprites[Dash][Down][4] =	{ link_x * 16, link_y * 5, link_width, link_height };
		sprites[Dash][Down][5] = { link_x * 16, link_y * 5, link_width, link_height };

		sprites[Dash][Left][5] = { link_x * 12, link_y * 8, link_width, link_height };
		sprites[Dash][Left][4] =	{ link_x * 12, link_y * 8, link_width, link_height };
		sprites[Dash][Left][3] = { link_x * 13, link_y * 8, link_width, link_height };
		sprites[Dash][Left][2] = { link_x * 14, link_y * 8, link_width, link_height };
		sprites[Dash][Left][1] = { link_x * 15, link_y * 8, link_width, link_height };
		sprites[Dash][Left][0] = { link_x * 16, link_y * 8, link_width, link_height };

		sprites[Dash][Right][0] =	{ link_x * 12, link_y * 7, link_width, link_height };
		sprites[Dash][Right][1] = { link_x * 13, link_y * 7, link_width, link_height };
		sprites[Dash][Right][2] = { link_x * 14, link_y * 7, link_width, link_height };
		sprites[Dash][Right][3] = { link_x * 15, link_y * 7, link_width, link_height };
		sprites[Dash][Right][4] = { link_x * 16, link_y * 7, link_width, link_height };
		sprites[Dash][Right][5] = { link_x * 16, link_y * 7, link_width, link_height };



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
	
		sprites[Pull][Down][0] = { link_x * 7, link_y, link_width, link_height };
		sprites[Pull][Down][1] = { link_x * 8, link_y, link_width, link_height };
		sprites[Pull][Down][2] = { link_x * 9, link_y, link_width, link_height };
		sprites[Pull][Down][3] = { link_x * 10, link_y, link_width, link_height };
		
		sprites[Pull][Up][0] = { link_x * 7, link_y * 2, link_width, link_height };
		sprites[Pull][Up][1] = { link_x * 8, link_y * 2, link_width, link_height };
		sprites[Pull][Up][2] = { link_x * 9, link_y * 2, link_width, link_height };
		sprites[Pull][Up][3] = { link_x * 10, link_y * 2, link_width, link_height };
		
		sprites[Pull][Left][0] = { link_x * 7, link_y * 4, link_width, link_height };
		sprites[Pull][Left][1] = { link_x * 8, link_y * 4, link_width, link_height };
		sprites[Pull][Left][2] = { link_x * 9, link_y * 4, link_width, link_height };
		sprites[Pull][Left][3] = { link_x * 10, link_y * 4, link_width, link_height };
		
		sprites[Pull][Right][3] = { link_x * 7, link_y * 3, link_width, link_height };
		sprites[Pull][Right][2] = { link_x * 8, link_y * 3, link_width, link_height };
		sprites[Pull][Right][1] = { link_x * 9, link_y * 3, link_width, link_height };
		sprites[Pull][Right][0] = { link_x * 10, link_y * 3, link_width, link_height };
	
	}
	{
		// All animation since sleeping until Link wakes up
		sprites[Sleep_Wake_up][Down][0] = { link_x * 2, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][1] = { link_x * 3, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][2] = { link_x * 4, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][3] = { link_x * 5, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][4] = { link_x * 6, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][5] = { link_x * 7, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][6] = { link_x * 8, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][7] = { link_x * 9, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][8] = { link_x * 10, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][9] = { link_x * 11, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][10] = { link_x * 12, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][11] = { link_x * 13, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][12] = { link_x * 14, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][13] = { link_x * 15, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][14] = { link_x * 16, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][15] = { link_x * 17, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][16] = { link_x * 18, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][17] = { link_x * 19, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][18] = { link_x * 20, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][19] = { link_x * 21, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][20] = { link_x * 22, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][21] = { link_x * 23, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][22] = { link_x * 24, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][23] = { link_x * 25, link_y * 14, link_width, link_height };
		sprites[Sleep_Wake_up][Down][24] = { link_x * 26, link_y * 14, link_width, link_height };

		// here is waking up from the bed
		sprites[Sleep_Wake_up][Down][25] = { link_x * 2, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][26] = { link_x * 3, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][27] = { link_x * 4, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][28] = { link_x * 5, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][29] = { link_x * 6, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][30] = { link_x * 7, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][31] = { link_x * 8, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][32] = { link_x * 9, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][33] = { link_x * 10, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][34] = { link_x * 11, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][35] = { link_x * 12, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][36] = { link_x * 13, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][37] = { link_x * 14, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][38] = { link_x * 15, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][39] = { link_x * 16, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][40] = { link_x * 17, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][41] = { link_x * 18, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][42] = { link_x * 19, link_y * 15, link_width, link_height };
		sprites[Sleep_Wake_up][Down][43] = { link_x * 20, link_y * 15, link_width, link_height };


	}

	{
		// Only waking up

		sprites[Wake_up][Down][0] = { link_x * 2, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][1] = { link_x * 3, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][2] = { link_x * 4, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][3] = { link_x * 5, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][4] = { link_x * 6, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][5] = { link_x * 7, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][6] = { link_x * 8, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][7] = { link_x * 9, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][8] = { link_x * 10, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][9] = { link_x * 11, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][10] = { link_x * 12, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][11] = { link_x * 13, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][12] = { link_x * 14, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][13] = { link_x * 15, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][14] = { link_x * 16, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][15] = { link_x * 17, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][16] = { link_x * 18, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][17] = { link_x * 19, link_y * 15, link_width, link_height };
		sprites[Wake_up][Down][18] = { link_x * 20, link_y * 15, link_width, link_height };
	}
	{
		// Dying animation

		sprites[Die][Right][0] = { link_x * 19, link_y * 11, link_width, link_height };
		sprites[Die][Right][1] = { link_x * 20, link_y * 11, link_width, link_height };
		sprites[Die][Right][2] = { link_x * 21, link_y * 11, link_width, link_height };

		

	}
	//Sword Charge Idle

	//Sword Charge Walk

	// !_SDL_Rects

	// Load Textures

	Link_Movement = App->tex->Load("Sprites/Link_Movement.png");
	

	// !_Textures

	// Animations Settup

	{

		for (int i = 0; i < LastDir; i++) {
			for (int k = 0; k < 6; k++) {
				animations[Dash][i].PushBack(sprites[Dash][i][k]);
			}
			animations[Dash][i].speed = 0.1;
		}
	}

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

	{
	// Dying

	animations[Die][Right].PushBack(sprites[Die][Right][0]);
	animations[Die][Right].PushBack(sprites[Die][Right][1]);
	animations[Die][Right].PushBack(sprites[Die][Right][2]);
	animations[Die][Right].speed = 0.1f;

	}

	// Sleep & Waking up
	{
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][0]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][1]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][2]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][3]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][4]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][5]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][6]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][7]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][8]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][9]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][10]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][11]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][12]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][13]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][14]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][15]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][16]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][17]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][18]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][19]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][20]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][21]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][22]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][23]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][24]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][25]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][26]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][27]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][28]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][29]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][30]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][31]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][32]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][33]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][34]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][35]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][36]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][37]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][38]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][39]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][40]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][41]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][42]);
	animations[Sleep_Wake_up][Down].PushBack(sprites[Sleep_Wake_up][Down][43]);
	animations[Sleep_Wake_up][Down].speed = 0.2f;


}

	{
		// Only waking up

		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][0]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][1]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][2]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][3]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][4]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][5]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][6]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][7]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][8]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][9]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][10]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][11]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][12]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][13]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][14]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][15]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][16]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][17]);
		animations[Wake_up][Down].PushBack(sprites[Wake_up][Down][18]);
		animations[Wake_up][Down].speed = 0.2f;
		
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
			animations[Push][Up].speed = 0.05f;
		}

		// Push DOWN
		{
			animations[Push][Down].PushBack(sprites[Push][Down][0]);
			animations[Push][Down].PushBack(sprites[Push][Down][1]);
			animations[Push][Down].PushBack(sprites[Push][Down][2]);
			animations[Push][Down].speed = 0.05f;
		}

		// Push LEFT
		{
			animations[Push][Left].PushBack(sprites[Push][Left][0]);
			animations[Push][Left].PushBack(sprites[Push][Left][1]);
			animations[Push][Left].PushBack(sprites[Push][Left][2]);
			animations[Push][Left].PushBack(sprites[Push][Left][3]);
			animations[Push][Left].speed = 0.05f;
		}

		// Push RIGHT
		{
			animations[Push][Right].PushBack(sprites[Push][Right][0]);
			animations[Push][Right].PushBack(sprites[Push][Right][1]);
			animations[Push][Right].PushBack(sprites[Push][Right][2]);
			animations[Push][Right].PushBack(sprites[Push][Right][3]);
			animations[Push][Right].speed = 0.05f;
		}

	}

	// Pull Objects
	
	{
		
					// Pull UP 
		{
			animations[Pull][Up].PushBack(sprites[Pull][Up][1]);
			animations[Pull][Up].PushBack(sprites[Pull][Up][2]);
			animations[Pull][Up].PushBack(sprites[Pull][Up][3]);
			animations[Pull][Up].speed = 0.05f;
		}
		
					// Pull DOWN
		{
			animations[Pull][Down].PushBack(sprites[Pull][Down][1]);
			animations[Pull][Down].PushBack(sprites[Pull][Down][2]);
			animations[Pull][Down].PushBack(sprites[Pull][Down][3]);
			animations[Pull][Down].speed = 0.05f;
		}
		
					// Pull LEFT
		{
			animations[Pull][Left].PushBack(sprites[Pull][Left][1]);
			animations[Pull][Left].PushBack(sprites[Pull][Left][2]);
			animations[Pull][Left].PushBack(sprites[Pull][Left][3]);
			animations[Pull][Left].speed = 0.05f;
		}
		
					// Pull RIGHT
		{
			animations[Pull][Right].PushBack(sprites[Pull][Right][3]);
			animations[Pull][Right].PushBack(sprites[Pull][Right][2]);
			animations[Pull][Right].PushBack(sprites[Pull][Right][1]);
			animations[Pull][Right].speed = 0.05f;
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
	hurt = App->audio->LoadFx("Audio/Fx/link_hurt.wav");
	// !_Animations


	SDL_Rect WeaponRect = { FARLANDS.x, FARLANDS.y, WPN_COL_W, WPN_COL_H };
	weapon_coll = App->collisions->AddCollider(WeaponRect, COLLIDER_PL_WEAPON);

	// Variable Settup

	link_coll = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 32, 32 }, COLLIDER_PLAYER, this);
	action_coll = App->collisions->AddCollider({ FARLANDS.x,FARLANDS.y, WPN_COL_W / 4, WPN_COL_H / 4 }, COLLIDER_ACTION);
	mov_coll = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 24, 24 }, COLLIDER_PLAYER, this);

	pl_speed.x = ORIGIN_SPD;
	pl_speed.y = ORIGIN_SPD;

	power = 30;

	curr_dir = Down;

	// !_Variables

	// Weapon SetUp

	AddWeapon(t_sword);


	curr_weapon = weapons.begin()._Ptr->_Myval;
	for (int i = 0; i < LastDir; i++) {
		animations[Weapon_atk][i] = curr_weapon->anim[i];
		animations[Weapon_atk][i] = curr_weapon->anim[i];
	}

	for (int i = 0; i < 5; i++) {
		push[i] = false;
		pull[i] = false;

	}
	// !_Weapon SetUp
	room = { 2,3 };
	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;

	if (inMainScreen) {

	}
	else {
		if (!App->IsPaused()) {
			w_a_timer.Start();
			w_a_timer.SetFlag(true);
			if (App->player->power > MAX_PWR)
				App->player->power = MAX_PWR;
			if (App->player->power < MIN_PWR)
				App->player->power = MIN_PWR;
			
			if (App->player->pl_speed.x > MAX_SPD) {
				App->player->pl_speed.x = MAX_SPD;
				App->player->pl_speed.y = MAX_SPD;
			}
			//if (App->player->pl_speed.x < MIN_SPD) {
			//	App->player->pl_speed = { MIN_SPD, MIN_SPD };
			//}
			
			if (App->player->max_life_points > MAX_HP)
				App->player->max_life_points = MAX_HP;
			if (App->player->max_life_points < MIN_HP)
				App->player->max_life_points = MIN_HP;
			
			if (curr_life_points > max_life_points) {
				curr_life_points = max_life_points;
			}
			if(!App->hud->Minimap->active)
			if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
				if ((App->scene_manager->dungeon_id == 5)||(App->scene_manager->dungeon_id == 6)) {
					App->hud->Minimap->active = false;
					App->hud->link_point->active = false;
				}
				else {
					App->hud->Enable_map();
				}
			}
			if (talking) {
				App->render->toDraw(Link_Movement, pos.y - PL_OFFSET_Y + animations[action_blit][curr_dir].GetCurrentFrame().h, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());
				App->hud->dialog->active = true;
				App->render->DrawQuad({ App->hud->dialog->pos.x - 10, App->hud->dialog->pos.y - 10,500,50 }, 128, 128, 128, 100);
				if (App->hud->dialog_num < App->dialog->DialogtoPrint(App->player->toTalk->npcId)->texts.size()) {
					App->hud->dialog->str = App->dialog->DialogtoPrint(App->player->toTalk->npcId)->texts[App->hud->dialog_num]->line->c_str();
				}
				if (App->input->GetKey(App->input->controls[ACTION]) == KEY_DOWN) {
					if (App->hud->dialog_num < App->dialog->DialogtoPrint(App->player->toTalk->npcId)->texts.size()) {
						App->hud->dialog_num++;
					}
					else {
						App->hud->dialog_num = 0;
						App->hud->dialog->active = false;
						talking = false;
					}
				}

			}
			
			
			else {
				Room* c_r = App->scene_manager->GetCurrentScene()->GetRoom(room.x, room.y);

				if (App->debug_mode == true)
					if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
						if (c_r->enemies.empty() == false) {
							for (std::list<Enemy*>::iterator it = c_r->enemies.begin(); it != c_r->enemies.end(); it++) {
								if (it._Ptr->_Myval != nullptr)
									it._Ptr->_Myval->Hit(Down, 9999);
							}
						}
					}

				//if (alive == false)
				//{
				//	DyingRestart();
				//	//action_blit = Sleep_Wake_up;//change to wake Up animation when we have it
				//	return ret;
				//}
				if (App->render->cam_travel != true) {
					if (App->debug_mode == true)
						if (App->input->GetKey(SDL_SCANCODE_RCTRL) == KEY_DOWN) {
							App->player->SetPos(-App->render->camera.x + App->render->camera.w / 2, -App->render->camera.y + App->render->camera.h / 2);
						}
					// Logic
					if (App->debug_mode == false)
					{
						if (action == false)
						{
							Movement();
							Slash_();
						}
					}
					if (Slashing == true)
					{
						curr_weapon->Attack();
						if (action_blit != Weapon_atk)
						{
							Slashing = false;
							weapon_coll->SetPos(FARLANDS.x, FARLANDS.y);
						}

					}

					// Actions
					{

						/*if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) {
							dir_override = true;
							anim_override = true;
							action = true;
							action_blit = Sleep_Wake_up;
							curr_dir = Down;

						}

						if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
							dir_override = true;
							anim_override = true;
							action = true;
							action_blit = Wake_up;
							curr_dir = Down;
						}*/

						/*if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
							dir_override = true;
							anim_override = true;
							action = true;
							action_blit = Die;
							curr_dir = Right;
						}*/

						if (App->input->GetKey(App->input->controls[WPN_NEXT]) == KEY_DOWN) {
							change_weapon = Q_Change;
						}
						if (App->input->GetKey(App->input->controls[WPN_PREV]) == KEY_DOWN) {
							change_weapon = E_Change;
						}
						ChangeWeapon();

						if (anim_override == false) {
							if (App->input->GetKey(App->input->controls[MOVE_UP]) == KEY_REPEAT || App->input->GetKey(App->input->controls[MOVE_LEFT]) == KEY_REPEAT || App->input->GetKey(App->input->controls[MOVE_DOWN]) == KEY_REPEAT || App->input->GetKey(App->input->controls[MOVE_RIGHT]) == KEY_REPEAT) {
								if (App->input->GetKey(App->input->controls[DASH]) == KEY_DOWN) {
									App->audio->PlayFx(dash_fx);
									action_blit = Dash;
									action = true;
									//dir_override = true;
									//anim_override = true;
								}
							}
						}

						if (action_blit != Dash) {
							link_coll->active = true;
						}

						if (action == true && action_blit == Dash) {
							PlayerInmortal(1);
							link_coll->active = false;
							if (App->input->GetKey(App->input->controls[MOVE_UP]) && App->input->GetKey(App->input->controls[MOVE_LEFT])) {
								if (CheckSpace(pos.x - pl_speed.x * (sqrt(2) / 2), pos.y - pl_speed.y  * (sqrt(2) / 2)) == 0) {
									pos.x -= pl_speed.x * DASH_SPD * (sqrt(2) / 2);
									pos.y -= pl_speed.y * DASH_SPD * (sqrt(2) / 2);
								}
							}
							else if (App->input->GetKey(App->input->controls[MOVE_UP]) && App->input->GetKey(App->input->controls[MOVE_RIGHT])) {
								if (CheckSpace(pos.x + pl_speed.x * DASH_SPD * (sqrt(2) / 2), pos.y - pl_speed.y * DASH_SPD * (sqrt(2) / 2)) == 0) {
									pos.x += pl_speed.x * DASH_SPD * (sqrt(2) / 2);
									pos.y -= pl_speed.y * DASH_SPD * (sqrt(2) / 2);
								}
							}
							else if (App->input->GetKey(App->input->controls[MOVE_DOWN]) && App->input->GetKey(App->input->controls[MOVE_LEFT])) {
								if (CheckSpace(pos.x - pl_speed.x * DASH_SPD * (sqrt(2) / 2), pos.y + pl_speed.y * DASH_SPD * (sqrt(2) / 2)) == 0) {
									pos.x -= pl_speed.x * DASH_SPD * (sqrt(2) / 2);
									pos.y += pl_speed.y * DASH_SPD * (sqrt(2) / 2);
								}
							}
							else if (App->input->GetKey(App->input->controls[MOVE_DOWN]) && App->input->GetKey(App->input->controls[MOVE_RIGHT])) {
								if (CheckSpace(pos.x + pl_speed.x * DASH_SPD * (sqrt(2) / 2), pos.y + pl_speed.y * DASH_SPD * (sqrt(2) / 2)) == 0) {
									pos.x += pl_speed.x * DASH_SPD * (sqrt(2) / 2);
									pos.y += pl_speed.y * DASH_SPD * (sqrt(2) / 2);
								}
							}
							else if (App->input->GetKey(App->input->controls[MOVE_UP])) {
								if (CheckSpace(pos.x, pos.y - pl_speed.y * DASH_SPD) == 0) {
									pos.y -= pl_speed.y * DASH_SPD;
								}
							}
							else if (App->input->GetKey(App->input->controls[MOVE_LEFT])) {
								if (CheckSpace(pos.x - pl_speed.x * DASH_SPD, pos.y) == 0) {
									pos.x -= pl_speed.x * DASH_SPD;
								}
							}
							else if (App->input->GetKey(App->input->controls[MOVE_DOWN])) {
								if (CheckSpace(pos.x, pos.y + pl_speed.y * DASH_SPD) == 0) {
									pos.y += pl_speed.y * DASH_SPD;
								}
							}
							else if (App->input->GetKey(App->input->controls[MOVE_RIGHT])) {
								if (CheckSpace(pos.x + pl_speed.x * DASH_SPD, pos.y) == 0) {
									pos.x += pl_speed.x * DASH_SPD;
								}
							}
						}

						if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && anim_override == false) {
							//for now perform an action to see animation
							//requires a detector for usage: villager = talk, bush or bomb or pot... = pickup and then throw, lever or rock = pull or push...
							action_test = true;
							switch (curr_dir) {
							case Up:
								App->player->action_coll->rect = { (int)App->player->GetPos().x, (int)App->player->link_coll->rect.y - WPN_COL_W / 4, WPN_COL_H / 4, WPN_COL_W / 4 };
								break;
							case Down:
								App->player->action_coll->rect = { (int)App->player->GetPos().x, (int)App->player->link_coll->rect.y + App->player->link_coll->rect.h, WPN_COL_H / 4, WPN_COL_W / 4 };
								break;
							case Left:
								App->player->action_coll->rect = { (int)App->player->GetPos().x - WPN_COL_W / 4, (int)App->player->GetPos().y + (App->player->link_coll->rect.w / 2) - (WPN_COL_H / 8), WPN_COL_W / 4, WPN_COL_H / 4 };
								break;
							case Right:
								App->player->action_coll->rect = { (int)App->player->GetPos().x + App->player->link_coll->rect.w, (int)App->player->GetPos().y + (App->player->link_coll->rect.w / 2) - (WPN_COL_H / 8), WPN_COL_W / 4, WPN_COL_H / 4 };
								break;

							}
						}

						else
							action_coll->SetPos(FARLANDS.x, FARLANDS.y);
						// !_Logic
					}
					// Graphics
					if (action == false) {
						//Movement or any action that does not stop movement

						if (shield == true && (action_blit == Idle || action_blit == Walk)) //add cases for actions that can be done with or without shield
							action_blit++;
						if (inmortal == true) {
							animations[action_blit][curr_dir].GetCurrentFrame();
							if (ticking_effect > 0) {
								App->render->toDraw(Link_Movement, pos.y - PL_OFFSET_Y + animations[action_blit][curr_dir].GetCurrentFrame().h, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());
								//!_Movement ""
								ticking_effect = 0;
							}
							else {
								ticking_effect++;
							}
						}
						else {
							App->render->toDraw(Link_Movement, pos.y - PL_OFFSET_Y + animations[action_blit][curr_dir].GetCurrentFrame().h, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());
						}
						if (anim_override == true && animations[action_blit][curr_dir].Finished()) {
							anim_override = false;
							dir_override = false;
							animations[action_blit][curr_dir].Reset();
							if (action_blit == Weapon_atk) {
								LOG("SPD %f", pl_speed.x);
								pl_speed.x = (pl_speed.x * PL_SPD_ATK);
								pl_speed.y = (pl_speed.y * PL_SPD_ATK);
							}
							action_blit = Idle;
						}
					}


					//Actions
					else if (action == true) {

						if (animations[action_blit][curr_dir].Finished() && App->input->GetKey(App->input->controls[ACTION]) != KEY_REPEAT) {
							action = false;
							LOG("ACTION = FALSE");
							action_test = false;
							animations[action_blit][curr_dir].Reset();
							App->render->toDraw(Link_Movement, pos.y - PL_OFFSET_Y + animations[Idle][curr_dir].GetCurrentFrame().h, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[Idle][curr_dir].GetCurrentFrame());
						}
						else {
							if (inmortal == true) {
								animations[action_blit][curr_dir].GetCurrentFrame();
								if (ticking_effect > 0) {
									App->render->toDraw(Link_Movement, pos.y - PL_OFFSET_Y + animations[action_blit][curr_dir].GetCurrentFrame().h, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());
									ticking_effect = 0;
								}
								else {
									ticking_effect++;
								}
							}
							else {
								App->render->toDraw(Link_Movement, pos.y - PL_OFFSET_Y + animations[action_blit][curr_dir].GetCurrentFrame().h, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());
							}
							if (animations[action_blit][curr_dir].Finished() && App->input->GetKey(App->input->controls[ACTION]) == KEY_REPEAT)
								animations[action_blit][curr_dir].Reset();
						}

					}
					//!_Actions	
					

					if ((App->input->GetKey(App->input->controls[MENU]) == KEY_DOWN)&&(!action)) {
						if (!App->hud->inv->active) {
							App->hud->inv->active = true;
							App->audio->PlayFx(open_inv_fx);
							App->Pause();
						}
						else {
							App->hud->inv->active = false;
							App->audio->PlayFx(close_inv_fx);
							App->UnPause();
						}
					}

					if (App->player->toTalk != nullptr) {
						if (App->input->GetKey(App->input->controls[ACTION]) == KEY_DOWN) {
							if (toTalk != nullptr) {
								App->hud->dialog->active = true;
								talking = true;
							}
						}
					}

					

					//!_Graphics

					// MODIFY COLLISION -------------------------------------------------
					link_coll->SetPos(pos.x, pos.y);
					mov_coll->SetPos(pos.x + (link_coll->rect.w / 2 - mov_coll->rect.w / 2), pos.y + (link_coll->rect.h / 2 - mov_coll->rect.h / 2));
					/*if ((App->player->curr_life_points <= 2)&&(App->player->curr_life_points!=0)) {
						App->audio->PlayFx(low_hp);
					}*/
					if (App->player->curr_life_points <= 0) {
						//Here he should change the scene to the room scene
						DyingRestart();
						App->audio->PlayFx(die_fx);
					}

					if (App->debug_mode == true) {
						inmortal = true;
					}

					if (inmortal == true) {
						//App->render->DrawQuad({ (int)pos.x - 2, (int)pos.y - 8, 36, 56 }, 255, 255, 255, 80);
						if (App->debug_mode == false)
							if (inmortal_timer.ReadMs() >= inmortal_time)
								inmortal = false;
					}
				}
			}
			if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
				App->scene_manager->toChangeScene((Scene*)App->scene_manager->dungeon_scene);
			}

		}
		else {
			App->render->toDraw(Link_Movement, pos.y - PL_OFFSET_Y + animations[action_blit][curr_dir].GetCurrentFrame().h, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());
			if (App->input->GetKey(App->input->controls[MENU]) == KEY_DOWN) {
				if (App->hud->inv->active) {
					App->hud->inv->active = false;
					App->audio->PlayFx(close_inv_fx);
					App->UnPause();
				}
			}
			if (App->hud->inv->active) {
				if (App->input->GetKey(App->input->controls[UP]) == KEY_DOWN) {
					App->hud->inv->Move_Sel_up();
				}
				else if (App->input->GetKey(App->input->controls[DOWN]) == KEY_DOWN) {
					App->hud->inv->Move_Sel_down();
				}
				else if (App->input->GetKey(App->input->controls[RIGHT]) == KEY_DOWN) {
					App->hud->inv->Move_Sel_forward();
				}
				else if (App->input->GetKey(App->input->controls[LEFT]) == KEY_DOWN) {
					App->hud->inv->Move_Sel_backwards();
				}
			}
			if (App->hud->Minimap->active) {
				if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
					if ((App->scene_manager->dungeon_id != 5) || (App->scene_manager->dungeon_id != 6)) {
						App->hud->Disable_map();
					}
				}
			}
			
		}
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
	if (action_coll != nullptr)
		action_coll->to_delete = true;
	if (mov_coll != nullptr)
		mov_coll->to_delete = true;

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
	if (pl_speed.x < MIN_SPD) {
		pl_speed = { MIN_SPD, MIN_SPD };
	}

}

void j1Player::UpgradePWR(int x)
{
	power += x;

	if (power > MAX_PWR)
		power = MAX_PWR;
	if (power < MIN_PWR)
		power = MIN_PWR;
}

void j1Player::UpgradeHP(int x)
{
	max_life_points += x;
	
	if (max_life_points > MAX_HP)
		max_life_points = MAX_HP;
	if (max_life_points < MIN_HP)
		max_life_points = MIN_HP;

	curr_life_points += x;

}

void j1Player::ChangeWeapon()
{
	//if (change_weapon == true && action_blit != Weapon_atk) {
	//	std::list<Weapon*>::iterator aux_it = std::find(weapons.begin(), weapons.end(), curr_weapon);
	//
	//	switch (change_weapon) {
	//	case Q_Change:
	//		if (aux_it == weapons.begin()) {
	//			aux_it = weapons.end();
	//			aux_it--;
	//		}
	//		else
	//			aux_it--;
	//		break;
	//	case E_Change:
	//		if (++aux_it == weapons.end()) {
	//			aux_it = weapons.begin();
	//		}
	//		break;
	//
	//	}
	//
	//	curr_weapon = aux_it._Ptr->_Myval;
	//
	//	for (int i = 0; i < LastDir; i++) {
	//		animations[Weapon_atk][i] = curr_weapon->anim[i];
	//		animations[Weapon_atk][i] = curr_weapon->anim[i];
	//	}
	//
	//	change_weapon = No_Change;
	//
	//}
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

void j1Player::SetToNewGame()
{
	std::memset(completed_maps, false, N_MAPS);

	keys = 0;
	curr_life_points = 6;
	max_life_points = 6;
	max_life_points = ORIGIN_HP;
	curr_life_points = max_life_points;

	weapons.clear();
	AddWeapon(t_sword);

	curr_weapon = weapons.front();

	rupees = 50;
	power = ORIGIN_PWR;
	pl_speed = { ORIGIN_SPD, ORIGIN_SPD };

	inventory.clear();

	App->SaveGame("save_game.xml");

}

void j1Player::HitPlayer(int dmg)
{
	if (App->player->curr_life_points > 0) {
		if (App->player->inmortal == false && link_coll->active == true) {

			App->audio->PlayFx(App->player->hurt);
			App->player->curr_life_points -= dmg;

			if(dmg > 0)
			App->render->Activate_Shake(2, 1);

			switch (curr_dir) {
			case Up:
				if (App->player->CheckSpace(App->player->GetPos().x, App->player->GetPos().y - App->map->data.tile_height) == 0)
					App->player->MovePos(0, -App->map->data.tile_height);
				break;
			case Down:
				if (App->player->CheckSpace(App->player->GetPos().x, App->player->GetPos().y + App->player->link_coll->rect.h + App->map->data.tile_height) == 0)
					App->player->MovePos(0, App->map->data.tile_height);
				break;
			case Left:
				if (App->player->CheckSpace(App->player->GetPos().x - App->map->data.tile_height, App->player->GetPos().y) == 0)
					App->player->MovePos(-App->map->data.tile_width, 0);
				break;
			case Right:
				if (App->player->CheckSpace(App->player->GetPos().x + App->player->link_coll->rect.w + App->map->data.tile_height, App->player->GetPos().y) == 0)
					App->player->MovePos(App->map->data.tile_width, 0);
				break;
			}

			App->player->PlayerInmortal(HIT_INM_TIME);

			
		}
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
	
	// Hit collision
	//if (link_coll == c1 && link_coll != nullptr && c2->type == COLLIDER_ENEMY && alive == true)
	//{
	//	if (curr_life_points <= 0)
	//		alive = false;
	//
	//	//Activate screen shake
	//	App->render->Activate_Shake(2, 1);
	//	//Add extra particles?
	//	//App->explosion->AddExplosion(App->explosion->Player, position.x - 30, position.y - 30, { 0, 0 }, { 0, 0, 105, 115 }, COLLIDER_EXPLOSION);
	//	//function to restart in the house()
	//}
		//Add extra particles?
		//App->explosion->AddExplosion(App->explosion->Player, position.x - 30, position.y - 30, { 0, 0 }, { 0, 0, 105, 115 }, COLLIDER_EXPLOSION);
		//function to restart in the house()

	if (link_coll == c1 && c2->type == COLLIDER_TO_DUNGEON) {
		if (App->input->GetKey(controls[MOVE_UP]) == KEY_DOWN)
			App->scene_manager->toChangeScene((Scene*)App->scene_manager->dungeon_scene);
	}

}

void j1Player::DyingRestart()
{
	
	App->hud->inv->clear();
	App->hud->inv->selected = nullptr;
	rupees = floor(rupees / 2);

	std::ifstream f("save/save_game.xml");

	if (f.good())
		App->LoadGame("save_game.xml");
	else
		App->player->SetToNewGame();

	//App->player->pos = App->scene_manager->village_scene->pl_start_pos;
//	arrows = 0;

	/*dir_override = true;
	anim_override = true;
	action = true;
	action_blit = Sleep_Wake_up;
	curr_dir = Down;*/

	action_blit = idle;

	//add more features to discuss by the designer
	action = true;
	alive = true;
	curr_dir = Down;
	App->scene_manager->toChangeScene((Scene*)App->scene_manager->main_screen);
}


void j1Player::PlayerInmortal(float time)
{
	inmortal = true;
	inmortal_time = time;
	inmortal_timer.Start();
}

void j1Player::Talk()
{
	//actionState = IDLE;
	App->dialog->text_on_screen->Set_Active_state(true);
	
	if (firstText == true)
	{
		App->dialog->BlitDialog(toTalk->npcId, toTalk->dialogState);
		firstText = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN ||
		App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
		App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN ||
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		if (toTalk != nullptr)
		{
			if (App->dialog->text_on_screen->dialog_state == MID_TEXT)
				App->dialog->text_on_screen->ForcedFinish();

			else
			{
				App->dialog->dialogueStep++;
				if (App->dialog->BlitDialog(toTalk->npcId, toTalk->dialogState) == false)
				{
					//playerState = ACTIVE;
					App->dialog->text_on_screen->Set_Active_state(false);
					if (toTalk->dialogState == 0)
					{
						toTalk->dialogState++;
					}
					App->dialog->dialogueStep = 0;
					int test = toTalk->dialogState;
					firstText = true;
					toTalk = nullptr;
				}
			}
		}
	}
}

int j1Player::CheckSpace(float new_x, float new_y)
{
	int ret = true;

	// TileCheck
	if (App->map->active == true) {
		ret = App->map->TileCheck(new_x, new_y);
		if(ret != 1 && action_blit == Dash)
		ret = App->map->TileCheck(new_x + mov_coll->rect.w, new_y + mov_coll->rect.h);
	}
		if (ret != 1) {
			SDL_Rect r = mov_coll->rect;
			r.x = new_x;
			r.y = new_y;

			Room* c_r = App->scene_manager->GetCurrentScene()->GetRoom(room.x, room.y);

			// Enemy Check
			if (inmortal == false) {
				for (std::list<Enemy*>::iterator it = c_r->enemies.begin(); it != c_r->enemies.end(); it++) {
					if (CheckIntersec(r, it._Ptr->_Myval->HitBox->rect) == true) {
						ret = 1;
						break;
					}
				}
			}
			// Block Check
			if (ret != false) {
				for (std::list<Block*>::iterator it = c_r->blocks.begin(); it != c_r->blocks.end(); it++) {
					if (CheckIntersec(r, it._Ptr->_Myval->HitBox->rect) == true) {
						ret = 1;
						break;
					}
				}
			}
			if (ret != false) {
				for (std::list<Npc*>::iterator it = c_r->npcs.begin(); it != c_r->npcs.end(); it++) {
					if (CheckIntersec(r, it._Ptr->_Myval->HitBox->rect) == true) {
						ret = 1;
						break;
					}
				}
			}


		}
	return ret;
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

		
void j1Player::Movement()
{
	//Movement
	if(App->player->alive){
		if (App->input->GetKey(App->input->controls[MOVE_UP]) && App->input->GetKey(App->input->controls[MOVE_LEFT])) {
			if (CheckSpace(pos.x - pl_speed.x, pos.y - pl_speed.y) == 0) //change dir
			{
				walk_dir = Up_L;
				pos.y -= pl_speed.y * sqrt(2) / 2;
				pos.x -= pl_speed.x * sqrt(2) / 2;
			}
			if (anim_override == false)
				action_blit = Walk;
		}
		else if (App->input->GetKey(App->input->controls[MOVE_LEFT]) && App->input->GetKey(App->input->controls[MOVE_DOWN])) {
			if (CheckSpace(pos.x - pl_speed.x, (pos.y + 34) + pl_speed.y) == 0) //change dir
			{
				walk_dir = Down_L;
				pos.y += pl_speed.y * sqrt(2) / 2;
				pos.x -= pl_speed.x * sqrt(2) / 2;

			}
			if (anim_override == false)
				action_blit = Walk;
		}
		else if (App->input->GetKey(App->input->controls[MOVE_DOWN]) && App->input->GetKey(App->input->controls[MOVE_RIGHT])) {
			if (CheckSpace((pos.x + 32) + pl_speed.x, (pos.y + 32) + pl_speed.y) == 0)//change dir
			{
				walk_dir = Down_R;
				pos.y += pl_speed.y * sqrt(2) / 2;
				pos.x += pl_speed.x * sqrt(2) / 2;
			}
			if (anim_override == false)
				action_blit = Walk;

		}
		else if (App->input->GetKey(App->input->controls[MOVE_RIGHT]) && App->input->GetKey(App->input->controls[MOVE_UP])) {
			if (CheckSpace((pos.x + 32) + pl_speed.x, pos.y - pl_speed.y) == 0)//change dir
			{
				walk_dir = Up_R;
				pos.y -= pl_speed.y * sqrt(2) / 2;
				pos.x += pl_speed.x * sqrt(2) / 2;
			}
			if (anim_override == false)
				action_blit = Walk;
		}
		else if (App->input->GetKey(App->input->controls[MOVE_UP])) {
			if (CheckSpace(pos.x, pos.y - pl_speed.y) == 0)
			{
				pos.y -= pl_speed.y;
			}
			if (anim_override == false)
				action_blit = Walk;
			if (dir_override == false) {
				curr_dir = Up;
				walk_dir = Up;
			}

		}
		else if (App->input->GetKey(App->input->controls[MOVE_LEFT])) {
			if (CheckSpace(pos.x - pl_speed.x, pos.y) == 0)
			{
				pos.x -= pl_speed.x;
			}
			if (anim_override == false)
				action_blit = Walk;
			if (dir_override == false) {
				curr_dir = Left;
				walk_dir = Left;
			}
		}
		else if (App->input->GetKey(App->input->controls[MOVE_DOWN]))
		{
			if (CheckSpace(pos.x, (pos.y+32) + pl_speed.y) == 0)
			{
				pos.y += pl_speed.y;
			}
			if (anim_override == false)
				action_blit = Walk;
			if (dir_override == false) {
				curr_dir = Down;
				walk_dir = Down;
			}
		}
		else if (App->input->GetKey(App->input->controls[MOVE_RIGHT]))
		{
			if (CheckSpace((pos.x + 32) + pl_speed.x, pos.y) == 0)
			{
				pos.x += pl_speed.x;
			}	
			if (anim_override == false)
				action_blit = Walk;
			if (dir_override == false) {
				curr_dir = Right;
				walk_dir = Right;
			}
		}
		else {
			if (anim_override == false)
				action_blit = Idle;
		}

	}
		last_pos = pos;
}

void j1Player::Slash_()
{
	uint a_time = 0;
	if (curr_weapon->subtype == weapon_bow)
		a_time = 500;
	else
		a_time = 0;

	if (App->player->alive) {
		
		if (!App->hud->inv->active)
		{
			if (anim_override == false)
			{
				if (w_a_timer.Read() > a_time) {
					if (App->input->GetKey(App->input->controls[UP])) {
						curr_dir = Up;
						action_blit = Weapon_atk;
						if (curr_weapon != nullptr)
							curr_weapon->Attack();
						App->audio->PlayFx(sword_fx);
						dir_override = true;
						anim_override = true;
						pl_speed.x = pl_speed.x / PL_SPD_ATK;
						pl_speed.y = pl_speed.y / PL_SPD_ATK;
						w_a_timer.SetFlag(false);

				}
				else if (App->input->GetKey(App->input->controls[DOWN])) {
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
					w_a_timer.SetFlag(false);

				}
				else if (App->input->GetKey(App->input->controls[RIGHT])) {
					curr_dir = Right;
					action_blit = Weapon_atk;
					if (curr_weapon != nullptr)
						curr_weapon->Attack();
					App->audio->PlayFx(sword_fx);
					dir_override = true;
					anim_override = true;
					pl_speed.x = pl_speed.x / PL_SPD_ATK;
					pl_speed.y = pl_speed.y / PL_SPD_ATK;
					w_a_timer.SetFlag(false);

				}
				else if (App->input->GetKey(App->input->controls[LEFT])) {
					curr_dir = Left;
					action_blit = Weapon_atk;
					if (curr_weapon != nullptr)
						curr_weapon->Attack();
					App->audio->PlayFx(sword_fx);
					dir_override = true;
					anim_override = true;
					pl_speed.x = pl_speed.x / PL_SPD_ATK;
					pl_speed.y = pl_speed.y / PL_SPD_ATK;
					w_a_timer.SetFlag(false);
				}
			}
			}
		}
		else
		{
			if (App->input->GetKey(App->input->controls[UP]) == KEY_DOWN) {
				App->hud->inv->Move_Sel_up();
			}
			else if (App->input->GetKey(App->input->controls[DOWN]) == KEY_DOWN) {
				App->hud->inv->Move_Sel_down();
			}
			else if (App->input->GetKey(App->input->controls[RIGHT]) == KEY_DOWN) {
				App->hud->inv->Move_Sel_forward();
			}
			else if (App->input->GetKey(App->input->controls[LEFT]) == KEY_DOWN) {
				App->hud->inv->Move_Sel_backwards();
			}
		}
	}
}


bool j1Player::LoadPlayer(int id,bool new_game)
{
	pugi::xml_document	data_file;
	pugi::xml_node		data;
	data = LoadXML(data_file,new_game);
	//keys
	uint n_k = 0;
	for (pugi::xml_node node_k = data.child("keys"); node_k; node_k = node_k.next_sibling("keys")) {
			completed_maps[n_k++] = data.child("keys").attribute("completed").as_bool(false);
	}

	keys = data.child("n_keys").attribute("n").as_int(0);

	//map1_comp = data.child("keys").attribute("m1").as_bool(false);
	//map2_comp = data.child("keys").attribute("m2").as_bool(false);
	//map3_comp = data.child("keys").attribute("m3").as_bool(false);
	//map4_comp = data.child("keys").attribute("m4").as_bool(false);
	//map5_comp = data.child("keys").attribute("m5").as_bool(false);

	//hp
	curr_life_points = data.child("hp").attribute("max").as_int();
	max_life_points = data.child("hp").attribute("max").as_int();
	///weapons
	std::string curr_weapon = data.child("weapons").attribute("curr_weapon").as_string();
	if (curr_weapon.c_str() == "t_sword")
		if (data.child("weapons").attribute("sword").as_bool())
			AddWeapon(t_sword);
	if (data.child("weapons").attribute("bow").as_bool())
		AddWeapon(t_bow);

	//items info
	pugi::xml_node items = data.child("items");
	if (items.attribute("power_gauntlet").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(power_gauntlet);
		aux->PassToInventory();
	}
	if (items.attribute("pegasus_boots").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(pegasus_boots);
		aux->PassToInventory();
	}
	if (items.attribute("heart_container").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(heart_container);
		aux->PassToInventory();
	}
	if (items.attribute("gold_gauntlet").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(gold_gauntlet);
		aux->PassToInventory();
	}
	if (items.attribute("wind_cape").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(wind_cape);
		aux->PassToInventory();
	}
	if (items.attribute("magic_hammer").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(magic_hammer);
		aux->PassToInventory();
	}
	if (items.attribute("small_shield").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(small_shield);
		aux->PassToInventory();
	}
	if (items.attribute("vanguard_emblem").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(vanguard_emblem);
		aux->PassToInventory();
	}
	if (items.attribute("magic_sphere").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(magic_sphere);
		aux->PassToInventory();
	}	if (items.attribute("magic_mirror").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(magic_mirror);
		aux->PassToInventory();
	}	if (items.attribute("golden_shield").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(golden_shield);
		aux->PassToInventory();
	}	if (items.attribute("mysterious_dust").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(mysterious_dust);
		aux->PassToInventory();
	}	if (items.attribute("odd_mushroom").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(odd_mushroom);
		aux->PassToInventory();
	}	if (items.attribute("bag_of_rupees").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(bag_of_rupees);
		aux->PassToInventory();
	}	if (items.attribute("icon_of_power").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(icon_of_power);
		aux->PassToInventory();
	}	if (items.attribute("icon_of_wisdom").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(icon_of_wisdom);
		aux->PassToInventory();
	}	if (items.attribute("icon_of_valor").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(icon_of_valor);
		aux->PassToInventory();
	}	if (items.attribute("boss_key").as_bool() == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(boss_key);
		aux->PassToInventory();
	}
	//dungeon situation info
	if (data.child("dungeon").attribute("in").as_bool(false) == true)
		App->scene_manager->SetCurrentScene((Scene*)App->scene_manager->dungeon_scene);

	return true;

}



pugi::xml_node j1Player::LoadXML(pugi::xml_document & config_file,bool new_game) const
{
	pugi::xml_node ret;
	int size = 0;
	pugi::xml_parse_result result;
	char* buf = nullptr;
	if(new_game == false)
		size = App->fs->Load("save_game.xml", &buf);
	else
		size = App->fs->Load("new_game.xml", &buf);

	if (size != 0 && buf != nullptr)
		result = config_file.load_buffer(buf, size);
	RELEASE(buf);

	if (result == NULL)
		LOG("Could not load player XML. pugi error: %s \n ---Offset: %d", result.description(), result.offset);


	return ret;
}

// Save Game State
bool j1Player::Save(pugi::xml_node& data) const
{
	//keys
	LOG("PLAYER SAVING");
	for (int i = 0; i < N_MAPS; i++) {
		pugi::xml_node keys = data.append_child("keys");
		keys.append_attribute("id") = i;
		keys.append_attribute("completed") = completed_maps[i];
	}

	pugi::xml_node n_keys = data.append_child("n_keys");
	n_keys.append_attribute("n") = keys;

	//hp
	pugi::xml_node hp = data.append_child("hp");
		hp.append_attribute("curr") = curr_life_points;
		hp.append_attribute("max") = max_life_points;
	pugi::xml_node weap = data.append_child("weapons");

	weap.append_attribute("curr_weapon") = curr_weapon->subtype;

	//rupees
	pugi::xml_node rupees = data.append_child("rupees");
	rupees.append_attribute("n") = rupees;
	//stats
	pugi::xml_node stats = data.append_child("stats");
	stats.append_attribute("power") = power;
	stats.append_attribute("speed") = pl_speed.x;
	//items
	pugi::xml_node items = data.append_child("items");
	for (std::list<Item*>::const_iterator it = inventory.cbegin(); it != inventory.cend(); it++) 
	{
		switch (it._Ptr->_Myval->type)
		{
		case power_gauntlet:
			items.append_attribute("power_gauntlet") = true;
			break;
		case pegasus_boots:   
			items.append_attribute("pegasus_boots") = true;
			break;
		case heart_container:
			items.append_attribute("pegasus_boots") = true;
			break;
		case gold_gauntlet:
			items.append_attribute("pegasus_boots") = true;
			break;
		case wind_cape:
			items.append_attribute("pegasus_boots") = true;
			break;
		case magic_hammer:
			items.append_attribute("magic_hammer") = true;
			break;
		case small_shield:
			items.append_attribute("small_shield") = true;
			break;
		case vanguard_emblem:
			items.append_attribute("vanguard_emblem") = true;
			break;
		case magic_sphere:
			items.append_attribute("magic_sphere") = true;
			break;
		case magic_mirror:
			items.append_attribute("magic_mirror") = true;
			break;
		case golden_shield:			
			items.append_attribute("golden_shield") = true;
			break;
		case mysterious_dust:
			items.append_attribute("mysterious_dust") = true;
			break;
		case odd_mushroom:
			items.append_attribute("odd_mushroom") = true;
			break;
		case icon_of_power:
			items.append_attribute("icon_of_power") = true;
			break;
		case  icon_of_wisdom:
			items.append_attribute("icon_of_wisdom") = true;
			break;
		case icon_of_valor:
			items.append_attribute("icon_of_valor") = true;
			break;
		}
	}                                                                                   
	return true;
}

bool j1Player::Load(pugi::xml_node & data)
{

	pugi::xml_node hp = data.child("hp");
	curr_life_points = hp.attribute("curr").as_int(6);
	max_life_points = hp.attribute("max").as_int(6);

	pugi::xml_node weap = data.child("weapons");

	weapons.clear();
	AddWeapon(weap.attribute("curr_weapon").as_int(t_sword));

	std::memset(completed_maps, false, N_MAPS);

	for (pugi::xml_node node_keys = data.child("keys"); node_keys; node_keys = node_keys.next_sibling("keys")) {
		completed_maps[node_keys.attribute("id").as_int(NULL)] = node_keys.attribute("completed").as_bool(false);
	}

	keys = data.child("n_keys").attribute("n").as_int(0);

	rupees = data.child("rupees").attribute("n").as_int(50);

	pugi::xml_node items = data.child("items");

	inventory.clear();

	if (items.attribute("power_gauntlet").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(power_gauntlet);
		aux->PassToInventory();
	}
	if (items.attribute("pegasus_boots").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(pegasus_boots);
		aux->PassToInventory();
	}
	if (items.attribute("heart_container").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(heart_container);
		aux->PassToInventory();
	}
	if (items.attribute("gold_gauntlet").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(gold_gauntlet);
		aux->PassToInventory();
	}
	if (items.attribute("wind_cape").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(wind_cape);
		aux->PassToInventory();
	}
	if (items.attribute("magic_hammer").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(magic_hammer);
		aux->PassToInventory();
	}
	if (items.attribute("small_shield").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(small_shield);
		aux->PassToInventory();
	}
	if (items.attribute("vanguard_emblem").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(vanguard_emblem);
		aux->PassToInventory();
	}
	if (items.attribute("magic_sphere").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(magic_sphere);
		aux->PassToInventory();
	}	if (items.attribute("magic_mirror").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(magic_mirror);
		aux->PassToInventory();
	}	if (items.attribute("golden_shield").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(golden_shield);
		aux->PassToInventory();
	}	if (items.attribute("mysterious_dust").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(mysterious_dust);
		aux->PassToInventory();
	}	if (items.attribute("odd_mushroom").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(odd_mushroom);
		aux->PassToInventory();
	}	if (items.attribute("bag_of_rupees").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(bag_of_rupees);
		aux->PassToInventory();
	}	if (items.attribute("icon_of_power").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(icon_of_power);
		aux->PassToInventory();
	}	if (items.attribute("icon_of_wisdom").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(icon_of_wisdom);
		aux->PassToInventory();
	}	if (items.attribute("icon_of_valor").as_bool(false) == true)
	{
		Item* aux = (Item*)App->entitymanager->CreateItem(icon_of_valor);
		aux->PassToInventory();
	}

	return true;
}
