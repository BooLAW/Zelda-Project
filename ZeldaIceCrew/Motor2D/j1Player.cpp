#include "j1Player.h"
#include "j1Input.h"

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

	//Pick-up Object
	//y coordinate for object depends on animation

	{
		sprites[Pickup][Down][0] = { link_x*12, link_y, link_width, link_height };
		sprites[Pickup][Down][1] = { link_x*13, link_y, link_width, link_height };
		sprites[Pickup][Down][2] = { link_x*14, link_y, link_width, link_height };
		sprites[Pickup][Down][3] = { link_x*15, link_y, link_width, link_height };
		sprites[Pickup][Down][4] = { link_x*16, link_y, link_width, link_height };
		sprites[Pickup][Down][5] = { link_x*17, link_y, link_width, link_height };

		sprites[Pickup][Up][0] = { link_x*12, link_y*2, link_width, link_height };
		sprites[Pickup][Up][1] = { link_x*13, link_y*2, link_width, link_height };
		sprites[Pickup][Up][2] = { link_x*14, link_y*2, link_width, link_height };
		sprites[Pickup][Up][3] = { link_x*15, link_y*2, link_width, link_height };	
		sprites[Pickup][Up][4] = { link_x*16, link_y*2, link_width, link_height };
		sprites[Pickup][Up][5] = { link_x*17, link_y*2, link_width, link_height };

		sprites[Pickup][Left][0] = { link_x*16, link_y*4, link_width, link_height };
		sprites[Pickup][Left][1] = { link_x*15, link_y*4, link_width, link_height };
		sprites[Pickup][Left][2] = { link_x*14, link_y*4, link_width, link_height };
		sprites[Pickup][Left][3] = { link_x*13, link_y*4, link_width, link_height };
		sprites[Pickup][Left][4] = { link_x*12, link_y*4, link_width, link_height };
		sprites[Pickup][Left][5] = { link_x*17, link_y*4, link_width, link_height };

		sprites[Pickup][Right][0] = { link_x*12, link_y*3, link_width, link_height };
		sprites[Pickup][Right][1] = { link_x*13, link_y*3, link_width, link_height };	
		sprites[Pickup][Right][2] = { link_x*14, link_y*3, link_width, link_height };	
		sprites[Pickup][Right][3] = { link_x*15, link_y*3, link_width, link_height };	
		sprites[Pickup][Right][4] = { link_x*16, link_y*3, link_width, link_height };
		sprites[Pickup][Right][5] = { link_x*17, link_y*3, link_width, link_height };
	}
	//Push Object
	{
		sprites[Push][Down][2] = { link_x*18, 6, link_width, link_height };
		sprites[Push][Down][1] = { link_x*19, 6, link_width, link_height };
		sprites[Push][Down][0] = { link_x*20, 6, link_width, link_height };

		sprites[Push][Up][2] = { link_x*18, link_y*2, link_width, link_height };
		sprites[Push][Up][1] = { link_x*19, link_y*2, link_width, link_height };
		sprites[Push][Up][0] = { link_x*20, link_y*2, link_width, link_height };

		sprites[Push][Left][2] = { link_x*18, 162, link_width, link_height };
		sprites[Push][Left][1] = { link_x*19, 162, link_width, link_height };
		sprites[Push][Left][0] = { link_x*20, 162, link_width, link_height };
		sprites[Push][Left][3] = { link_x*21, 162, link_width, link_height };

		sprites[Push][Right][2] = { link_x*18, link_y*3, link_width, link_height };
		sprites[Push][Right][1] = { link_x*19, link_y*3, link_width, link_height };
		sprites[Push][Right][0] = { link_x*20, link_y*3, link_width, link_height };
		sprites[Push][Right][3] = { link_x*21, link_y*3, link_width, link_height };


	}
	//Pull Object
	{}

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

	animations[Walk][Down].PushBack(sprites[Idle][Down][0]);
	animations[Walk][Left].PushBack(sprites[Idle][Left][0]);
	animations[Walk][Right].PushBack(sprites[Idle][Right][0]);

	// animations speed settup
	//This was bad because not all animations are played back in the same speed, every animation requires a speed setup
	{
		for (int n_dir = Direction::FirstDir; n_dir < Direction::LastDir; n_dir++) {
			animations[Pickup][n_dir].speed = 0.2f;
		}
	}


	// !_Animations

	// Variable Settup

	pos.x = 0;
	pos.y = 0;

	pl_speed.x = 2.5;
	pl_speed.y = 2.5;

	curr_dir = Down;

	// !_Variables

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;

	// Logic
	if (action == false) {
		//Movement
		{
			if (App->input->GetKey(SDL_SCANCODE_W) && App->input->GetKey(SDL_SCANCODE_A)) {
				pos.y -= pl_speed.y * sqrt(2) / 2;
				pos.x -= pl_speed.x * sqrt(2) / 2;
			}
			else if (App->input->GetKey(SDL_SCANCODE_A) && App->input->GetKey(SDL_SCANCODE_S)) {
				pos.y += pl_speed.y * sqrt(2) / 2;
				pos.x -= pl_speed.x * sqrt(2) / 2;
			}
			else if (App->input->GetKey(SDL_SCANCODE_S) && App->input->GetKey(SDL_SCANCODE_D)) {
				pos.y += pl_speed.y * sqrt(2) / 2;
				pos.x += pl_speed.x * sqrt(2) / 2;
			}
			else if (App->input->GetKey(SDL_SCANCODE_D) && App->input->GetKey(SDL_SCANCODE_W)) {
				pos.y -= pl_speed.y * sqrt(2) / 2;
				pos.x += pl_speed.x * sqrt(2) / 2;
			}
			else if (App->input->GetKey(SDL_SCANCODE_W)) {
				pos.y -= pl_speed.y;
				curr_dir = Up;

			}
			else if (App->input->GetKey(SDL_SCANCODE_A)) {
				pos.x -= pl_speed.x;
				curr_dir = Left;
			}
			else if (App->input->GetKey(SDL_SCANCODE_S)) {
				pos.y += pl_speed.y;
				curr_dir = Down;
			}
			else if (App->input->GetKey(SDL_SCANCODE_D)) {
				pos.x += pl_speed.x;
				curr_dir = Right;
			}


			// Direction/Atk
			// This inherently bad, you are ignoring 6 more buttons (X Y L R SELECT START)
			{

				if (App->input->GetKey(SDL_SCANCODE_UP)) {
					curr_dir = Up;
				}
				else if (App->input->GetKey(SDL_SCANCODE_DOWN)) {
					curr_dir = Down;
				}
				else if (App->input->GetKey(SDL_SCANCODE_RIGHT)) {
					curr_dir = Right;
				}
				else if (App->input->GetKey(SDL_SCANCODE_LEFT)) {
					curr_dir = Left;
				}

			}
		}
	}

			// Actions
	{

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			//for now perform an action to see animation
			//requires a detector for usage: villager = talk, bush or bomb or pot... = pickup and then throw, lever or rock = pull or push...
			action = true;
			action_blit = Pickup;
		}

	}

			// !_Logic

			// Graphics
		if (action == false){
			//Movement
			if (App->input->GetKey(SDL_SCANCODE_W)) {																// Walk UP
				App->render->Blit(Link_Movement, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[Walk][curr_dir].GetCurrentFrame());
			}
			else if (App->input->GetKey(SDL_SCANCODE_A)) {																	// Walk Left
				App->render->Blit(Link_Movement, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[Walk][curr_dir].GetCurrentFrame());
			}
			else if (App->input->GetKey(SDL_SCANCODE_S)) {																	// Walk Down
				App->render->Blit(Link_Movement, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[Walk][curr_dir].GetCurrentFrame());
			}
			else if (App->input->GetKey(SDL_SCANCODE_D)) {																	// Walk Right
				App->render->Blit(Link_Movement, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[Walk][curr_dir].GetCurrentFrame());
			}
			//!_Movement


			else
				App->render->Blit(Link_Movement, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[Idle][curr_dir].GetCurrentFrame());			// Idle
			
		}
	

	//Actions
		else if (action == true) {
			App->render->Blit(Link_Movement, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());
			
			if (animations[action_blit][curr_dir].Finished() && App->input->GetKey(SDL_SCANCODE_SPACE) != KEY_REPEAT) {
				action = false;
				animations[action_blit][curr_dir].Reset();
			}
		}
	//!_Actions																													
	
	//!_Graphics

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


	return ret;
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
