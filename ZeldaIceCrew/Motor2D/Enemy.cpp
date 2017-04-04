#include "Enemy.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Input.h"
#include <time.h>
#include <math.h>

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
	type = ENEMYTYPE::__LAST_ENEMYTYPE;
	hit_fx = App->audio->LoadFx("Audio/Fx/enemy_hit.wav");
	return ret;

}

void Enemy::SetRewards()
{
	memset(reward_pool, 0, N_ITEMS);
	
	// Standard Reward Pool
	reward_pool[drop_heart] = 5;
	reward_pool[drop_potion] = 0;
	reward_pool[drop_rupee] = 50;
	reward_pool[drop_fiverupee] = 10;
	reward_pool[drop_tenrupee] = 0;

	//SortRewardProbs();

}

void Enemy::Update(float dt)
{

	if (App->render->IsCameraCull(this->HitBox->rect) == 0) {

		if (App->player->weapon_coll != nullptr)
			if (this->HitBox->CheckCollision(App->player->weapon_coll->rect) == true) {
				Hit(App->player->curr_dir, App->player->power);
				App->audio->PlayFx(hit_fx);
			}

		if (App->player->action_blit != j1Player::Weapon_atk)
			hit = false;

	if(App->debug_mode == false)
		Move();

		Attack();

		Draw();

	}

	
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
				if(stats.Flying == true || CheckSpace(pos.x + stats.Speed, pos.y))
					pos.x += stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.x < pos.x)
				if (stats.Flying == true || CheckSpace(pos.x - stats.Speed, pos.y))
					pos.x -= stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.y > pos.y)
				if (stats.Flying == true || CheckSpace(pos.x, pos.y + stats.Speed))
					pos.y += stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.y < pos.y)
				if (stats.Flying == true || CheckSpace(pos.x, pos.y - stats.Speed))
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
		HitBox->SetPos(pos.x, pos.y + ENEMY_STD_OFFSET_Y);
	}

	if (App->player->link_coll != nullptr)
		if (this->HitBox->CheckCollision(App->player->link_coll->rect) == true) {
			HitPlayer();
		}
	

	return ret;
}

void Enemy::HitPlayer()
{

	if (App->player->inmortal == false) {

		App->audio->PlayFx(App->player->hurt);
		App->player->curr_life_points -= stats.Power;

		switch (curr_dir) {
		case Up:
			if (App->player->CheckSpace(App->player->GetPos().x, App->player->GetPos().y - App->map->data.tile_height))
				App->player->MovePos(0, -App->map->data.tile_height);
			break;
		case Down:
			if (App->player->CheckSpace(App->player->GetPos().x, App->player->GetPos().y + App->player->link_coll->rect.h + App->map->data.tile_height))
				App->player->MovePos(0, App->map->data.tile_height);
			break;
		case Left:
			if (App->player->CheckSpace(App->player->GetPos().x - App->map->data.tile_height, App->player->GetPos().y))
				App->player->MovePos(-App->map->data.tile_width, 0);
			break;
		case Right:
			if (App->player->CheckSpace(App->player->GetPos().x + App->player->link_coll->rect.w + App->map->data.tile_height, App->player->GetPos().y))
				App->player->MovePos(App->map->data.tile_width, 0);
			break;
		}

		App->player->PlayerInmortal(HIT_INM_TIME);
	}
}

void Enemy::HitPlayer(uint dmg)
{

	if (App->player->inmortal == false) {

		if (dmg != NULL)
			App->audio->PlayFx(App->player->hurt);

		App->player->curr_life_points -= dmg;

		switch (curr_dir) {
		case Up:
			if (App->player->CheckSpace(App->player->GetPos().x, App->player->GetPos().y - App->map->data.tile_height))
				App->player->MovePos(0, -App->map->data.tile_height);
			break;
		case Down:
			if (App->player->CheckSpace(App->player->GetPos().x, App->player->GetPos().y + App->player->link_coll->rect.h + App->map->data.tile_height))
				App->player->MovePos(0, App->map->data.tile_height);
			break;
		case Left:
			if (App->player->CheckSpace(App->player->GetPos().x - App->map->data.tile_height, App->player->GetPos().y))
				App->player->MovePos(-App->map->data.tile_width, 0);
			break;
		case Right:
			if (App->player->CheckSpace(App->player->GetPos().x + App->player->link_coll->rect.w + App->map->data.tile_height, App->player->GetPos().y))
				App->player->MovePos(App->map->data.tile_width, 0);
			break;
		}

		if (dmg != NULL)
			App->player->PlayerInmortal(HIT_INM_TIME);
	}

}

void Enemy::Draw()
{

	if (curr_dir == EnDirection::Left)
		inverse_draw = true;
	else
		inverse_draw = false;

	SDL_Rect* draw_rect = &animations[curr_dir].GetCurrentFrame();
	fPoint aux_pos = pos;
	if (inverse_draw == true)
		aux_pos.x = pos.x - draw_rect->w + HitBox->rect.w;

	//App->render->Blit(GetTexture(), aux_pos.x, aux_pos.y, &draw_rect);
	App->render->toDraw(GetTexture(), aux_pos.y + draw_rect->h, aux_pos.x, aux_pos.y, draw_rect);
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
			if (CheckSpace(pos.x, pos.y - jump_hit))
				pos.y -= jump_hit;
			break;
		case Direction::Down:
			if (CheckSpace(pos.x, pos.y + jump_hit))
				pos.y += jump_hit;
			break;
		case Direction::Left:
			if (CheckSpace(pos.x - jump_hit, pos.y))
				pos.x -= jump_hit;
			break;
		case Direction::Right:
			if (CheckSpace(pos.x + jump_hit, pos.y))
				pos.x += jump_hit;
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
	
		App->scene_manager->GetCurrentScene()->AddItem(target, pos.x + HitBox->rect.w / 2 - 16, pos.y + +HitBox->rect.h / 2 - 16);

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

	HitBox = App->collisions->AddCollider({ 0, 0, 36, 32 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = chase;

	subtype = ENEMYTYPE::t_bluesoldier;

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

	HitBox = App->collisions->AddCollider({ 0, 0, 36, 32 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = chase;

	subtype = ENEMYTYPE::t_redsoldier;

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
		sprites[Enemy::EnDirection::Left][1] = { 542, 25, 36, 56 };

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

	HitBox = App->collisions->AddCollider({ 0, 0, 36, 32 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = chase;

	subtype = ENEMYTYPE::t_greensoldier;

	return ret;
}

bool BossChainBall::Start()
{
	bool ret = true;

	int cb_n = 0;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Mace knight.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Enemy::EnDirection::Down][0] = { 2, 226 * 10 + 2, 211, 224 };
		sprites[Enemy::EnDirection::Down][1] = { 218, 226 * 10 + 2, 208, 224 };
		sprites[Enemy::EnDirection::Down][2] = { 2, 226 * 10 + 2, 211, 224 };
		sprites[Enemy::EnDirection::Down][3] = { 434, 226 * 10 + 2, 205, 224 };

		sprites[Enemy::EnDirection::Up][0] = { 2, 226 * 6 + 2, 211, 224 };
		sprites[Enemy::EnDirection::Up][1] = { 215, 226 * 6 + 2, 211, 224 };
		sprites[Enemy::EnDirection::Up][2] = { 2, 226 * 6 + 2, 211, 224 };
		sprites[Enemy::EnDirection::Up][3] = { 215 * 2 - 2, 226 * 6 + 2, 211, 224 };

		sprites[Enemy::EnDirection::Left][0] = { 2, 2, 211, 224 };
		sprites[Enemy::EnDirection::Left][1] = { 215, 4, 211, 222 };
		sprites[Enemy::EnDirection::Left][2] = { 2, 2, 211, 224 };
		sprites[Enemy::EnDirection::Left][3] = { 215 * 2 - 2, 4, 211, 222 };

		sprites[Enemy::EnDirection::Right][0] = { 2, 2, 211, 224 };
		sprites[Enemy::EnDirection::Right][1] = { 215, 4, 211, 222 };
		sprites[Enemy::EnDirection::Right][2] = { 2, 2, 211, 224 };
		sprites[Enemy::EnDirection::Right][3] = { 215 * 2 - 2, 4, 211, 222 };


		//ball_rect[circle_ball][Up][cb_n++] = { 215 * 5 - 2, 226 * 9 + 2, 211, 224 };
		//ball_rect[circle_ball][Up][cb_n++] = { 215 * 4 - 2, 226 * 9 + 2, 211, 224 };
		//ball_rect[circle_ball][Up][cb_n++] = { 215 * 3 - 2, 226 * 9 + 2, 211, 224 };
		//ball_rect[circle_ball][Up][cb_n++] = { 215 * 2 - 2, 226 * 9 + 2, 211, 224 };
		//ball_rect[circle_ball][Up][cb_n++] = { 215 * 1 - 2, 226 * 9 + 2, 211, 224 };
		//ball_rect[circle_ball][Up][cb_n++] = { 2, 226 * 9 + 2, 211, 224 };
		//
		//cb_n = 0;
		//
		//ball_rect[circle_ball][Down][cb_n++] = { 215 * 4 - 6, 226 * 12 + 2, 211, 224 };
		//ball_rect[circle_ball][Down][cb_n++] = { 215 * 4 - 6, 226 * 13 + 2, 211, 216 };
		//ball_rect[circle_ball][Down][cb_n++] = { 215 * 3 - 4, 226 * 13 + 2, 211, 224 };
		//ball_rect[circle_ball][Down][cb_n++] = { 215 * 2 - 2, 226 * 13 + 2, 211, 224 };
		//ball_rect[circle_ball][Down][cb_n++] = { 215 * 1, 226 * 13 + 2, 211, 224 };
		//ball_rect[circle_ball][Down][cb_n++] = { 2, 226 * 13 + 2, 211, 224 };
		//ball_rect[circle_ball][Down][cb_n++] = { 2, 226 * 12 + 2, 211, 224 };
		//ball_rect[circle_ball][Down][cb_n++] = { 215 * 5 - 8, 226 * 10 + 2, 211, 224 };
		//
		//cb_n = 0;
		//
		//ball_rect[circle_ball][Left][cb_n++] = { 215 * 5, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Left][cb_n++] = { 215 * 4, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Left][cb_n++] = { 215 * 3, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Left][cb_n++] = { 215 * 2, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Left][cb_n++] = { 215 * 1, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Left][cb_n++] = { 2, 226 * 3 + 2, 211, 224 };
		//
		//cb_n = 0;
		//
		//ball_rect[circle_ball][Right][cb_n++] = { 215 * 5, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Right][cb_n++] = { 215 * 4, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Right][cb_n++] = { 215 * 3, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Right][cb_n++] = { 215 * 2, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Right][cb_n++] = { 215 * 1, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Right][cb_n++] = { 2, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Right][cb_n++] = { 215 * 1, 226 * 3 + 2, 211, 224 };
		//ball_rect[circle_ball][Right][cb_n++] = { 215 * 5, 226 * 3 + 2, 211, 224 };



	}

	stats.Hp = 60;
	stats.Speed = 1;
	stats.Power = 2;

	for (int i = 0; i < EnDirection::LastDir; i++) {
		for (int k = 0; k < 4; k++)
			animations[i].PushBack(sprites[i][k]);
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5
	}

	//for (int i = 0; i < EnDirection::LastDir; i++) {
	//	for (int k = 0; k < cb_n; k++)
	//		ball_anim[circle_ball][i].PushBack(ball_rect[circle_ball][i][k]);
	//	ball_anim[circle_ball][i].speed = 0.01;
	//}

	stats.Flying = false;

	HitBox = App->collisions->AddCollider({ 0, 0, 36, 32 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = chase;

	subtype = ENEMYTYPE::t_boss_ballandchain;

	SDL_Rect ball_rect = { 0, 0, 32, 32 };
	ball_collider = App->collisions->AddCollider(ball_rect, COLLIDER_ENEMY_PROJECTILE);

	return ret;
}

bool BossChainBall::Attack()
{

	bool ret = true;

	if (DmgType[melee] == true) {
		HitBox->SetPos(pos.x, pos.y + ENEMY_STD_OFFSET_Y);
	}

	

	switch (state) {
	case no_ball_start:
		ball_collider->SetPos(FARLANDS.x, FARLANDS.y);
		ball_timer.Start();
		state = no_ball;
		break;
	case no_ball:
		if (ball_timer.ReadSec() >= 3)
			state = circle_ball_start;
		break;
	case circle_ball_start:
		ball_r = 64;
		ball_centre = pos;
		ball_x = ball_centre.x - ball_r;
		ball_y = ball_centre.y;
		ball_speed = 0.1;
		ball_p = 0;
		round_counter = 0;
		state = circle_ball;
		break;
	case circle_ball:
		
		ball_centre = pos;

		if (ball_p >= 2 * PI) {
			ball_p = 0;
			round_counter++;
		}

		ball_x = ball_r * cos(ball_p) + ball_centre.x;
		ball_y = ball_r * sin(ball_p) + ball_centre.y;

		ball_p += ball_speed;

		ball_collider->SetPos(ball_x, ball_y);
		
		if (round_counter >= 5)
			state = no_ball_start;

		break;
	case attack_ball_start:
		break;
	case attack_ball:
		break;
	}

	if (App->player->link_coll != nullptr) {
		if (this->ball_collider->CheckCollision(App->player->link_coll->rect) == true) {
			HitPlayer();
		}
		if (this->HitBox->CheckCollision(App->player->link_coll->rect) == true) {
			HitPlayer(NULL);
		}
	}

	return ret;
}

void BossChainBall::SetRewards()
{
	reward_pool[boss_key] = 100;
}

void BossChainBall::Draw()
{
	SDL_Rect* draw_rect;
	
	switch (state) {
	//case circle_ball:
	//	draw_rect = &ball_anim[circle_ball][curr_dir].GetCurrentFrame();
	//	break;
	default:
		draw_rect = &animations[curr_dir].GetCurrentFrame();
		break;
	}

	fPoint aux_pos = pos;
	aux_pos.x -= 86;
	aux_pos.y -= 86;

	//App->render->Blit(GetTexture(), aux_pos.x, aux_pos.y, &draw_rect);
	App->render->toDraw(GetTexture(), pos.y + HitBox->rect.h, aux_pos.x, aux_pos.y, draw_rect);
	App->render->DrawQuad({ ball_collider->rect.x, ball_collider->rect.y, 32, 32 }, 255, 255, 255, 90);

}

void BossChainBall::CleanUp()
{
	if (tex != nullptr)
		App->tex->UnLoad(tex);

	if (HitBox != nullptr)
		HitBox->to_delete = true;

	path_to_follow.clear();

	if (ball_collider != nullptr)
		ball_collider->to_delete = true;

	App->scene_manager->GetCurrentScene()->DestroyEnemy(this);
}

bool Hinox::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Enemy::EnDirection::Down][0] = { 636, 239, 56, 60 };
		sprites[Enemy::EnDirection::Down][1] = { 739, 239, 56, 60 };

		sprites[Enemy::EnDirection::Up][0] = { 635, 349, 56, 60 };
		sprites[Enemy::EnDirection::Up][1] = { 738, 349, 56, 60 };

		sprites[Enemy::EnDirection::Left][0] = { 647, 463, 38, 56 };
		sprites[Enemy::EnDirection::Left][1] = { 748, 461, 38, 58 };

		sprites[Enemy::EnDirection::Right][0] = { 648, 571, 38, 58 };
		sprites[Enemy::EnDirection::Right][1] = { 749, 573, 38, 56 };

		animations[Enemy::EnDirection::Down].PushBack(sprites[Down][0]);
		animations[Enemy::EnDirection::Down].PushBack(sprites[Down][1]);

		animations[Enemy::EnDirection::Up].PushBack(sprites[Up][0]);
		animations[Enemy::EnDirection::Up].PushBack(sprites[Up][1]);

		animations[Enemy::EnDirection::Left].PushBack(sprites[Left][0]);
		animations[Enemy::EnDirection::Left].PushBack(sprites[Left][1]);

		animations[Enemy::EnDirection::Right].PushBack(sprites[Right][0]);
		animations[Enemy::EnDirection::Right].PushBack(sprites[Right][1]);


	}

	stats.Hp = 15;
	stats.Speed = 0.75;
	stats.Power = 1;

	jump_hit = 8;

	stats.Flying = false;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 36, 40 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = chase;

	subtype = ENEMYTYPE::t_hinox;

	return ret;
}

void Hinox::SetRewards()
{
	reward_pool[heart_container] = 2;
	reward_pool[power_gauntlet] = 25;
	reward_pool[drop_rupee] = 35;
	reward_pool[drop_fiverupee] = 10;
	reward_pool[drop_tenrupee] = 5;
	reward_pool[drop_heart] = 23;
}

bool Hinox::Attack()
{
	bool ret = true;

	if (DmgType[melee] == true) {
		HitBox->rect = { (int)pos.x, (int)pos.y + 24, animations[curr_dir].GetCurrentFrame().w, animations[curr_dir].GetCurrentFrame().h - 24 };
	}

	if (App->player->link_coll != nullptr)
		if (this->HitBox->CheckCollision(App->player->link_coll->rect) == true) {
			HitPlayer();
		}


	return ret;
}
