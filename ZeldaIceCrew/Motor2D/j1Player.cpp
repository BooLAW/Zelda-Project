#include "j1Player.h"
#include "j1Input.h"
#include "j1Window.h"

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

	pos.x = 0;
	pos.y = 0;

	return ret;
}

bool j1Player::Start()
{
	bool ret = true;
	LOG("Player Start");

	// Setting Up all SDL_Rects

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
		sprites[Walk][Up][0] = { 4  ,  58,  32,48 };
		sprites[Walk][Up][1] = { 42 , 60, 32,46 };
		sprites[Walk][Up][2] = { 80 , 62, 32,44 };
		sprites[Walk][Up][3] = { 118, 62, 32,44 };
		sprites[Walk][Up][4] = { 156, 62, 32,44 };
		sprites[Walk][Up][5] = { 194, 60, 32,46 };
		sprites[Walk][Up][6] = { 232,57,32,48 };

		sprites[Walk][Down][0] = { 4  ,  4, 32, 48 };
		sprites[Walk][Down][1] = { 42 , 6, 32, 48 };
		sprites[Walk][Down][2] = { 80 , 8, 32, 44 };
		sprites[Walk][Down][3] = { 118, 8, 32, 44 };
		sprites[Walk][Down][4] = { 156, 8, 32, 44 };
		sprites[Walk][Down][5] = { 194, 6, 32, 46 };
		sprites[Walk][Down][6] = { 232, 6, 32, 48 };

		sprites[Walk][Right][0] = { 4  ,112,32,46 };
		sprites[Walk][Right][1] = { 42 ,110,32,46 };
		sprites[Walk][Right][2] = { 80 ,110,32,48 };
		sprites[Walk][Right][3] = { 118,112,32,48 };
		sprites[Walk][Right][4] = { 156,110,32,46 };
		sprites[Walk][Right][5] = { 194,110,32,48 };
		sprites[Walk][Right][6] = { 232,112,32,48 };

		sprites[Walk][Left][0] = { 4  ,164,32,46 };
		sprites[Walk][Left][1] = { 42 ,162,32,48 };
		sprites[Walk][Left][2] = { 80 ,162,32,48 };
		sprites[Walk][Left][3] = { 118,164,32,46 };
		sprites[Walk][Left][4] = { 156,162,32,48 };
		sprites[Walk][Left][5] = { 194,162,32,48 };
		sprites[Walk][Left][6] = { 232,164,34,46 };
	}

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
			animations[Walk][Up].speed = 0.1f;
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
			animations[Walk][Down].speed = 0.1f;
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
			animations[Walk][Left].speed = 0.1f;
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
			animations[Walk][Right].speed = 0.1f;
		}

	}

	animations[Walk][Down].PushBack(sprites[Idle][Down][0]);
	animations[Walk][Left].PushBack(sprites[Idle][Left][0]);
	animations[Walk][Right].PushBack(sprites[Idle][Right][0]);

		// animations speed settup
	for (int n_sprit = Sprites::__FIRST; n_sprit < Sprites::__LAST; n_sprit++) {
		for (int n_dir = Direction::FirstDir; n_dir < Direction::LastDir; n_dir++) {
			animations[n_sprit][n_dir].speed = 0.1f;
		}
	}

	// !_Animations

	// Variable Settup

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
	else if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;

	// !_Logic

	// Graphics
	if (App->input->GetKey(SDL_SCANCODE_W))																					// Walk UP
		App->render->Blit(Link_Movement, pos.x, pos.y - PL_OFFSET, &animations[Walk][curr_dir].GetCurrentFrame());
	else
	if (App->input->GetKey(SDL_SCANCODE_A))																					// Walk Left
		App->render->Blit(Link_Movement, pos.x, pos.y - PL_OFFSET, &animations[Walk][curr_dir].GetCurrentFrame());
	else
	if (App->input->GetKey(SDL_SCANCODE_S))																					// Walk Down
		App->render->Blit(Link_Movement, pos.x, pos.y - PL_OFFSET, &animations[Walk][curr_dir].GetCurrentFrame());
	else
	if (App->input->GetKey(SDL_SCANCODE_D))																					// Walk Right
		App->render->Blit(Link_Movement, pos.x, pos.y - PL_OFFSET, &animations[Walk][curr_dir].GetCurrentFrame());
	else
		App->render->Blit(Link_Movement, pos.x, pos.y - PL_OFFSET, &animations[Idle][curr_dir].GetCurrentFrame());			// Idle

	//!_Graphics

	App->render->SetCamPos(-(pos.x - App->win->screen_surface->w / 2) , -(pos.y - App->win->screen_surface->h / 2));

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

	iPoint new_pos = App->map->MapToWorld(x, y);

	pos.x = new_pos.x;
	pos.y = new_pos.y;

	return true;
}

Point<float> j1Player::GetPos()
{
	return pos;
}
