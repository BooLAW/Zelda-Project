#include "Enemy.h"
#include "j1Pathfinding.h"
#include "j1Map.h"

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
	Move();

	Attack();

	Draw();
}

bool Enemy::Move()
{
	bool ret = true;

	fPoint aux_pos = pos;

	iPoint target;

	switch (AIType) {
	case AITYPE::path:	
		target = { (int)App->player->GetPos().x, (int)App->player->GetPos().y };
		break;
	case AITYPE::chase:
		break;
	case AITYPE::distance:
		break;
	case AITYPE::no_move:
		break;
	}

	App->pathfinding->CreatePath({ (int)pos.x, (int)pos.y }, target);

	path_to_follow = *App->pathfinding->GetLastPath();

	if (App->debug_mode == true) {
		for (std::list<iPoint>::iterator it = path_to_follow.begin(); it != path_to_follow.end(); it++) {
			App->render->DrawQuad({it._Ptr->_Myval.x, it._Ptr->_Myval.y, App->map->data.tile_width, App->map->data.tile_height }, 255, 0, 0, 80);
		}
	}

		if (path_to_follow.size() > 0) {

			if (path_to_follow.begin()._Ptr->_Myval.x > pos.x)
				pos.x += stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.x < pos.x)
				pos.x -= stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.y > pos.y)
				pos.y += stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.y < pos.y)
				pos.y -= stats.Speed;
			if (path_to_follow.begin()._Ptr->_Myval.x == (int)pos.x && path_to_follow.begin()._Ptr->_Myval.y == (int)pos.y)
				path_to_follow.pop_back();
		}
	

	if (aux_pos.x > pos.x)
		curr_dir = Enemy::Direction::Left;
	else if (aux_pos.x < pos.x)
		curr_dir = Enemy::Direction::Right;
	else if (aux_pos.y > pos.y)
		curr_dir = Enemy::Direction::Down;
	else if (aux_pos.y < pos.y)
		curr_dir = Enemy::Direction::Up;

	return ret;
}

bool Enemy::Attack()
{
	bool ret = true;

	if (DmgType[melee] == true) {
		HitBox->rect = animations[curr_dir].GetCurrentFrame();
		HitBox->SetPos(pos.x, pos.y);
	}

	return ret;
}

void Enemy::Draw()
{
	App->render->Blit(Entity::GetTexture(), pos.x, pos.y, &animations[curr_dir].GetCurrentFrame());
}

bool BSoldier::Start()
{
	bool ret = true;

	curr_dir = Enemy::Direction::Down;

	Entity::SetTexture(App->tex->Load("Sprites/Enemies/Enemies.png"));

	// All Animation Settup (you don't want to look into that, trust me :s)
	{
		sprites[Enemy::Direction::Down][0] = { 30, 251, 44, 68 };
		sprites[Enemy::Direction::Down][1] = { 132, 249, 44, 70 };

		sprites[Enemy::Direction::Up][0] = { 30, 357, 44, 52 };
		sprites[Enemy::Direction::Up][1] = { 132, 357, 44, 52 };

		sprites[Enemy::Direction::Left][0] = { 214, 465, 64, 54 };
		sprites[Enemy::Direction::Left][1] = { 316, 465, 64, 54 };

		sprites[Enemy::Direction::Right][0] = { 30, 465, 64, 54 };
		sprites[Enemy::Direction::Right][1] = { 132, 465, 64, 54 };

		animations[Enemy::Direction::Down].PushBack(sprites[Down][0]);
		animations[Enemy::Direction::Down].PushBack(sprites[Down][1]);

		animations[Enemy::Direction::Up].PushBack(sprites[Up][0]);
		animations[Enemy::Direction::Up].PushBack(sprites[Up][1]);

		animations[Enemy::Direction::Left].PushBack(sprites[Left][0]);
		animations[Enemy::Direction::Left].PushBack(sprites[Left][1]);

		animations[Enemy::Direction::Right].PushBack(sprites[Right][0]);
		animations[Enemy::Direction::Right].PushBack(sprites[Right][1]);


	}

	stats.Hp = 3;
	stats.Speed = 1.5;
	stats.Power = 1;

	stats.Flying = false;

	for (int i = 0; i < Enemy::Direction::LastDir; i++)
		animations[i].speed = stats.Speed * ENEMY_SPRITES_PER_SPD; // All Enemy Animation.Speed's must be Subtype::stats.speed * 0.5

	HitBox = App->collisions->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY);

	memset(DmgType, false, __LAST_DMGTYPE);

	DmgType[melee] = true;

	AIType = path;

	subtype = ENEMYTYPE::BlueSoldier;

	return ret;
}
