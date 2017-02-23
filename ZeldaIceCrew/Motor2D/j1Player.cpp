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

	// Setting Up all SDL_Rects
	//When you create rects, always maintain the Highest Y value for the whole set of animations, and keep the same biggest Height, that way the animation is done perfect and only needs to move where it is blitted

	{
		sprites[Idle][Up][0].x = 118;
		sprites[Idle][Up][0].y = 62;
		sprites[Idle][Up][0].w = 32;
		sprites[Idle][Up][0].h = 44;

		sprites[Idle][Down][0].x = 118;
		sprites[Idle][Down][0].y = 8;
		sprites[Idle][Down][0].w = 32;
		sprites[Idle][Down][0].h = 44;

		sprites[Idle][Left][0].x = 118;
		sprites[Idle][Left][0].y = 163;
		sprites[Idle][Left][0].w = 32;
		sprites[Idle][Left][0].h = 44;

		sprites[Idle][Right][0].x = 118;
		sprites[Idle][Right][0].y = 112;
		sprites[Idle][Right][0].w = 32;
		sprites[Idle][Right][0].h = 44;
	}

	//Walk
	{
		sprites[Walk][Up][0] = { 4, 58, 32, 48 };
		sprites[Walk][Up][1] = { 42, 58, 32, 48 };
		sprites[Walk][Up][2] = { 80 , 58, 32, 48 };
		sprites[Walk][Up][3] = { 118, 58, 32, 48 };
		sprites[Walk][Up][4] = { 156, 58, 32, 48 };
		sprites[Walk][Up][5] = { 194, 58, 32, 48 };
		sprites[Walk][Up][6] = { 232, 58, 32, 48 };

		sprites[Walk][Down][0] = { 4  ,  4, 32, 48 };
		sprites[Walk][Down][1] = { 42 , 4, 32, 48 };
		sprites[Walk][Down][2] = { 80 , 4, 32, 48 };
		sprites[Walk][Down][3] = { 118, 4, 32, 48 };
		sprites[Walk][Down][4] = { 156, 4, 32, 48 };
		sprites[Walk][Down][5] = { 194, 4, 32, 48 };
		sprites[Walk][Down][6] = { 232, 4, 32, 48 };

		sprites[Walk][Right][0] = { 4  ,110,32,48 };
		sprites[Walk][Right][1] = { 42 ,110,32,48 };
		sprites[Walk][Right][2] = { 80 ,110,32,48 };
		sprites[Walk][Right][3] = { 118,110,32,48 };
		sprites[Walk][Right][4] = { 156,110,32,46 };
		sprites[Walk][Right][5] = { 194,110,32,48 };
		sprites[Walk][Right][6] = { 232,110,32,48 };

		sprites[Walk][Left][0] = { 4  ,162,32,48 };
		sprites[Walk][Left][1] = { 42 ,162,32,48 };
		sprites[Walk][Left][2] = { 80 ,162,32,48 };
		sprites[Walk][Left][3] = { 118,162,32,48 };
		sprites[Walk][Left][4] = { 156,162,32,48 };
		sprites[Walk][Left][5] = { 194,162,32,48 };
		sprites[Walk][Left][6] = { 234,162,34,48 };
	}

	//Walk with blue Shield

	//Pick-up Object
	//y coordinate for object depends on animation, all x2 because size
	//Pick up left/right [1.y = +7 / 2.y = +6  / 3.y = +6 / 4.y = +6 / 5.y = +10 / 6.y = +10 ]
	//Pick up top [1.y = +14 / 2.y = +15  / 3.y = +13 / 4.y = +13 / 5.y = +16 / 6.y = +10 ]
	//Pick up down [1.y = +0 / 2.y = +0  / 3.y = +1 / 4.y = +10 / 5.y = +12 / 6.y = +10 ]
	// x for top and down is link.x + link.w/2
	// for right left [1.x = +10 / 2.x +16/ 3.x = +17 / 4.x = +17 / 5.x = +5 / 6.x = +2 ]
	{
		sprites[Pickup][Down][0] = { 834, 6, 32, 46 };
		sprites[Pickup][Down][1] = { 880, 6, 60, 46 };	//x - 14
		sprites[Pickup][Down][2] = { 946, 6, 68, 46 };	//x - 18
		sprites[Pickup][Down][3] = { 1020, 6, 68, 46 };	//print with x - 18
		sprites[Pickup][Down][4] = { 1098, 6, 32, 46 };
		sprites[Pickup][Down][5] = { 1148, 6, 32, 46 };

		sprites[Pickup][Up][0] = { 834, 60, 32, 46 };
		sprites[Pickup][Up][1] = { 880, 60, 60, 46 };	//x - 12
		sprites[Pickup][Up][2] = { 946, 60, 68, 46 };	//x - 16
		sprites[Pickup][Up][3] = { 1020, 60, 68, 46 };	//x - 16
		sprites[Pickup][Up][4] = { 1098, 60, 32, 46 };
		sprites[Pickup][Up][5] = { 1148, 60, 32, 46 };

		//Remember Left animation is invers of right, so have to render taking into account new W and it starts on left
		sprites[Pickup][Left][0] = { 1098, 164, 50, 46 };
		sprites[Pickup][Left][1] = { 1020, 164, 62, 46 };	//x - 48
		sprites[Pickup][Left][2] = { 946, 164, 70, 46 };	//x - 44 from right
		sprites[Pickup][Left][3] = { 880, 164, 62, 46 };	//x - 44 from right
		sprites[Pickup][Left][4] = { 819, 164, 50, 46 };
		sprites[Pickup][Left][5] = { 1148, 164, 34, 46 };

		sprites[Pickup][Right][0] = { 819, 114, 50, 46 };
		sprites[Pickup][Right][1] = { 882, 114, 62, 46 };	//x - 14
		sprites[Pickup][Right][2] = { 946, 114, 70, 46 };	//x - 18
		sprites[Pickup][Right][3] = { 1020, 114, 62, 46 };	//x - 18
		sprites[Pickup][Right][4] = { 1098, 114, 40, 46 };
		sprites[Pickup][Right][5] = { 1148, 114, 34, 46 };
	}
	//Push Object
	{
		sprites[Push][Down][2] = { 1276, 6, 32, 48 };
		sprites[Push][Down][1] = { 1238, 6, 32, 48 };
		sprites[Push][Down][0] = { 1198, 6, 32, 48 };

		sprites[Push][Up][2] = { 1276, 60, 32, 48 };
		sprites[Push][Up][1] = { 1238, 60, 32, 48 };
		sprites[Push][Up][0] = { 1198, 60, 32, 48 };

		sprites[Push][Left][2] = { 1276, 162, 32, 50 };
		sprites[Push][Left][1] = { 1238, 162, 32, 50 };
		sprites[Push][Left][0] = { 1198, 162, 32, 50 };
		sprites[Push][Left][3] = { 1318, 162, 32, 50 };

		sprites[Push][Right][2] = { 1276, 110, 32, 50 };
		sprites[Push][Right][1] = { 1238, 110, 32, 50 };
		sprites[Push][Right][0] = { 1198, 110, 32, 50 };
		sprites[Push][Right][3] = { 1318, 110, 32, 50 };


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
	}

		// Direction/Atk
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

		// Actions
	{

		if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
			//for now perform an action to see animation
			//requires a detector for usage: villager = talk, bush or bomb or pot... = pickup and then throw, lever or rock = pull or push...

		}

	}

	// !_Logic

	// Graphics
	if (App->input->GetKey(SDL_SCANCODE_W)) {																// Walk UP
		App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Walk][curr_dir].GetCurrentFrame());
	}
	else if (App->input->GetKey(SDL_SCANCODE_A)) {																	// Walk Left
		App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Walk][curr_dir].GetCurrentFrame());
	}
	else if (App->input->GetKey(SDL_SCANCODE_S)) {																	// Walk Down
		App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Walk][curr_dir].GetCurrentFrame());
	}
	else if (App->input->GetKey(SDL_SCANCODE_D)) {																	// Walk Right
		App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Walk][curr_dir].GetCurrentFrame());
	}
	else if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
		//On frames 1 and 2&3 there is a displace required of pos.x in order to blit correctly the animation, numbers above
		//How to do an if statement depending on frame of animation?
		//This animation has to trigger completely, can't be because of key repeat, but of key press
		//animations depend on action taken
		//App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Pickup][curr_dir].GetCurrentFrame());
		App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Push][curr_dir].GetCurrentFrame());
		//App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Pull][curr_dir].GetCurrentFrame());
	}


	else
		App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Idle][curr_dir].GetCurrentFrame());			// Idle

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
