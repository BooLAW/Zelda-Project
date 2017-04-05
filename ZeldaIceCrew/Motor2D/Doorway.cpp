#include "Doorway.h"
#include "j1Player.h"
#include "Entity.h"
#include "VillageScene.h"
#include "DungeonScene.h"
#include "HouseScene.h"
#include "ShopScene.h"
void Doorway::Start()
{
	open = true;
	collider = App->collisions->AddCollider({ 0, 0, 0, 0 }, COLLIDER_DUNGEON_DOORWAY);
	this->tex = nullptr;
	this->type = doorway;

}
void Doorway::SetUp(uint dir)
{
	direction = dir;

	switch (direction) {
	case Direction::Up:
		collider->rect = { (int)pos.x, (int)pos.y, DOORWAY_SIZE.x, DOORWAY_SIZE.y };
		break;
	case Direction::Down:
		collider->rect = { (int)pos.x, (int)pos.y, DOORWAY_SIZE.x, DOORWAY_SIZE.y };
		break;
	case Direction::Left:
		collider->rect = { (int)pos.x, (int)pos.y, DOORWAY_SIZE.y, DOORWAY_SIZE.x };
		break;
	case Direction::Right:
		collider->rect = { (int)pos.x, (int)pos.y, DOORWAY_SIZE.y, DOORWAY_SIZE.x };
		break;
	default:
		LOG("Unknown DOORWAY Direction Id: %d", direction);
		break;
	}
}
void Doorway::Update(float dt)
{
	collider->SetPos(pos.x, pos.y);

	if(App->player->link_coll != nullptr)
	if (collider->CheckCollision(App->player->link_coll->rect) == true)
		Cross();
};

bool DwDungeon::Cross()
{
	switch (direction) {
	case Direction::Up:
		App->player->room.y--;
		App->player->pos = { (float)ROOM_W / 2 + App->player->room.x * ROOM_W,  (float)(ROOM_H - 125) + (App->player->room.y) * ROOM_H };
		break;
	case Direction::Down:
		App->player->room.y++;
		App->player->pos = { (float)ROOM_W / 2 + App->player->room.x * ROOM_W,  (float)(125) + (App->player->room.y) * ROOM_H };
		break;
	case Direction::Left:
		App->player->room.x--;
		App->player->pos = { (float)ROOM_W - 125 + App->player->room.x * ROOM_W,  (float)(ROOM_H / 2) + (App->player->room.y) * ROOM_H };
		break;
	case Direction::Right:
		App->player->room.x++;
		App->player->pos = { (float)100 + App->player->room.x * ROOM_W,  (float)(ROOM_H / 2) + (App->player->room.y) * ROOM_H };
		break;
	}

	LOG("PLAYER CROSS");
	LOG("PLAYER ROOM: %d %d", App->player->room.x, App->player->room.y);

	return true;
}
bool DwOverworld::Cross()
{
	switch (direction) {
	case Direction::Up:
		//go to dungeon
		App->scene_manager->ChangeScene(App->scene_manager->dungeon_scene);
		App->player->MovePos(80, 80);
		break;
	case Direction::Down:
		//go to house
		App->scene_manager->ChangeScene(App->scene_manager->house_scene);
		App->player->MovePos(10, 10);
		break;
	case Direction::Left:
		//nothing in  the demo
		break;
	case Direction::Right:
		//go shop
		App->scene_manager->ChangeScene(App->scene_manager->shop_scene);
		App->player->MovePos(10, 10);
		break;
	}
	return true;
}
bool DwHouse::Cross()
{
	App->scene_manager->ChangeScene(App->scene_manager->village_scene);
	App->player->MovePos(-235, 1290);
	return true;
}
bool DwShop::Cross()
{
	App->scene_manager->ChangeScene(App->scene_manager->village_scene);
	App->player->MovePos(265, 350);
	return true;
}
void DwDungeon::SetRoomPos(int x, int y)
{
	switch (direction) {
	case Direction::Up:
		pos = { (float)DOORWAY_UP.x + ROOM_W * x, (float)DOORWAY_UP.y + ROOM_H * y };
		break;
	case Direction::Down:
		pos = { (float)DOORWAY_DOWN.x + ROOM_W * x, (float)DOORWAY_DOWN.y + ROOM_H * y };
		break;
	case Direction::Left:
		pos = { (float)DOORWAY_LEFT.x + ROOM_W * x, (float)DOORWAY_LEFT.y + ROOM_H * y };
		break;
	case Direction::Right:
		pos = { (float)DOORWAY_RIGHT.x + ROOM_W * x, (float)DOORWAY_RIGHT.y + ROOM_H * y };
		break;
	}
};
void DwHouse::SetRoomPos(int x, int y)
{
	pos = { (float) x, (float) y };

};
void DwShop::SetRoomPos(int x, int y)
{
	pos = { (float)x, (float)y };

};
void DwOverworld::SetRoomPos(int x, int y)
{
	pos = { (float)x, (float)y };

};
void Doorway::CleanUp()
{
	if(collider != nullptr)
		collider->to_delete = true;
};
