#include "Doorway.h"
#include "j1Player.h"
#include "Entity.h"
#include "VillageScene.h"
#include "DungeonScene.h"
#include "j1Input.h"
void Doorway::Start()
{
	char* tex_str = nullptr;
	switch (App->scene_manager->dungeon_id) {
	case 0:
		tex_str = "Sprites/Door.png";
		break;
	case 1:
		tex_str = "Sprites/DoorRetro.png";
		break;
	case 2:
		tex_str = "Sprites/DoorDesert.png";
		break;
	case 3:
		tex_str = "Sprites/Doors forest.png";
		break;
	case 4:
		tex_str = "Sprites/Doors cave.png";
		break;
	case 5:
		tex_str = "Sprites/Door.png";
		break;
	}
	tex = App->tex->Load(tex_str);
	crossed = false;
	state = open;
	collider = App->collisions->AddCollider({ 0, 0, 0, 0 }, COLLIDER_DUNGEON_DOORWAY);
	SetUp();
}

void Doorway::SetUp(uint dir)
{
	direction = dir;
	if (collider != nullptr) {
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

			break;
		}
	}
}
void Doorway::Update(float dt)
{

	bool end_animating = false;

	if (animating == true) {

		App->scene_manager->GetCurrentScene()->AllEnemyActive(false);
		App->render->cam_travel = true;
	
		iPoint go_to = { -((App->player->room.x - 1) * ROOM_W), -((App->player->room.y - 1) * ROOM_H - (App->render->camera.h / 2 - ROOM_H / 2)) };
	
	//	if (App->render->camera.x != go_to.x && App->render->camera.y != go_to.y) {
	//
			switch (direction) {
			case Up:
				if (App->render->camera.y >= go_to.y)
					end_animating = true;
				App->render->camera.y += CHANGE_SPEED;
				break;
			case Down:
				if (App->render->camera.y <= go_to.y - 2 * ROOM_H)
			 		end_animating = true;
				App->render->camera.y -= CHANGE_SPEED;
				break;
			case Left:
			
				if (App->render->camera.x >= go_to.x)
					end_animating = true;
				App->render->camera.x += CHANGE_SPEED;
				break;
			case Right:
			
				if (App->render->camera.x <= go_to.x - 2*ROOM_W)
					end_animating = true;
				App->render->camera.x -= CHANGE_SPEED;
				break;
			}
			if (end_animating == true) {
				App->render->cam_travel = false;
				App->scene_manager->GetCurrentScene()->AllEnemyActive(true);
				animating = false;
			}

	}
	else {

		collider->SetPos(pos.x, pos.y);

		bool crossing = false;

		if (App->player->link_coll != nullptr)
			if (collider->CheckCollision(App->player->link_coll->rect) == true) {
				switch (direction) {
				case Up:
					if (App->input->GetKey(App->input->controls[MOVE_UP]) || SDL_JoystickGetAxis(App->input->joy, 1) < -CONTROLLER_SENSIBILITY)
						crossing = true;
					break;
				case Down:
					if (App->input->GetKey(App->input->controls[MOVE_DOWN]) || SDL_JoystickGetAxis(App->input->joy, 1) > CONTROLLER_SENSIBILITY)
						crossing = true;
					break;
				case Left:
					if (App->input->GetKey(App->input->controls[MOVE_LEFT]) || SDL_JoystickGetAxis(App->input->joy, 0) < -CONTROLLER_SENSIBILITY)
						crossing = true;
					break;
				case Right:
					if (App->input->GetKey(App->input->controls[MOVE_RIGHT]) || SDL_JoystickGetAxis(App->input->joy, 0) > CONTROLLER_SENSIBILITY)
						crossing = true;
					break;
				}
			}
		if (crossing == true && (state == open || state == half)) {
			
				Cross();
				
			
		}

		Draw();
	}

		
};

bool DwDungeon::Cross()
{

	App->render->cam_travel = true;

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

	animating = true;

	//App->Pause();


	return true;
}

void DwDungeon::SetUp()
{

	switch (App->scene_manager->dungeon_id) {
	case 0:
		//tex_str = "Sprites/Door.png";
		sprite[Up][open] = { 0, 0, 0, 0 };
		sprite[Down][open] = { 0, 0, 0, 0 };
		sprite[Left][open] = { 0, 0, 0, 0 };
		sprite[Right][open] = { 0, 0, 0, 0 };
		sprite[Up][close] = { 0, 0, 64, 48 };
		sprite[Down][close] = { 72, 0, 64, 48 };
		sprite[Right][close] = { 72, 56, 48, 64 };
		sprite[Left][close] = { 16, 56, 48, 64 };
		break;
	case 1:
		//tex_str = "Sprites/DoorRetro.png";
		sprite[Up][open] = { 0, 0, 0, 0 };
		sprite[Down][open] = { 0, 0, 0, 0 };
		sprite[Left][open] = { 0, 0, 0, 0 };
		sprite[Right][open] = { 0, 0, 0, 0 };
		sprite[Up][close] = { 0, 0, 64, 48 };
		sprite[Down][close] = { 72, 0, 64, 48 };
		sprite[Right][close] = { 72, 56, 48, 64 };
		sprite[Left][close] = { 16, 56, 48, 64 };
		break;
	case 2:
		//tex_str = "Sprites/DoorDesert.png";
		sprite[Up][open] = { 0, 0, 0, 0 };
		sprite[Down][open] = { 0, 0, 0, 0 };
		sprite[Left][open] = { 0, 0, 0, 0 };
		sprite[Right][open] = { 0, 0, 0, 0 };
		sprite[Up][close] = { 0, 0, 64, 48 };
		sprite[Down][close] = { 72, 0, 64, 48 };
		sprite[Right][close] = { 72, 56, 48, 64 };
		sprite[Left][close] = { 16, 56, 48, 64 };
		break;
	case 3:
		//tex_str = "Sprites/Door forest.png";
		sprite[Up][open] =			{ 0, 0, 0, 0 };
		sprite[Down][open] =		{ 0, 0, 0, 0 };
		sprite[Left][open] =		{ 0, 0, 0, 0 };
		sprite[Right][open] =		{ 0, 0, 0, 0 };
		sprite[Down][close] =		{ 0,	0,		94, 64};
		sprite[Up][close] =			{ 0,	68,		94, 64};
		sprite[Right][close] =		{ 98,	0,		64, 94};
		sprite[Left][close] =		{ 166,	0,		64, 94};
		sprite[Down][half] =		{ 0,	144,	94, 64 };
		sprite[Up][half] =			{ 0,	212,	94, 64 };
		sprite[Right][half] =		{ 98,	144,	64, 94 };
		sprite[Left][half] =		{ 166,	144,	64, 94 };
		break;
	case 4:
		//tex_str = "Sprites/Door cave.png";
		sprite[Up][open] =		{ 0,	0,		0,		0 };
		sprite[Down][open] =	{ 0,	0,		0,		0 };
		sprite[Left][open] =	{ 0,	0,		0,		0 };
		sprite[Right][open] =	{ 0,	0,		0,		0 };
		sprite[Up][half] =		{ 136,	136,	96,		64 };
		sprite[Down][half] =	{ 136,	204,	96,		64 };
		sprite[Right][half] =	{ 68,	136,	64,		96 };
		sprite[Left][half] =	{ 0,	136,	64,		96 };
		sprite[Up][close] =		{ 136,	0,		96,		64 };
		sprite[Down][close] =	{ 136,	68,		96,		64 };
		sprite[Right][close] =	{ 68,	0,		64,		96 };
		sprite[Left][close] =	{ 0,	0,		64,		96 };
		break;
	case 5:
		//tex_str = "Sprites/Door.png";
		sprite[Up][open] = { 0, 0, 0, 0 };
		sprite[Down][open] = { 0, 0, 0, 0 };
		sprite[Left][open] = { 0, 0, 0, 0 };
		sprite[Right][open] = { 0, 0, 0, 0 };
		sprite[Up][close] = { 0, 0, 64, 48 };
		sprite[Down][close] = { 72, 0, 64, 48 };
		sprite[Right][close] = { 72, 56, 48, 64 };
		sprite[Left][close] = { 16, 56, 48, 64 };
		break;
	default:
		sprite[Up][open] = { 0, 0, 0, 0 };
		sprite[Down][open] = { 0, 0, 0, 0 };
		sprite[Left][open] = { 0, 0, 0, 0 };
		sprite[Right][open] = { 0, 0, 0, 0 };
		sprite[Up][close] = { 0, 0, 64, 48 };
		sprite[Down][close] = { 72, 0, 64, 48 };
		sprite[Right][close] = { 72, 56, 48, 64 };
		sprite[Left][close] = { 16, 56, 48, 64 };
		break;
	}

	for (int k = 0; k < Direction::LastDir; k++) {
		open_anim[k].PushBack(sprite[k][close]);
		open_anim[k].PushBack(sprite[k][half]);
		open_anim[k].PushBack(sprite[k][open]);
		open_anim[k].speed = 0.1;
		open_anim[k].loop = false;
		close_anim[k].PushBack(sprite[k][close]);
		close_anim[k].PushBack(sprite[k][half]);
		close_anim[k].PushBack(sprite[k][open]);
		close_anim[k].speed = 0.1;
		close_anim[k].loop = false;

	}

}

void DwDungeon::Draw()
{
	if (App->render->IsCameraCull(collider->rect) == false) {
		iPoint aux_pos = { collider->rect.x, collider->rect.y };
		

		switch (direction) {
		case Up:
			aux_pos.y -= 48;
			aux_pos.x -= 16;
			if (App->scene_manager->dungeon_id == 3 || App->scene_manager->dungeon_id == 4) {
				aux_pos.y += 16;
				aux_pos.x -= 16;
				if (App->scene_manager->dungeon_id == 4) {
					aux_pos.y -= 16;
				}
			}
			break;
		case Down:
			aux_pos.x -= 16;
			aux_pos.y += 16;
			if (App->scene_manager->dungeon_id == 3 || App->scene_manager->dungeon_id == 4) {
				aux_pos.y -= 32;
				aux_pos.x -= 16;
				if (App->scene_manager->dungeon_id == 4) {
					aux_pos.y += 16;
				}
			}
			break;
		case Left:
			aux_pos.x -= 48;
			aux_pos.y -= 16;
			if (App->scene_manager->dungeon_id == 3 || App->scene_manager->dungeon_id == 4) {
				aux_pos.y -= 16;
				aux_pos.x += 8;
				if (App->scene_manager->dungeon_id == 4) {
					aux_pos.x -= 8;
				}
			}
			break;
		case Right:
			aux_pos.x += 16;
			aux_pos.y -= 16;
			if (App->scene_manager->dungeon_id == 3 || App->scene_manager->dungeon_id == 4) {
				aux_pos.x -= 32;
				aux_pos.y -= 16;
				if (App->scene_manager->dungeon_id == 4) {
					aux_pos.x += 16;
				}
			}
			break;
		}

		if (state == half) {
			App->render->toDraw(tex, -99999, aux_pos.x, aux_pos.y, &open_anim[direction].GetCurrentFrame());
			if (open_anim[direction].Finished()) {
				//open_anim[direction].Reset();
				state = open;
			}
		}
		else if (state == half_close) {
			App->render->toDraw(tex, -99999, aux_pos.x, aux_pos.y, &close_anim[direction].GetCurrentFrame());
			if (close_anim[direction].Finished()) {
				//close_anim[direction].Reset();
				state = close;
			}
		}
		else {
			App->render->toDraw(tex, -99999, aux_pos.x, aux_pos.y, &sprite[direction][state]);
		}
	}
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
	
	if (collider != nullptr) {
		collider->to_delete = true;
	}

	App->scene_manager->GetCurrentScene()->DestroyDoorway(this);

}
void Doorway::Draw()
{
	
}
;

bool DwScene::Cross()
{
	
		App->scene_manager->ChangeScene(target);

	return true;
}

bool DwCam::Cross()
{

	App->player->pos = target;

	return true;
}