#include "Doorway.h"
#include "j1Player.h"
#include "Entity.h"
#include "VillageScene.h"
#include "DungeonScene.h"
#include "j1Input.h"
void Doorway::Start()
{
	tex = App->tex->Load("Sprites/Door.png");
	crossed = false;
	state = open;
	collider = App->collisions->AddCollider({ 0, 0, 0, 0 }, COLLIDER_DUNGEON_DOORWAY);
	SetUp();
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
		//LOG("Unknown DOORWAY Direction Id: %d", direction);
		break;
	}
}
void Doorway::Update(float dt)
{

	//LOG("DOORWAY UPDATE");

	collider->SetPos(pos.x, pos.y);

		bool crossing = false;

		if (App->player->link_coll != nullptr)
			if (collider->CheckCollision(App->player->link_coll->rect) == true) {
				switch (direction) {
				case Up:
					if (App->input->GetKey(SDL_SCANCODE_W))
						crossing = true;
					break;
				case Down:
					if (App->input->GetKey(SDL_SCANCODE_S))
						crossing = true;
					break;
				case Left:
					if (App->input->GetKey(SDL_SCANCODE_A))
						crossing = true;
					break;
				case Right:
					if (App->input->GetKey(SDL_SCANCODE_D))
						crossing = true;
					break;
				}
			}
		if (crossing == true && state == open) {
			Cross();
			crossed = true;
		}

		Draw();

		//LOG("END DOORWAY UPDT");
};

bool DwDungeon::Cross()
{
	switch (direction) {
	case Direction::Up:
		App->player->room.y--;
		target_pos = { (float)ROOM_W / 2 + App->player->room.x * ROOM_W,  (float)(ROOM_H - 125) + (App->player->room.y) * ROOM_H };
		break;
	case Direction::Down:
		App->player->room.y++;
		target_pos = { (float)ROOM_W / 2 + App->player->room.x * ROOM_W,  (float)(125) + (App->player->room.y) * ROOM_H };
		break;
	case Direction::Left:
		App->player->room.x--;
		target_pos = { (float)ROOM_W - 125 + App->player->room.x * ROOM_W,  (float)(ROOM_H / 2) + (App->player->room.y) * ROOM_H };
		break;
	case Direction::Right:
		App->player->room.x++;
		target_pos = { (float)100 + App->player->room.x * ROOM_W,  (float)(ROOM_H / 2) + (App->player->room.y) * ROOM_H };
		break;
	}

	App->player->pos = target_pos;

	//LOG("PLAYER CROSS");
	//LOG("PLAYER ROOM: %d %d", App->player->room.x, App->player->room.y);

	return true;
}

void DwDungeon::SetUp()
{
	sprite[Up][open] = { 0, 0, 0, 0 };
	sprite[Down][open] = { 0, 0, 0, 0 };
	sprite[Left][open] = { 0, 0, 0, 0 };
	sprite[Right][open] = { 0, 0, 0, 0 };
	sprite[Up][close] = { 0, 0, 64, 48 };
	sprite[Down][close] = { 72, 0, 64, 48 };
	sprite[Right][close] = { 72, 56, 48, 64 };
	sprite[Left][close] = { 16, 56, 48, 64 };
}

void DwDungeon::SetPos(int x, int y)
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

void Doorway::CleanUp()
{
	//LOG("DOOR CLEANUP");
	if (collider != nullptr) {
		collider->to_delete = true;
	}

	App->scene_manager->GetCurrentScene()->DestroyDoorway(this);

}
void Doorway::Draw()
{
	if (App->render->IsCameraCull(collider->rect)== false) {
		iPoint aux_pos = { collider->rect.x, collider->rect.y };
		switch (direction) {
		case Up:
			aux_pos.y -= 48;
			aux_pos.x -= 16;
			break;
		case Down:
			aux_pos.x -= 16;
			aux_pos.y += 16;
			break;
		case Left:
			aux_pos.x -= 48;
			aux_pos.y -= 16;
			break;
		case Right:
			aux_pos.x += 16;
			aux_pos.y -= 16;
			break;
		}
		App->render->toDraw(tex, -99999, aux_pos.x, aux_pos.y, &sprite[direction][state]);
	}
}
;

bool DwScene::Cross()
{
	if (crossed == false) {
		App->scene_manager->toChangeScene(target);
		crossed = true;
	}

	App->player->pos = target_pos;

	return true;
}

bool DwCam::Cross()
{

	App->player->pos = target;

	return true;
}