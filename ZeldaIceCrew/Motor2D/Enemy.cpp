#include "Enemy.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Input.h"

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

void Enemy::Update(float dt)
{

	if (App->player->weapon_coll != nullptr)
		if (this->HitBox->CheckCollision(App->player->weapon_coll->rect) == true)
			Hit();
	
	if (App->player->action_blit != j1Player::Slash)
		hit = false;

	if (stats.Hp <= 0) {
		Death();
	}
	else {
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
		break;
	case AITYPE::distance:
		break;
	case AITYPE::no_move:
		break;
	}

	//App->pathfinding->CreatePath({ (int)pos.x, (int)pos.y }, target);
	//
	//path_to_follow = *App->pathfinding->GetLastPath();

	path_to_follow.push_back(target);

	if (App->debug_mode == true) {
		for (std::list<iPoint>::iterator it = path_to_follow.begin(); it != path_to_follow.end(); it++) {
			App->render->DrawQuad({it._Ptr->_Myval.x, it._Ptr->_Myval.y, App->map->data.tile_width, App->map->data.tile_height }, 255, 0, 0, 80);
		}
	}


		if (path_to_follow.size() > 0) {

			if (path_to_follow.begin()._Ptr->_Myval.x > pos.x)
				if(App->map->TileCheck(pos.x + rect.w + stats.Speed, pos.y, Down_R) == 0)
					pos.x += stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.x < pos.x)
				if (App->map->TileCheck(pos.x - stats.Speed, pos.y, Down_R) == 0)
					pos.x -= stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.y > pos.y)
				if (App->map->TileCheck(pos.x, pos.y + rect.h + stats.Speed, Down_R) == 0)
					pos.y += stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.y < pos.y)
				if (App->map->TileCheck(pos.x, pos.y - stats.Speed, Down_R) == 0)
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
		HitBox->rect = animations[curr_dir].GetCurrentFrame();
		HitBox->SetPos(pos.x, pos.y);
		rect = HitBox->rect;
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
	App->render->Blit(Entity::GetTexture(), pos.x, pos.y, &animations[curr_dir].GetCurrentFrame());
}

void Enemy::Hit()
{
	//stats.Hp -= App->player->power;
	if (hit == false) {
		
		stats.Hp -= App->player->power;
		
		switch (App->player->curr_dir) {
		case Up:
			if (App->map->TileCheck(pos.x, pos.y - JUMP_WHEN_HIT * App->map->data.tile_height, Direction::Up))
				pos.y += JUMP_WHEN_HIT * App->map->data.tile_height;
			break;
		case Down:
			if (App->map->TileCheck(pos.x, pos.y + JUMP_WHEN_HIT * App->map->data.tile_height, Direction::Down))
				pos.y -= JUMP_WHEN_HIT * App->map->data.tile_height;
			break;
		case Left:
			if (App->map->TileCheck(pos.x - JUMP_WHEN_HIT * App->map->data.tile_height, pos.y, Direction::Left))
				pos.x += JUMP_WHEN_HIT * App->map->data.tile_width;
			break;
		case Right:
			if (App->map->TileCheck(pos.x + JUMP_WHEN_HIT * App->map->data.tile_height, pos.y, Direction::Right))
				pos.x -= JUMP_WHEN_HIT * App->map->data.tile_width;
			break;
		}
		
		hit = true;
	}

}

void Enemy::Death()
{
	App->entitymanager->DestroyEnity(this);
}

bool BSoldier::Start()
{
	bool ret = true;

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

	HitBox = App->collisions->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = chase;

	subtype = ENEMYTYPE::BlueSoldier;

	return ret;
}
