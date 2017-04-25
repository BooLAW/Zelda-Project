#include "Block.h"
#include "j1Map.h"
#include "j1Input.h"
#include <time.h>

Block::Block(uint subtype) {

}

bool Block::Start()
{

	bool ret = true;
	anim = idle;

	HitBox = new Collider({ 0, 0, 0, 0 }, COLLIDER_BLOCK);

	type = BLOCKTYPE::last_;

	return ret;

}

void Block::CleanUp()
{
	if (tex != nullptr)
		App->tex->UnLoad(tex);
	if (HitBox != nullptr)
		HitBox->to_delete = true;

	App->scene_manager->GetCurrentScene()->DestroyBlock(this);

}

void Bush::SetRewards()
{
	memset(reward_pool, 0, N_ITEMS);

	// Standard Reward Pool
	reward_pool[drop_heart] = 0;
	reward_pool[drop_potion] = 0;
	reward_pool[drop_rupee] = 30;
	reward_pool[drop_fiverupee] = 1;
	reward_pool[drop_tenrupee] = 0;

	//SortRewardProbs();

}

void Pot::SetRewards()
{
	memset(reward_pool, 0, N_ITEMS);

	// Standard Reward Pool
	reward_pool[drop_heart] = 10;
	reward_pool[drop_potion] = 1;
	reward_pool[drop_rupee] = 30;
	reward_pool[drop_fiverupee] = 1;
	reward_pool[drop_tenrupee] = 0;

	//SortRewardProbs();

}

void Block::Reward()
{

	uint aux = 0;
	uint prob = (rand() % 100) + 1;

	int target = -1;

	for (uint i = 0; i < N_ITEMS; i++) {
		if (prob <= aux + reward_pool[i] && prob > aux) {
			target = i;
			break;
		}
		else {
			aux += reward_pool[i];
		}
	}

	if (target != -1) {

		App->scene_manager->GetCurrentScene()->AddItem(target, room.x, room.y, pos.x - room.x * ROOM_W, pos.y - room.y * ROOM_H);

	}
	else {}
		//LOG("NO REWARD FAGGOT");

}

void Block::Update(float dt)
{

	//LOG("BLOCK UPDATE");

	if(HitBox != nullptr)
	HitBox->SetPos(pos.x, pos.y + sprites[subtype][idle][0].h - 32);

	/*if (App->player->link_coll != nullptr) {

	if (HitBox->CheckCollision(App->player->link_coll->rect) == true) {
	if (this->isPushable()) {
	this->Push();
	}
	}
	}*/

	//Check that you don't have an item picked
	if (moving == false) {
		if (picked == false && App->player->action_blit != App->player->Hold_sth && App->player->action == false)
		{
			if (App->player->weapon_coll != nullptr && App->player->weapon_coll->rect.x != FARLANDS.x) {

				if(HitBox != nullptr)
				if (this->HitBox->CheckCollision(App->player->weapon_coll->rect) == true) {
					if (this->isBreakable()) {
						this->Break();
					}
				}
			}

			if (App->player->action_coll != nullptr && App->player->action_coll->rect.x != FARLANDS.x) {
				if(HitBox != nullptr)
				if (HitBox->CheckCollision(App->player->action_coll->rect) == true) {
					if (this->isPickable()) {
						this->Pick();
					}
					else if (this->isLitable()) {
						this->Light();
					}
					else
						this->Move();
				}
			}
		}

		else if (picked == true /*App->player->action_blit == App->player->Hold_sth*/) {

			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
				this->Throw();
			}

			else {
				this->pos = App->player->GetPos();
			}
		}
	}
	else
		Move();


	Draw();

}

void Block::Draw()
{

	SDL_Rect draw_rect = animations[subtype][anim].GetCurrentFrame();
	fPoint aux_pos = pos;

	//App->render->Blit(Entity::GetTexture(), aux_pos.x, aux_pos.y, &draw_rect);
	App->render->toDraw(tex, pos.y + animations[subtype][anim].GetCurrentFrame().h, pos.x, pos.y, &animations[subtype][anim].GetCurrentFrame());
}


bool Bush::Start() {
	bool ret = true;
	SetRewards();
	anim = idle;
	subtype = bush;
	Entity::SetTexture(App->tex->Load("Sprites/Blocks_Temp.png"));
	{
		sprites[bush][idle][0] = { 0,0,32,32 };

		//sprites[bush][broke][] = ;

		animations[bush][idle].PushBack(sprites[bush][idle][0]);
	}
	HitBox = App->collisions->AddCollider({ int(pos.x),int(pos.y), 32, 32 }, COLLIDER_BLOCK);

	subtype = bush;

	return ret;
}

bool Pot::Start() {
	bool ret = true;
	SetRewards();
	anim = idle;
	subtype = pot;
	Entity::SetTexture(App->tex->Load("Sprites/Blocks_Temp.png"));
	{
		sprites[pot][idle][0] = { 32,32,32,32 };

		//sprites[pot][broke][] = ;

		animations[pot][idle].PushBack(sprites[bush][idle][0]);
	}

	HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_BLOCK);

	subtype = pot;
	return ret;
}

bool Slab::Start() {
	bool ret = true;
	front = true;
	back = true;
	subtype = slabs;
	Entity::SetTexture(App->tex->Load("Sprites/Blocks_Temp.png"));
	anim = idle;
	{
		sprites[slabs][idle][0] = { 32,64,32,32 };

		animations[slabs][idle].PushBack(sprites[slabs][idle][0]);
	}

	HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_BLOCK);

	subtype = slabs;
	return ret;
}

bool Slab_No_Move::Start()
{
	bool ret = true;
	subtype = slabs_no_move;
	Entity::SetTexture(App->tex->Load("Sprites/Blocks_Temp.png"));
	anim = idle;
	{
		sprites[slabs_no_move][idle][0] = { 0,64,32,32 };

		animations[slabs_no_move][idle].PushBack(sprites[slabs_no_move][idle][0]);
	}

	HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_BLOCK);

	subtype = slabs_no_move;
	return ret;
}


bool Statue::Start() {
	bool ret = true;
	front = true;
	subtype = statue;
	Entity::SetTexture(App->tex->Load("Sprites/Blocks_Temp.png"));
	anim = idle;
	{
		sprites[statue][idle][0] = { 64,0,32,49 };

		//sprites[bush][broke][] = ;

		animations[statue][idle].PushBack(sprites[statue][idle][0]);
	}
	HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_BLOCK);

	subtype = statue;
	return ret;
}

bool Torch_Bowl::Start() {
	bool ret = true;
	subtype = torch_bowl;
	Entity::SetTexture(App->tex->Load("Sprites/Blocks_Temp.png"));
	anim = idle;

	HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_BLOCK);

	subtype = torch_bowl;
	return ret;
}

bool Slab_Spikes::Start()
{
	bool ret = true;
	subtype = slabs_spikes;
	Entity::SetTexture(App->tex->Load("Sprites/Blocks_Temp.png"));
	anim = idle;
	{
		sprites[slabs_spikes][idle][0] = { 64,50,32,32 };

		animations[slabs_no_move][idle].PushBack(sprites[slabs_spikes][idle][0]);
	}

	HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_ENEMY);

	subtype = slabs_no_move;
	return ret;
}

void Block::Move() {
	App->player->action_blit = App->player->Pull;
	App->player->action = true;
	HitBox->SetPos(pos.x, pos.y + sprites[subtype][idle][0].h - 32);
	if (App->player->curr_dir == Up) {
		if (front == true && App->input->GetKey(SDL_SCANCODE_W)) {
			App->player->action_blit = App->player->Push;
			if (CheckSpace(HitBox->rect.x, HitBox->rect.y - App->player->pl_speed.y / 4)) {
				App->player->pos.y -= App->player->pl_speed.y / 4;
				pos.y -= App->player->pl_speed.y / 4;
			}
		}
		else if (back == true && App->input->GetKey(SDL_SCANCODE_S)) {
			App->player->action_blit = App->player->Pull;
			if (CheckSpace(HitBox->rect.x, HitBox->rect.y + App->player->pl_speed.y / 4)) {
				App->player->pos.y += App->player->pl_speed.y / 4;
				pos.y += App->player->pl_speed.y / 4;
			}
		}
	}
	else if (App->player->curr_dir == Left) {
		if (front == true && App->input->GetKey(SDL_SCANCODE_A)) {
			App->player->action_blit = App->player->Push;
			if (CheckSpace(HitBox->rect.x - App->player->pl_speed.x / 4, HitBox->rect.y)) {
				App->player->pos.x -= App->player->pl_speed.x / 4;
				pos.x -= App->player->pl_speed.x / 4;
			}
		}
		else if (back == true && App->input->GetKey(SDL_SCANCODE_D)) {
			App->player->action_blit = App->player->Pull;
			if (CheckSpace(HitBox->rect.x + App->player->pl_speed.x / 4, HitBox->rect.y)) {
				App->player->pos.x += App->player->pl_speed.x / 4;
				pos.x += App->player->pl_speed.x / 4;
			}
		}
	}

	else if (App->player->curr_dir == Right) {
		if (front == true && App->input->GetKey(SDL_SCANCODE_D)) {
			App->player->action_blit = App->player->Push;
			bool test = CheckSpace(pos.x + App->player->pl_speed.x / 4, pos.y);
			if (CheckSpace(HitBox->rect.x  + App->player->pl_speed.x / 4, HitBox->rect.y)) {
				App->player->pos.x += App->player->pl_speed.x / 4;
				pos.x += App->player->pl_speed.x / 4;
			}
		}
		else if (back == true && App->input->GetKey(SDL_SCANCODE_A)) {
			App->player->action_blit = App->player->Pull;
			if (CheckSpace(HitBox->rect.x - App->player->pl_speed.x / 4, HitBox->rect.y)) {
				App->player->pos.x -= App->player->pl_speed.x / 4;
				pos.x -= App->player->pl_speed.x / 4;
			}
		}
	}

	else if (App->player->curr_dir == Down) {
		if (front == true && App->input->GetKey(SDL_SCANCODE_S)) {
			App->player->action_blit = App->player->Push;
 		if (CheckSpace(HitBox->rect.x, HitBox->rect.y + App->player->pl_speed.y / 4)) {
				App->player->pos.y += App->player->pl_speed.y / 4;
				pos.y += App->player->pl_speed.y / 4;
			}
		}
		else if (back == true && App->input->GetKey(SDL_SCANCODE_W)) {
			App->player->action_blit = App->player->Pull;
			if (CheckSpace(HitBox->rect.x, HitBox->rect.y - App->player->pl_speed.y / 4)) {
				App->player->pos.y -= App->player->pl_speed.y / 4;
				pos.y -= App->player->pl_speed.y / 4;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE))
		moving = true;
	else
		moving = false;
}

void Torch_Bowl::Light() {
	//changes the spire blitted, from idle to lit
	App->player->action_blit = App->player->Light;
	App->player->action = true;

}

void Bush::Break() {
	//triggers break animation (for whatever reason) and calls destructor
	Reward();

	this->CleanUp();

}

void Pot::Break() {
	//triggers break animation (for whatever reason) and calls destructor
	Reward();

	this->CleanUp();

}

void Bush::Pick() {
	//triggers pick animation, then put pick state
	App->player->action_blit = App->player->Pickup;
	App->player->action = true;
	picked = true;
	Reward();
	App->collisions->EraseCollider(this->HitBox);
	this->pos = App->player->GetPos();

}

void Pot::Pick() {
	//triggers pick animation, then put pick state
	App->player->action_blit = App->player->Pickup;
	App->player->action = true;
	picked = true;
	App->collisions->EraseCollider(this->HitBox);
	this->pos = App->player->GetPos();

}

void Bush::Throw() {
	//throws if something is held
	Break();
}

void Pot::Throw() {
	//throws if something is held
	Break();
}


/*bool Torch_Pillar::Start() {
bool ret = true;
Entity::SetTexture(App->tex->Load("Sprites/Blocks_Temp.png"));
anim = idle;

HitBox = App->collisions->AddCollider({ 0, 0, 32, 64 }, COLLIDER_BLOCK);

subtype = torch_pillar;
return ret;
}

void Torch_Pillar::Light() {
//changes the spire blitted, from idle to lit
App->player->action_blit = App->player->Light;
App->player->action = true;

}*/


