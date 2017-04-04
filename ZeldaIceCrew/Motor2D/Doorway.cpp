#include "Doorway.h"
#include "j1Player.h"
#include "Entity.h"
#include "VillageScene.h"
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
	LOG("DOORWAY POS: %d %d", pos.x, pos.y);

	collider->SetPos(pos.x, pos.y);

	if (collider->CheckCollision(App->player->link_coll->rect) == true)
		Cross();
};

bool DwDungeon::Cross()
{
	switch (direction) {
	case Direction::Up:
		App->render->camera.y -= -ROOM_H;
		App->player->MovePos(0, -ROOM_CHANGE_Y);
		break;
	case Direction::Down:
		App->render->camera.y += -ROOM_H;
		App->player->MovePos(0, ROOM_CHANGE_Y);
		break;
	case Direction::Left:
		App->render->camera.x += ROOM_W;
		App->player->MovePos(-ROOM_CHANGE_X, 0);
		break;
	case Direction::Right:
		App->render->camera.x -= ROOM_W;
		App->player->MovePos(ROOM_CHANGE_X, 0);
		break;
	}
	return true;
}
bool DwHouse::Cross()
{
	App->scene_manager->ChangeScene(App->scene_manager->village_scene);
	App->player->MovePos(-235, 1165);
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

void Doorway::CleanUp()
{
	if(collider != nullptr)
		collider->to_delete = true;
};
