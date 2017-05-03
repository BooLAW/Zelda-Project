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
	reward_pool[drop_rupee] = 10;
	reward_pool[drop_fiverupee] = 0;
	reward_pool[drop_tenrupee] = 0;

	//SortRewardProbs();

}

uint Enemy::GetPlayerDirection()
{
	uint dir = NULL;

	fPoint p = App->player->pos;

	if (p.x < pos.x && (p.y > pos.y - 32 && p.y < pos.y + 64))
		dir = Direction::Left;
	else if ((p.x > pos.x - 32 && p.x < pos.x + 64) && p.y > pos.y)
		dir = Direction::Down;
	else if ((p.x > pos.x - 32 && p.x < pos.x + 64) && p.y < pos.y)
		dir = Direction::Up;
	else if (p.x > pos.x && (p.y > pos.y - 32 && p.y < pos.y + 64))		
		dir = Direction::Right;
	else if (p.x < pos.x && p.y < pos.y)
		dir = Direction::Up_L;
	else if (p.x > pos.x && p.y > pos.y)
		dir = Direction::Down_R;
	else if (p.x < pos.x && p.y > pos.y)
		dir = Direction::Down_L;
	else if (p.x > pos.x && p.y < pos.y)
		dir = Direction::Up_R;

	return dir;
}

void Enemy::stdUpdate(float dt)
{
	//LOG("ENEMY POS: %f %f", pos.x, pos.y);
	//LOG("ENEMY UPDATE");
		if(HitBox->type == COLLIDER_ENEMY) {
			if (App->player->weapon_coll != nullptr)
				if (this->HitBox->CheckCollision(App->player->weapon_coll->rect) == true) {
					Hit(App->player->curr_dir, App->player->power);
					App->audio->PlayFx(hit_fx);
				}
		}

			if (App->player->action_blit != j1Player::Weapon_atk)
				hit = false;

				//if (App->debug_mode == false)
			Move();

			Attack();

			Draw();
	
}

bool Enemy::Move()
{
	bool ret = true;

	switch (AIType) {
	case AITYPE::path:
		break;
	case AITYPE::chase:
		target = { (int)App->player->link_coll->rect.x, (int)App->player->link_coll->rect.y - PL_OFFSET_Y / 2};
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

		if (path_to_follow.size() > 0 && AIType != no_move) {

			float diff_x, diff_y;
			float hip;
			float angle;

			diff_x =( path_to_follow.begin()._Ptr->_Myval.x - pos.x);
			diff_y = path_to_follow.begin()._Ptr->_Myval.y - pos.y;

			if (path_to_follow.begin()._Ptr->_Myval.x > pos.x) {
				diff_x = -diff_x;
				diff_y = -diff_y;
			}

			angle = (atan2(diff_y, diff_x));
			
			fPoint aux_s;

			if (path_to_follow.begin()._Ptr->_Myval.x >= pos.x) {
				aux_s = { -stats.Speed * (float)cos((double)angle), stats.Speed * (float)sin((double)angle) };
			}
			else
				aux_s = { stats.Speed * (float)cos((double)angle), -stats.Speed * (float)sin((double)angle) };

			if (stats.Flying == true || CheckSpace(HitBox->rect.x + aux_s.x, HitBox->rect.y + aux_s.y) == 0) {
				pos.x += aux_s.x;
				pos.y -= aux_s.y;
			}

			if (path_to_follow.begin()._Ptr->_Myval.x > (int)pos.x && path_to_follow.begin()._Ptr->_Myval.y == (int)pos.y)
				path_to_follow.pop_back();
		
		}

		if (AIType == chase)
			path_to_follow.clear();
	
		if (path_to_follow.empty() == false) {
			iPoint path_t = path_to_follow.begin()._Ptr->_Myval;
			if (path_t.y < pos.y && (path_t.x > pos.x - ENEMY_DIR_CHANGE_OFFSET && path_t.x < pos.x + ENEMY_DIR_CHANGE_OFFSET))
				curr_dir = Enemy::EnDirection::Up;
			else if (path_t.y > pos.y && (path_t.x > pos.x - ENEMY_DIR_CHANGE_OFFSET && path_t.x < pos.x + ENEMY_DIR_CHANGE_OFFSET))
				curr_dir = Enemy::EnDirection::Down;
			else if (path_t.x < pos.x)
				curr_dir = Enemy::EnDirection::Left;
			else if (path_t.x > pos.x)
				curr_dir = Enemy::EnDirection::Right;
		}
	return ret;
}

bool Enemy::Attack()
{
	bool ret = true;

	HitBox->SetPos(pos.x + animations[curr_dir].GetCurrentFrame().w / 6, pos.y + ENEMY_STD_OFFSET_Y);

	if (DmgType[melee] == true) {
	if (App->player->link_coll != nullptr)
		if (this->HitBox->CheckCollision(App->player->link_coll->rect) == true) {
			HitPlayer();
		}
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

void Enemy::HitPlayer(uint dmg)
{

	if (App->player->inmortal == false) {

		if (dmg != NULL)
			App->audio->PlayFx(App->player->hurt);

		App->player->curr_life_points -= dmg;

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

		if (dmg != NULL)
			App->player->PlayerInmortal(HIT_INM_TIME);
	}

}

void Enemy::SetAnimation(SDL_Rect spr[LastDir][2])
{
	for (int i = 0; i < EnDirection::LastDir; i++) {
		for (int k = 0; k < sizeof(spr) / sizeof(*spr); k++) {
			animations[i].PushBack(spr[i][k]);
		}
	}
}

void Enemy::Draw()
{
	SDL_Rect* draw_rect = &animations[curr_dir].GetCurrentFrame();
	fPoint aux_pos = { pos.x - 16, pos.y - 14 };

	App->render->toDraw(GetTexture(), HitBox->rect.y + HitBox->rect.h, aux_pos.x, aux_pos.y, draw_rect);
}

void Enemy::Hit(uint dir, uint dmg)
{


	if (hit == false) {
		
		hit = true;
		
		//LOG("HP: %d DMG: %d", stats.Hp, dmg);

		stats.Hp -= dmg;

		//LOG("HP: %d", stats.Hp, dmg);

		if (stats.Hp <= 0) {
			//LOG("ENEMY DEATH");
			Death();
			return;
		}

		switch (dir) {
		case Direction::Up:
			if (CheckSpace(pos.x, pos.y - jump_hit)==0)
				pos.y -= jump_hit;
			break;
		case Direction::Down:
			if (CheckSpace(pos.x, pos.y + jump_hit)==0)
				pos.y += jump_hit;
			break;
		case Direction::Left:
			if (CheckSpace(pos.x - jump_hit, pos.y)==0)
				pos.x -= jump_hit;
			break;
		case Direction::Right:
			if (CheckSpace(pos.x + jump_hit, pos.y)==0)
				pos.x += jump_hit;
			break;
		}
		
	}

}

void Enemy::Death()
{
	Reward();
	//LOG("ENEMY DEATH");
	App->scene_manager->GetCurrentScene()->DestroyEnemy(this);
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
	
		App->scene_manager->GetCurrentScene()->GetCurrentRoom()->AddItem(target, pos.x + HitBox->rect.w / 2 - 16, pos.y + +HitBox->rect.h / 2 - 16);

	}
	else {}
		//LOG("NO REWARD FAGGOT");

}


void Enemy::CleanUp()
{
	LOG("ENEMY CLEANUP %d", EnemyType);
	if (tex != nullptr)
		App->tex->UnLoad(tex);

	//LOG("TEX");

	if (HitBox != nullptr)
		HitBox->to_delete = true;

	//LOG("HB");

	path_to_follow.clear();

	//LOG("END ENEMY CP");

}

bool BSoldier::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Enemy::EnDirection::Down][0] = { 2, 219, 100, 108 };
		sprites[Enemy::EnDirection::Down][1] = { 104, 219, 100, 108 };

		sprites[Enemy::EnDirection::Up][0] = { 2, 329,  100, 108 };
		sprites[Enemy::EnDirection::Up][1] = { 104, 329, 100, 108 };

		sprites[Enemy::EnDirection::Left][0] = { 206, 439, 100, 108 };
		sprites[Enemy::EnDirection::Left][1] = { 308, 439, 100, 108 };

		sprites[Enemy::EnDirection::Right][0] = { 2, 439,  100, 108 };
		sprites[Enemy::EnDirection::Right][1] = { 104, 439, 100, 108 };

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
		sprites[Enemy::EnDirection::Down][0] = { 410, 219, 100,108 };
		sprites[Enemy::EnDirection::Down][1] = { 512, 219, 100,108 };

		sprites[Enemy::EnDirection::Up][0] = { 410, 329, 100, 108 };
		sprites[Enemy::EnDirection::Up][1] = { 512, 329, 100, 108 };

		sprites[Enemy::EnDirection::Left][0] = { 410, 439, 100, 108 };
		sprites[Enemy::EnDirection::Left][1] = { 512, 439, 100, 108 };

		sprites[Enemy::EnDirection::Right][0] = { 410, 549, 100, 108 };
		sprites[Enemy::EnDirection::Right][1] = { 512, 549, 100, 108 };

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
		sprites[Enemy::EnDirection::Down][0] = { 2, 0,  100, 108 };
		sprites[Enemy::EnDirection::Down][1] = { 104, 0, 100, 108 };

		sprites[Enemy::EnDirection::Up][0] = { 614, 0, 100, 108 };
		sprites[Enemy::EnDirection::Up][1] = { 716, 0, 100, 108 };

		sprites[Enemy::EnDirection::Left][0] = { 410, 0, 100, 108 };
		sprites[Enemy::EnDirection::Left][1] = { 512, 0, 100, 108 };

		sprites[Enemy::EnDirection::Right][0] = { 206, 0, 100, 108 };
		sprites[Enemy::EnDirection::Right][1] = { 308, 0, 100, 108 };

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
}

bool Hinox::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Enemy::EnDirection::Down][0] = { 614, 219, 100, 108 };
		sprites[Enemy::EnDirection::Down][1] = { 716, 219, 100, 108 };

		sprites[Enemy::EnDirection::Up][0] = { 614, 329, 100, 108 };
		sprites[Enemy::EnDirection::Up][1] = { 716, 329, 100, 108 };

		sprites[Enemy::EnDirection::Left][0] = { 614, 439, 100, 108 };
		sprites[Enemy::EnDirection::Left][1] = { 716, 439, 100, 108 };

		sprites[Enemy::EnDirection::Right][0] = { 614, 549, 100, 108 };
		sprites[Enemy::EnDirection::Right][1] = { 716, 549, 100, 108 };

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
};

bool Rope::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
	
		RopeSprites_m[Up][0] = { 2, 659, 100, 108 };
		RopeSprites_m[Up][1] = { 2, 659, 100, 108 };
		RopeSprites_m[Down][0] = { 2, 659, 100, 108 };
		RopeSprites_m[Down][1] = { 2, 659, 100, 108 };
		RopeSprites_m[Right][0] = { 206, 549, 100, 108};
		RopeSprites_m[Right][1] = { 206, 549, 100, 108};
		RopeSprites_m[Left][0] = { 104 , 549, 100, 108 };
		RopeSprites_m[Left][1] = { 104 , 549, 100, 108 };

		RopeSprites_nm[Up][0] =		{ 2, 549, 100, 108 };
		RopeSprites_nm[Down][0] =	{ 2, 549, 100, 108 };
		RopeSprites_nm[Right][0] =	{ 2, 549, 100, 108 };
		RopeSprites_nm[Left][0] =	{ 2, 549, 100, 108 };
		RopeSprites_nm[Up][1] =		{ 2, 659, 100, 108};
		RopeSprites_nm[Down][1] =	{ 2, 659, 100, 108};
		RopeSprites_nm[Right][1] =	{ 2, 659, 100, 108};
		RopeSprites_nm[Left][1] =	{ 2, 659, 100, 108};

		for (int i = 0; i < LastDir; i++) {
			for (int k = 0; k < 2; k++) {
				animations[i].PushBack(RopeSprites_m[i][k]);
			}
		}
		nm_anim.PushBack(RopeSprites_nm[0][0]);
		nm_anim.PushBack(RopeSprites_nm[0][1]);
		nm_anim.speed = 0.05;
	}

	stats.Hp = 1;
	stats.Speed = 5;
	stats.Power = 1;

	stats.Flying = false;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = 0.02; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 24, 32 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	state = no_move;

	DmgType[melee] = true;

	AIType = path;

	subtype = ENEMYTYPE::t_rope;

	return ret;
}

void Rope::Update(float dt)
{
	aux_pos = pos;

	stdUpdate(dt);

	uint dir;

	switch (state) {
	case no_move:
		walk_timer.Start();
		walk_timer.SetFlag(true);
		if (walk_timer.ReadSec() >= 1) {
			target.x = (int)pos.x;
			target.y = (int)pos.y;
			dir = rand() % EnDirection::LastDir;
			switch (dir) {
			case EnDirection::Up:
				target.y += 32 * ROPE_JMP;
				break;
			case EnDirection::Down:
				target.y -= 32 * ROPE_JMP;
				break;
			case EnDirection::Left:
				target.x -= 32 * ROPE_JMP;
				break;
			case EnDirection::Right:
				target.x += 32 * ROPE_JMP;
				break;
			}
			LOG("ROPE DIR %d", dir);
			path_to_follow.push_back(target);
			walk_timer.SetFlag(false);
			state = moving;
		}
		break;
	case moving:
		walk_timer.Start();
		walk_timer.SetFlag(true);
		if (walk_timer.ReadSec() >= 1) {
			walk_timer.SetFlag(false);
			path_to_follow.clear();
			state = no_move;
		}

		break;
	}

}

void Rope::Draw()
{
	SDL_Rect* draw_rect;

	if (aux_pos == pos)
		draw_rect = &nm_anim.GetCurrentFrame();
	else
	draw_rect = &animations[curr_dir].GetCurrentFrame();
	
	fPoint draw_pos = pos;

	draw_pos.x -= 24;
	draw_pos.y -= 16;

	App->render->toDraw(GetTexture(), HitBox->rect.y + HitBox->rect.h, draw_pos.x, draw_pos.y, draw_rect);

}

bool BlueArcher::Start()
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
	stats.Speed = 2;
	stats.Power = 1;

	stats.Flying = false;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 24, 32 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[projectile] = true;

	AIType = distance;

	state = moving;

	subtype = ENEMYTYPE::t_bluearcher;

	return ret;
}

void BlueArcher::Update(float dt)
{
	stdUpdate(dt);

	shoot_time.Start();
	shoot_time.SetFlag(true);

	fPoint pl_pos = App->player->GetPos();
	pl_pos.y -= PL_OFFSET_Y / 2;

	//target.x = (int)pl_pos.x;
	//target.y = (int)pl_pos.y;

	switch (state) {
	case moving:
		react_time.Start();
		react_time.SetFlag(true);
		target.x = pl_pos.x;
		target.y = pl_pos.y;
		if (std::abs(pos.x - pl_pos.x) >= std::abs(pos.y - pl_pos.y)) {
			if (pos.x < pl_pos.x) {
				target.x = pl_pos.x - range * TILE_S;
			}
			if (pos.x > pl_pos.x) {
				target.x = pl_pos.x + range * TILE_S;
			}
		}
		else {
			if (pos.y < pl_pos.y) {
				target.x = pl_pos.x - range * TILE_S;
			}
			if (pos.y > pl_pos.y) {
				target.y = pl_pos.y + range * TILE_S;
			}
		}
		if (react_time.Read() >= 1000) {
			react_time.SetFlag(false);
			path_to_follow.clear();
			path_to_follow.push_back(target);
		}

		if ((pos.x > pl_pos.x - 8 && pos.x < pl_pos.x + 8) || (pos.y > pl_pos.y - 8 && pos.y < pl_pos.y + 8))
			state = shoot;

		break;
		state = shoot;

	case shoot:
		path_to_follow.clear();
		if (pl_pos.y < pos.y && (pl_pos.x > pos.x - ENEMY_DIR_CHANGE_OFFSET && pl_pos.x < pos.x + ENEMY_DIR_CHANGE_OFFSET))
			curr_dir = Enemy::EnDirection::Up;
		else if (pl_pos.y > pos.y && (pl_pos.x > pos.x - ENEMY_DIR_CHANGE_OFFSET && pl_pos.x < pos.x + ENEMY_DIR_CHANGE_OFFSET))
			curr_dir = Enemy::EnDirection::Down;
		else if (pl_pos.x < pos.x)
			curr_dir = Enemy::EnDirection::Left;
		else if (pl_pos.x > pos.x)
			curr_dir = Enemy::EnDirection::Right;
		
		if (shoot_time.Read() >= 1000) {
			App->particle->CreateParticle(p_enarrow, pos.x + 8, pos.y + 16, App->entitymanager->fromEntoPlDir(curr_dir));
			shoot_time.SetFlag(false);
		}

		state = moving;
		
		break;
	}

}

void BlueArcher::Draw()
{

	SDL_Rect* draw_rect = &animations[curr_dir].GetCurrentFrame();
	fPoint aux_pos = pos;
	
	App->render->toDraw(GetTexture(), HitBox->rect.y + HitBox->rect.h, aux_pos.x, aux_pos.y, draw_rect);

}

bool GreyBat::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Enemy::EnDirection::Down][0] = { 104, 659, 100, 108 };
		sprites[Enemy::EnDirection::Down][1] = { 206, 659, 100, 108 };
		sprites[Enemy::EnDirection::Down][2] = { 308, 659, 100, 108 };
		sprites[Enemy::EnDirection::Down][3] = { 410, 659, 100, 108 };
		sprites[Enemy::EnDirection::Down][4] = { 512, 659, 100, 108 };

		for (int i = 0; i < LastDir; i++) {
			for (int k = 0; k < 4; k++)
				animations[i].PushBack(sprites[Down][k]);
		}
	}

	stats.Hp = 1;
	stats.Speed = 2.5;
	stats.Power = 1;

	stats.Flying = true;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 36, 32 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;
	AIType = chase;

	subtype = ENEMYTYPE::t_GBat;

	return ret;
}

bool Geldman::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		appear_sprites[0] = { 104, 659, 100, 108 };
		appear_sprites[1] = { 410, 659, 100, 108 };
		appear_sprites[2] = { 410, 659, 1, 1 };

		move_sprites[0] = { 206, 659, 100, 108 };
		move_sprites[1] = { 308, 659, 100, 108 };

		for (int i = 0; i < 3; i++) {
			disappear_anim.PushBack(appear_sprites[1 - i]);
			if (i < 2) {
				appear_anim.PushBack(appear_sprites[i]);
				move_anim.PushBack(move_sprites[i]);
			}
		}
		appear_anim.speed = 0.07;
		appear_anim.loop = false;
		disappear_anim.speed = 0.1;
		disappear_anim.loop = false;
		move_anim.speed = 0.05;
	}

	stats.Hp = 3;
	stats.Speed = 2;
	stats.Power = 1;

	stats.Flying = false;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 48, 32 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = path;

	subtype = ENEMYTYPE::t_geldman;

	return ret;
}

void Geldman::Draw()
{

	fPoint aux_pos = pos;

	aux_pos.y = pos.y - 20;
	aux_pos.x = pos.x - 26;

	Animation* animation_aux = &move_anim;

	switch (state) {
	case move:
		animation_aux = &move_anim;
		break;
	case appear:
		animation_aux = &appear_anim;
		break;
	case disappear:
		animation_aux = &disappear_anim;
		break;
	}
	
	if(state == move || state == appear || state == disappear)
	App->render->toDraw(tex, HitBox->rect.y + HitBox->rect.h, aux_pos.x, aux_pos.y, &animation_aux->GetCurrentFrame());
}

void Geldman::Update(float dt)
{

	int aux_hp = stats.Hp;

	SDL_Rect c_r = App->scene_manager->GetCurrentScene()->GetCurrentRoom()->room_rect;

	fPoint app_pos;

	fPoint p_pos = App->player->pos;

	SDL_Rect p_rect;
	SDL_Rect en_rect = { 0, 0, 250, 250 };

	switch (state) {
	case appear_start:
		appear_anim.Reset();
		app_pos.x = rand() % en_rect.w + (int)(p_pos.x - en_rect.w /2);
		app_pos.y = rand() % en_rect.h + (int)(p_pos.y - en_rect.h /2);
		LOG("APPEAR POS: %f %f", app_pos.x, app_pos.y);
		if (!(CheckSpace(app_pos.x, app_pos.y) != 0 || App->scene_manager->GetCurrentScene()->GetCurrentRoom()->isInside({ (int)app_pos.x, (int)app_pos.y, 0, 0 }) == false)) {
			SDL_Rect en_aux = { app_pos.x, app_pos.y, 1, 1 };
			p_rect = {(int)p_pos.x - 100, (int)p_pos.y - 100, 132, 148 };
			if (CheckIntersec(en_aux, p_rect) == false) {
				pos = app_pos;
				state = appear;
			}
		}
		break;
	case appear:
		move_time.Start();
		move_time.SetFlag(true);
		if (move_time.Read() >= 700) {
			state = move;
			move_time.SetFlag(false);
		}
		break;
	case move:
		move_time.Start();
		move_time.SetFlag(true);
		AIType = chase;
		if (move_time.Read() >= time_moving) {
			state = disappear_start;
			move_time.SetFlag(false);
		}
		break;
	case disappear_start:
		disappear_anim.Reset();
		state = disappear;
		break;
	case disappear:
		move_time.Start();
		move_time.SetFlag(true);
		AIType = no_move;
		path_to_follow.clear();
		if (move_time.Read() >= 3000) {
			state = appear_start;
			move_time.SetFlag(false);
		}
		break;
	}

	stdUpdate(dt);

	if (state != move) {
		HitBox->SetPos(-9999, -9999);
		DmgType[melee] = 0;
		DmgType[none] = 1;
	}
	else {
		DmgType[melee] = 1;
		DmgType[none] = 0;
	}

	if (aux_hp > stats.Hp)
		state = disappear_start;

}

bool Freezor::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		appear_sprites[0] = { 104, 659, 100, 108 };
		appear_sprites[1] = { 410, 659, 100, 108 };
		appear_sprites[2] = { 410, 659, 1, 1 };

		attack_sprites[0] = { 206, 659, 100, 108 };
		attack_sprites[1] = { 308, 659, 100, 108 };

		for (int i = 0; i < 3; i++) {
			disappear_anim.PushBack(appear_sprites[1 - i]);
			if (i < 2) {
				appear_anim.PushBack(appear_sprites[i]);
				attack_anim.PushBack(attack_sprites[i]);
			}
		}
		appear_anim.speed = 0.07;
		appear_anim.loop = false;
		disappear_anim.speed = 0.1;
		disappear_anim.loop = false;
		attack_anim.speed = 0.05;
	}

	stats.Hp = 3;
	stats.Speed = 2;
	stats.Power = 1;

	stats.Flying = false;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 48, 32 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[projectile] = true;

	AIType = no_move;

	subtype = ENEMYTYPE::t_freezor;

	return ret;

}

void Freezor::Draw()
{
	fPoint aux_pos = pos;

	aux_pos.y = pos.y - 20;
	aux_pos.x = pos.x - 26;

	Animation* animation_aux = &attack_anim;

	switch (state) {
	case attack:
		animation_aux = &attack_anim;
		break;
	case appear:
		animation_aux = &appear_anim;
		break;
	case disappear:
		animation_aux = &disappear_anim;
		break;
	}

	if (state == attack || state == appear || state == disappear)
		App->render->toDraw(tex, HitBox->rect.y + HitBox->rect.h, aux_pos.x, aux_pos.y, &animation_aux->GetCurrentFrame());

}

void Freezor::Update(float dt)
{
	int aux_hp = stats.Hp;

	SDL_Rect c_r = App->scene_manager->GetCurrentScene()->GetCurrentRoom()->room_rect;

	fPoint app_pos;

	fPoint p_pos = App->player->pos;

	SDL_Rect p_rect;
	SDL_Rect en_rect = { 0, 0, 500, 500 };

	switch (state) {
	case appear_start:
		appear_anim.Reset();
		app_pos.x = rand() % en_rect.w + (int)(p_pos.x - en_rect.w / 2);
		app_pos.y = rand() % en_rect.h + (int)(p_pos.y - en_rect.h / 2);
		LOG("APPEAR POS: %f %f", app_pos.x, app_pos.y);
		if (!(CheckSpace(app_pos.x, app_pos.y) != 0 || App->scene_manager->GetCurrentScene()->GetCurrentRoom()->isInside({ (int)app_pos.x, (int)app_pos.y, 0, 0 }) == false)) {
			SDL_Rect en_aux = { app_pos.x, app_pos.y, 1, 1 };
			p_rect = { (int)p_pos.x - 100, (int)p_pos.y - 100, 132, 148 };
			if (CheckIntersec(en_aux, p_rect) == false) {
				pos = app_pos;
				state = appear;
			}
		}
		break;
	case appear:
		timer.Start();
		timer.SetFlag(true);
		if (timer.Read() >= 700) {
			state = attack;
			timer.SetFlag(false);
		}
		break;
	case attack:
		timer.Start();
		timer.SetFlag(true);
		attack_timer.Start();
		attack_timer.SetFlag(true);
		if (attack_timer.Read() >= 1000) {
			App->particle->CreateParticle(p_shadow, HitBox->rect.x, HitBox->rect.y, curr_dir);
			attack_timer.SetFlag(false);
		}
		if (timer.Read() >= time_attack) {
			state = disappear_start;
			timer.SetFlag(false);
		}
		break;
	case disappear_start:
		disappear_anim.Reset();
		state = disappear;
		break;
	case disappear:
		timer.Start();
		timer.SetFlag(true);
		path_to_follow.clear();
		if (timer.Read() >= 3000) {
			state = appear_start;
			timer.SetFlag(false);
		}
		break;
	}


	target.x = App->player->link_coll->rect.x;
	target.y = App->player->link_coll->rect.y;
	path_to_follow.clear();
	path_to_follow.push_back(target);
	stdUpdate(dt);

	if (state != attack) {
		HitBox->SetPos(-9999, -9999);
		DmgType[projectile] = 0;
		DmgType[none] = 1;
	}
	else {
		DmgType[projectile] = 1;
		DmgType[none] = 0;
	}

	if (aux_hp > stats.Hp)
		state = disappear_start;
}

bool Beamos::Start()
{
	bool ret = true;

	SetRewards();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		beamos_sprites[Direction::Right] =	{ 410, 985, 100, 108 };
		beamos_sprites[Direction::Up_R] =	{ 104, 985, 100, 108 };
		beamos_sprites[Direction::Up] =		{ 2  , 985, 100, 108 };
		beamos_sprites[Direction::Up_L] =	{ 410, 879, 100, 104 };
		beamos_sprites[Direction::Left] =	{ 104, 879, 100, 104 };
		beamos_sprites[Direction::Down_L] =	{ 614, 1095, 100, 108 };
		beamos_sprites[Direction::Down] =	{ 410, 1095, 100, 108 };
		beamos_sprites[Direction::Down_R] =	{ 206, 1095, 100, 108 };

	}

	stats.Hp = 1;
	stats.Speed = 2;
	stats.Power = 1;

	stats.Flying = false;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 24, 24 }, COLLIDER_DMG_BY_BB);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[projectile] = true;

	AIType = no_move;

	state = search;

	subtype = ENEMYTYPE::t_beamos;

	return ret;
}

void Beamos::Draw()
{
	fPoint aux_pos = pos;
	SDL_Rect* r_aux = nullptr;

	aux_pos.y = pos.y;
	aux_pos.x = pos.x - 40;

	r_aux = &beamos_sprites[GetPlayerDirection()];

	//fPoint p_pos = App->player->pos;
	//float angle = 0;
	//fPoint diff = { p_pos.x + 16 - (pos.x),  (p_pos.y + 16 - (pos.y)) };
	//fPoint origin = { 2, 0.5 };
	////if (p_pos.x > pos.x) {
	////	diff_x = -diff_x;
	////	diff_y = -diff_y;
	////}
	//
	//float dotp = diff.x*origin.x + diff.y*origin.y;
	//float det = diff.x*origin.y - diff.y*origin.x;
	//
	//angle = std::abs(atan2(det, dotp));
	//
	//if (p_pos.y > pos.y + 16)
	//	angle = DegtoRad(180) + (DegtoRad(180) - angle);
	//
	//float num = RadtoDeg(angle);
	//
	//if (num < 0) {
	//	//num = std::abs(num);
	//}
	//
	//LOG("ANGLE %f", num);
	//
	//r_aux = &beamos_sprites[(int)floor(num/15)];
	//
	//if(r_aux != nullptr)
		App->render->toDraw(tex, HitBox->rect.y + HitBox->rect.h, aux_pos.x, aux_pos.y, r_aux);

}

void Beamos::Update(float dt)
{
	stdUpdate(dt);

	switch (state) {
	case search:
		timer.Start();
		timer.SetFlag(true);
		if (timer.Read() >= 1500) {
			state = shooting;
			App->particle->CreateParticle(p_bounceback, pos.x, pos.y, curr_dir);
			timer.SetFlag(false);
		}
		break;
	case shooting:
		timer.Start();
		timer.SetFlag(true);
		if (timer.Read() >= 500) {
			state = search;
			timer.SetFlag(true);
		}
		break;
	}

}

bool BossAgahnim::Start()
{
	bool ret = true;

	SetReward();

	curr_dir = Enemy::EnDirection::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Bosses.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		appear_sprites[0] = { 104, 659, 100, 108 };
		appear_sprites[1] = { 410, 659, 100, 108 };
		appear_sprites[2] = { 410, 659, 1, 1 };

		attack_sprites[0] = { 206, 659, 100, 108 };
		attack_sprites[1] = { 308, 659, 100, 108 };

		for (int i = 0; i < 3; i++) {
			disappear_anim.PushBack(appear_sprites[1 - i]);
			if (i < 2) {
				appear_anim.PushBack(appear_sprites[i]);
				attack_anim.PushBack(attack_sprites[i]);
			}
		}
		appear_anim.speed = 0.07;
		appear_anim.loop = false;
		disappear_anim.speed = 0.1;
		disappear_anim.loop = false;
		attack_anim.speed = 0.05;
	}

	stats.Hp = 12;
	stats.Speed = 1;
	stats.Power = 2;

	stats.Flying = false;

	for (int i = 0; i < Enemy::EnDirection::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 48, 32 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[projectile] = true;

	AIType = special;

	subtype = ENEMYTYPE::t_boss_agahnim;

	return ret;
}

void BossAgahnim::SetReward()
{
	reward_pool[heart_container] = 100;
}

void BossAgahnim::Draw()
{
	int aux_hp = stats.Hp;
	SDL_Rect c_r = App->scene_manager->GetCurrentScene()->GetCurrentRoom()->room_rect;
	fPoint app_pos;
	fPoint p_pos = App->player->pos;

	SDL_Rect p_rect;
	SDL_Rect en_rect = { 0,0,500,500 };

	switch(state)
	{
	case appear_start:
		appear_anim.Reset();
		app_pos.x = rand() % en_rect.w + (int)(p_pos.x - en_rect.w / 2);
		app_pos.x = rand() % en_rect.h + (int)(p_pos.y - en_rect.h / 2);
		
		if (!(CheckSpace(app_pos.x, app_pos.y) != 0 || App->scene_manager->GetCurrentScene()->GetCurrentRoom()->isInside({ (int)app_pos.x, (int)app_pos.y, 0, 0 }) == false))
		{
			SDL_Rect en_aux = { app_pos.x,app_pos.y,1,1 };
			p_rect = { (int)p_pos.x - 100, (int)p_pos.y - 100, 132, 148 };
			if (CheckIntersec(en_aux, p_rect) == false) {
				pos = app_pos;
				state = appear;
			}
		}
		break;
	case appear:
		timer.Start();
		timer.SetFlag(true);
		if (timer.Read() >= 700) {
			state = attack;
			timer.SetFlag(false);
		}
		break;
	case attack:
		timer.Start();
		timer.SetFlag(true);
		attack_timer.Start();
		attack_timer.SetFlag(true);
		if (attack_timer.Read() >= 1000) {
			App->particle->CreateParticle(p_shadow, HitBox->rect.x, HitBox->rect.y, curr_dir);
			attack_timer.SetFlag(false);
		}
		if (timer.Read() >= time_attack) {
			state = disappear_start;
			timer.SetFlag(false);
		}
		break;
	case hit:
		timer.Start();
		timer.SetFlag(true);
		attack_timer.Start();
		attack_timer.SetFlag(true);
		if (attack_timer.Read() >= 1000) {
			App->particle->CreateParticle(p_shadow, HitBox->rect.x, HitBox->rect.y, curr_dir);
			attack_timer.SetFlag(false);
		}
		if (timer.Read() >= time_attack) {
			state = disappear_start;
			timer.SetFlag(false);
		}
		break;
	case disappear:
		timer.Start();
		timer.SetFlag(true);
		path_to_follow.clear();
		if (timer.Read() >= 3000) {
			state = appear_start;
			timer.SetFlag(false);
		}
		break;
	case disappear_start:
		disappear_anim.Reset();
		state = disappear;
		break;
	}
}
