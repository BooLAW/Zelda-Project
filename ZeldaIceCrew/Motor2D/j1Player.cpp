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

	// !_SDL_Rects

	// Load Textures

	Link_Movement = App->tex->Load("Sprites/Link_Movement.png");

	// !_Textures

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;

	App->render->Blit(Link_Movement, 0, 0, &sprites[Idle][Left][0]);

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
