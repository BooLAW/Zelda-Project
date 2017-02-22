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

	// Idle
	{
		sprites[Idle][Up][0].x = 59;
		sprites[Idle][Up][0].y = 31;
		sprites[Idle][Up][0].w = 16;
		sprites[Idle][Up][0].h = 22;

		sprites[Idle][Down][0].x = 59;
		sprites[Idle][Down][0].y = 4;
		sprites[Idle][Down][0].w = 16;
		sprites[Idle][Down][0].h = 22;

		sprites[Idle][Left][0].x = 59;
		sprites[Idle][Left][0].y = 82;
		sprites[Idle][Left][0].w = 16;
		sprites[Idle][Left][0].h = 22;

		sprites[Idle][Right][0].x = 59;
		sprites[Idle][Right][0].y = 56;
		sprites[Idle][Right][0].w = 16;
		sprites[Idle][Right][0].h = 22;
	}
	
	//Walk
	{
	sprites[Walk][Up][0] = { 2,29,16,24 };
	sprites[Walk][Up][1] = { 21,30,16,23 };
	sprites[Walk][Up][2] = { 40,31,16,22 };
	sprites[Walk][Up][3] = { 59,31,16,22 };
	sprites[Walk][Up][4] = { 78,31,16,22 };
	sprites[Walk][Up][5] = { 97,30,16,23 };
	sprites[Walk][Up][6] = { 116,29,16,24 };

	sprites[Walk][Down][0] = { 2,2,16,24 };
	sprites[Walk][Down][1] = { 21,3,16,24 };
	sprites[Walk][Down][2] = { 40,4,16,22 };
	sprites[Walk][Down][3] = { 59,4,16,22 };
	sprites[Walk][Down][4] = { 78,4,16,22 };
	sprites[Walk][Down][5] = { 97,3,16,23 };
	sprites[Walk][Down][6] = { 116,2,16,24 };

	sprites[Walk][Right][0] = { 2,56,16,23 };
	sprites[Walk][Right][1] = { 21,55,16,23 };
	sprites[Walk][Right][2] = { 40,55,16,24 };
	sprites[Walk][Right][3] = { 59,56,16,24 };
	sprites[Walk][Right][4] = { 78,55,16,23 };
	sprites[Walk][Right][5] = { 97,55,16,24 };
	sprites[Walk][Right][6] = { 116,56,16,24 };

	sprites[Walk][Left][0] = { 2,82,16,23 };
	sprites[Walk][Left][1] = { 21,81,16,24 };
	sprites[Walk][Left][2] = { 40,81,16,24 };
	sprites[Walk][Left][3] = { 59,82,16,23 };
	sprites[Walk][Left][4] = { 78,81,16,24 };
	sprites[Walk][Left][5] = { 97,81,16,24 };
	sprites[Walk][Left][6] = { 116,82,17,23 };
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

	// !_Logic

	// Graphics
	if (App->input->GetKey(SDL_SCANCODE_W))																		// Walk UP
		App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Walk][curr_dir].GetCurrentFrame());
	else
	if (App->input->GetKey(SDL_SCANCODE_A))																		// Walk Left
		App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Walk][curr_dir].GetCurrentFrame());
	else
	if (App->input->GetKey(SDL_SCANCODE_S))																		// Walk Down
		App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Walk][curr_dir].GetCurrentFrame());
	else
	if (App->input->GetKey(SDL_SCANCODE_D))																		// Walk Right
		App->render->Blit(Link_Movement, pos.x, pos.y, &animations[Walk][curr_dir].GetCurrentFrame());
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
