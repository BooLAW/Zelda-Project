#include "Room.h"

void Room::Start()
{
	retro_enemies = App->tex->Load("Sprites/Enemies/EnemiesRetro.png");
	retro_items = App->tex->Load("Sprites/Items32x32Retro.png");
	enemies_nonretro = App->tex->Load("Sprites/Enemies/Enemies.png");
	items_nonretro = App->tex->Load("Sprites/Items32x32.png");
}

void Room::Update(float dt)
{

	for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
		if()
	}
		for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++) {
			if ((*it) != nullptr) {
				if (PlayerInside() == true) {
					enemies.empty() ? (*it)->state = DWSTATE::open : (*it)->state = DWSTATE::close;
				}
				else {
					App->audio->PlayFx(App->scene_manager->open_fx);
					(*it)->state = DWSTATE::open;
				}
			}
		}

		if (App->debug)
			App->render->DrawQuad(room_rect, 255, 0, 0, 10);

		active = PlayerInside();

		if (PlayerInside() == true && App->player->room != coords) {
			App->player->room = coords;
		}

		EnemyActive(active);

		if (doorways.empty() == false) {
			for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++)
			{
				if (it._Ptr->_Myval != nullptr) {
					it._Ptr->_Myval->Update(dt);
				}
			}
		}

		if (npcs.empty() == false) {
			for (std::list<Npc*>::iterator it = npcs.begin(); it != npcs.end(); it++)
			{
				if (!App->IsPaused()) {
					if (it._Ptr->_Myval->HitBox->CheckCollision(App->player->link_coll->rect) == 1) {
						App->player->toTalk = it._Ptr->_Myval;
					}
					else {
						it._Ptr->_Myval->Draw();
					}
				}
			}
		}
}

void Room::CleanUp()
{
	if (items.empty() == false) {
		for (std::list<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				parent->DestroyItem((*it));
		}
		items.clear();
	}
	if (enemies.empty() == false) {
		for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				parent->DestroyEnemy((*it));
		}
		enemies.clear();
	}

	if (blocks.empty() == false) {
		for (std::list<Block*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
			if (it._Ptr->_Myval != nullptr) {
				parent->DestroyBlock((*it));
			}
		}
		blocks.clear();
	}

	if (doorways.empty() == false) {
		for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr) {
				it._Ptr->_Myval->CleanUp();
				RELEASE(it._Ptr->_Myval);
			}
		}
		doorways.clear();
	}
}

bool Room::isInside(SDL_Rect r)
{
	if (r.x > room_rect.x && r.x < room_rect.x + room_rect.w)
		if (r.y > room_rect.y && r.y < room_rect.y + room_rect.h)
			return true;

	return false;
}

bool Room::NoEnemies()
{
	return enemies.empty();
}

bool Room::PlayerInside()
{
	return isInside(App->player->mov_coll->rect);
}

Item * Room::AddItem(uint subtype, float x, float y)
{
	Item* ret = nullptr;

	ret = App->entitymanager->CreateItem(subtype);
	ret->pos = { x + ROOM_W * coords.x, y + ROOM_H * coords.y};

	LOG("ITEM &d %d", ret->pos.x, ret->pos.y);

	ret->coords.x = coords.x;
	ret->coords.y = coords.y;

	items.push_back(ret);

	return ret;
}

Enemy * Room::AddEnemy(uint subtype, float x, float y)
{
	Enemy* ret = nullptr;

	ret = App->entitymanager->CreateEnemy(subtype);
	ret->room = { coords.x, coords.y };
	ret->pos = { x + coords.x * ROOM_W, y + coords.y * ROOM_H };

	enemies.push_back(ret);

	return ret;
}

Block * Room::AddBlock(uint subtype, float x, float y)
{
	Block* ret = nullptr;

	ret = App->entitymanager->CreateBlock(subtype);
	ret->pos = { x + ROOM_W * coords.x, y + ROOM_H * coords.y };

	blocks.push_back(ret);

	return ret;
}

Doorway * Room::AddDungeonDoorway(uint dir)
{
	return parent->AddDungeonDoorway(dir, coords.x, coords.y);
}

Doorway * Room::AddSceneDoorway(Scene* target, uint dir, float x, float y)
{
	return parent->AddSceneDoorway(target, coords.x, coords.y, dir, x, y);
}

Doorway * Room::AddCamDoorway(float target_x, float target_y, uint dir, float x, float y)
{
	return parent->AddCamDoorway(target_x, target_y, coords.x, coords.y, dir, x, y);
}

Npc * Room::AddNpc(NPC_TYPE type, float x, float y, int id)
{
	Npc* ret = nullptr;

	ret = App->entitymanager->CreateNPC(type,id);
	ret->pos = { x + coords.x * ROOM_W, y + coords.y * ROOM_H };

	ret->HitBox->SetPos((int)ret->pos.x, (int)ret->pos.y);

	npcs.push_back(ret);

	return ret;
}

void Room::EnemyActive(bool flag)
{
	for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
		it._Ptr->_Myval->active = flag;
	}
}

Scene * Room::GetParentScene()
{
	return parent;
}

void Room::SetParentScene(Scene * scene)
{
	parent = scene;
}
