#include "Enemy.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Input.h"
#include <time.h>

Enemy::Enemy(uint subtype)
{

}

bool Enemy::Start()
{
	bool ret = true;

	stats.Hp = 0;
	stats.Speed = 0;
	stats.Power = 0;

	stats.Flying = false;

	HitBox = new Collider({ 0, 0, 0, 0 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);
	AIType = no_move;	
	type = ENEMYTYPE::__LAST;

	return ret;

}

void Enemy::SetRewards()
{
	memset(reward_pool, 0, N_ITEMS);
	
	// Standard Reward Pool
	reward_pool[drop_heart] = 30;
	reward_pool[drop_potion] = 5;
	reward_pool[drop_rupee] = 45;
	reward_pool[drop_fiverupee] = 15;
	reward_pool[drop_tenrupee] = 5;

	SortRewardProbs();

}

void Enemy::Update(float dt)
{

	if (App->player->weapon_coll != nullptr)
		if (this->HitBox->CheckCollision(App->player->weapon_coll->rect) == true)
			Hit(App->player->curr_dir, App->player->power);
	
	if (App->player->action_blit != j1Player::Weapon_atk)
		hit = false;

		Move();

		Attack();

		Draw();
	
}

bool Enemy::Move()
{
	bool ret = true;

	iPoint target;

	switch (AIType) {
	case AITYPE::path:	
		break;
	case AITYPE::chase:
		target = { (int)App->player->GetPos().x, (int)App->player->GetPos().y };
		path_to_follow.push_back(target);
		break;
	case AITYPE::distance:
		break;
	case AITYPE::no_move:
		break;
	}

	//App->pathfinding->CreatePath({ (int)pos.x, (int)pos.y }, target);
	//
	//path_to_follow = *App->pathfinding->GetLastPath();


	if (App->debug == true) {
		for (std::list<iPoint>::iterator it = path_to_follow.begin(); it != path_to_follow.end(); it++) {
			App->render->DrawQuad({it._Ptr->_Myval.x, it._Ptr->_Myval.y, App->map->data.tile_width, App->map->data.tile_height }, 255, 0, 0, 80);
		}
	}


		if (path_to_follow.size() > 0) {

			if (path_to_follow.begin()._Ptr->_Myval.x > pos.x)
				if(stats.Flying == true || App->map->TileCheck(pos.x + rect.w + stats.Speed, pos.y, Direction::Right) == 0)
					pos.x += stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.x < pos.x)
				if (stats.Flying == true || App->map->TileCheck(pos.x - stats.Speed, pos.y, Direction::Left) == 0)
					pos.x -= stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.y > pos.y)
				if (stats.Flying == true || App->map->TileCheck(pos.x, pos.y + rect.h + stats.Speed, Direction::Down) == 0)
					pos.y += stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.y < pos.y)
				if (stats.Flying == true || App->map->TileCheck(pos.x, pos.y - stats.Speed, Direction::Up) == 0)
					pos.y -= stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.x == (int)pos.x && path_to_follow.begin()._Ptr->_Myval.y == (int)pos.y)
				path_to_follow.pop_back();
		
		}

		if (AIType == chase)
			path_to_follow.clear();
	

	if (target.y < pos.y && (target.x > pos.x - ENEMY_DIR_CHANGE_OFFSET && target.x < pos.x + ENEMY_DIR_CHANGE_OFFSET) )
		curr_dir = Enemy::EnDirection::Up;
	else if (target.y > pos.y && (target.x > pos.x - ENEMY_DIR_CHANGE_OFFSET && target.x < pos.x + ENEMY_DIR_CHANGE_OFFSET))
		curr_dir = Enemy::EnDirection::Down;
	else if (target.x < pos.x)
		curr_dir = Enemy::EnDirection::Left;
	else if (target.x > pos.x)
		curr_dir = Enemy::EnDirection::Right;

	return ret;
}

bool Enemy::Attack()
{
	bool ret = true;

	if (DmgType[melee] == true) {
		HitBox->SetPos(pos.x, pos.y);
	}

	if (App->player->link_coll != nullptr)
		if (this->HitBox->CheckCollision(App->player->link_coll->rect) == true) {
			App->player->curr_life_points -= stats.Power;

			switch (curr_dir) {
			case Up:
				if (App->map->TileCheck(App->player->GetPos().x, App->player->GetPos().y - App->map->data.tile_height, Direction::Up) == 0)
					App->player->MovePos(0, -App->map->data.tile_height);
				break;
			case Down:
				if (App->map->TileCheck(App->player->GetPos().x, App->player->GetPos().y + App->player->link_coll->rect.h + App->map->data.tile_height, Direction::Down) == 0)
					App->player->MovePos(0, App->map->data.tile_height);
				break;
			case Left:
				if (App->map->TileCheck(App->player->GetPos().x - App->map->data.tile_height, App->player->GetPos().y, Direction::Left) == 0)
					App->player->MovePos( -App->map->data.tile_width, 0);
				break;
			case Right:
				if (App->map->TileCheck(App->player->GetPos().x + App->player->link_coll->rect.w + App->map->data.tile_height, App->player->GetPos().y, Direction::Right) == 0)
					App->player->MovePos(App->map->data.tile_width, 0);
				break;
			}
		}

	return ret;
}

void Enemy::Draw()
{

	if (curr_dir == EnDirection::Left)
		inverse_draw = true;
	else
		inverse_draw = false;

	SDL_Rect draw_rect = animations[curr_dir].GetCurrentFrame();
	fPoint aux_pos = pos;
	if (inverse_draw == true)
		aux_pos.x = pos.x - draw_rect.w + HitBox->rect.w;

	App->render->Blit(Entity::GetTexture(), aux_pos.x, aux_pos.y, &draw_rect);
}

void Enemy::Hit(uint dir, uint dmg)
{


	if (hit == false) {
		
		hit = true;
		
		LOG("HP: %d DMG: %d", stats.Hp, dmg);

		stats.Hp -= dmg;
		
		LOG("HP: %d", stats.Hp, dmg);

		if (stats.Hp <= 0) {
			LOG("ENEMY DEATH");
			Death();
			return;
		}

		switch (dir) {
		case Direction::Up:
			if (App->map->TileCheck(pos.x, pos.y - JUMP_WHEN_HIT, Direction::Up) == 0)
				pos.y -= JUMP_WHEN_HIT;
			break;
		case Direction::Down:
			if (App->map->TileCheck(pos.x, pos.y + JUMP_WHEN_HIT, Direction::Down) == 0)
				pos.y += JUMP_WHEN_HIT;
			break;
		case Direction::Left:
			if (App->map->TileCheck(pos.x - JUMP_WHEN_HIT, pos.y, Direction::Left) == 0)
				pos.x -= JUMP_WHEN_HIT;
			break;
		case Direction::Right:
			if (App->map->TileCheck(pos.x + JUMP_WHEN_HIT, pos.y, Direction::Right) == 0)
				pos.x += JUMP_WHEN_HIT;
			break;
		}
		
	}

}

void Enemy::Death()
{
	Reward();

	App->entitymanager->DestroyEnity(this);
}

void Enemy::Reward()
{

	srand(time(NULL));

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

		Item* newitem;

		newitem = App->entitymanager->CreateItem(target);
		if (newitem != nullptr)
			newitem->pos = { pos.x, pos.y };

	}
	else
		LOG("NO REWARD FAGGOT");

}

void Enemy::CleanUp()
{
	if (tex != nullptr)
		App->tex->UnLoad(tex);

	if (HitBox != nullptr)
		HitBox->to_delete = true;

	path_to_follow.clear();

	App->scene_manager->GetCurrentScene()->DestroyEnemy(this);
}

bool BSoldier::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Enemy::EnDirection::Down][0] = { 30, 251, 44, 68 };
		sprites[Enemy::EnDirection::Down][1] = { 132, 249, 44, 70 };

		sprites[Enemy::EnDirection::Up][0] = { 30, 357, 44, 52 };
		sprites[Enemy::EnDirection::Up][1] = { 132, 357, 44, 52 };

		sprites[Enemy::EnDirection::Left][0] = { 214, 465, 64, 54 };
		sprites[Enemy::EnDirection::Left][1] = { 316, 465, 64, 54 };

		sprites[Enemy::EnDirection::Right][0] = { 30, 465, 64, 54 };
		sprites[Enemy::EnDirection::Right][1] = { 132, 465, 64, 54 };

		animations[Enemy::EnDirection::Down].PushBack(sprites[Down][0]);
		animations[Enemy::EnDirection::Down].PushBack(sprites[Down][1]);

		animations[Enemy::EnDirection::Up].PushBack(sprites[Up][0]);
		animations[Enemy::EnDirection::Up].PushBack(sprites[Up][1]);

		animations[Enemy::EnDirection::Left].PushBack(sprites[Left][0]);
		animations[Enemy::EnDirection::Left].PushBack(sprites[Left][1]);

		animations[Enemy::EnDirection::Right].PushBack(sprites[Right][0]);
		animations[Enemy::EnDirection::Right].PushBack(sprites[Right][1]);


	}

	stats.Hp = 3;
	stats.Speed = 1.5;
	stats.Power = 1;

	stats.Flying = false;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 36, 56 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = chase;

	subtype = ENEMYTYPE::BlueSoldier;

	return ret;
}

bool RSoldier::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Enemy::EnDirection::Down][0] = { 438, 251, 44, 68 };
		sprites[Enemy::EnDirection::Down][1] = { 540, 249, 44, 70 };

		sprites[Enemy::EnDirection::Up][0] = { 438, 357, 44, 52 };
		sprites[Enemy::EnDirection::Up][1] = { 540, 357, 44, 52 };

		sprites[Enemy::EnDirection::Left][0] = { 420, 575, 64, 54 };
		sprites[Enemy::EnDirection::Left][1] = { 528, 577, 58, 52 };

		sprites[Enemy::EnDirection::Right][0] = { 438, 467, 58, 52 };
		sprites[Enemy::EnDirection::Right][1] = { 540, 465, 64, 54 };

		animations[Enemy::EnDirection::Down].PushBack(sprites[Down][0]);
		animations[Enemy::EnDirection::Down].PushBack(sprites[Down][1]);

		animations[Enemy::EnDirection::Up].PushBack(sprites[Up][0]);
		animations[Enemy::EnDirection::Up].PushBack(sprites[Up][1]);

		animations[Enemy::EnDirection::Left].PushBack(sprites[Left][0]);
		animations[Enemy::EnDirection::Left].PushBack(sprites[Left][1]);

		animations[Enemy::EnDirection::Right].PushBack(sprites[Right][0]);
		animations[Enemy::EnDirection::Right].PushBack(sprites[Right][1]);


	}

	stats.Hp = 5;
	stats.Speed = 0.75;
	stats.Power = 2;

	stats.Flying = false;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 36, 56 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = chase;

	subtype = ENEMYTYPE::RedSoldier;

	return ret;
}

bool GSoldier::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Enemy::EnDirection::Down][0] = { 36, 25, 32, 56 };
		sprites[Enemy::EnDirection::Down][1] = { 138, 25, 32, 56 };

		sprites[Enemy::EnDirection::Up][0] = { 648, 25, 32, 56 };
		sprites[Enemy::EnDirection::Up][1] = { 750, 25, 32, 56 };

		sprites[Enemy::EnDirection::Left][0] = { 440, 25, 36, 56 };
		sprites[Enemy::EnDirection::Left][1] = { 542, 25, 64, 56 };

		sprites[Enemy::EnDirection::Right][0] = { 240, 25, 36, 56 };
		sprites[Enemy::EnDirection::Right][1] = { 342, 25, 36, 56 };

		animations[Enemy::EnDirection::Down].PushBack(sprites[Down][0]);
		animations[Enemy::EnDirection::Down].PushBack(sprites[Down][1]);

		animations[Enemy::EnDirection::Up].PushBack(sprites[Up][0]);
		animations[Enemy::EnDirection::Up].PushBack(sprites[Up][1]);

		animations[Enemy::EnDirection::Left].PushBack(sprites[Left][0]);
		animations[Enemy::EnDirection::Left].PushBack(sprites[Left][1]);

		animations[Enemy::EnDirection::Right].PushBack(sprites[Right][0]);
		animations[Enemy::EnDirection::Right].PushBack(sprites[Right][1]);


	}

	stats.Hp = 1;
	stats.Speed = 2.5;
	stats.Power = 1;

	stats.Flying = false;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 36, 56 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = chase;

	subtype = ENEMYTYPE::GreenSoldier;

	return ret;
}
