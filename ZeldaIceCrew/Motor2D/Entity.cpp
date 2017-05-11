#include "Entity.h"
#include "j1Map.h"

void Entity::CleanUp()
{
	//LOG("ENT CLEANUP %d", type);

	if (tex != nullptr)
		App->tex->UnLoad(tex);

	tex = nullptr;

	//LOG("ENT TEX");

	if (HitBox != nullptr)
		HitBox->to_delete = true;

	//HitBox = nullptr;

	//LOG("ENT HITBOX");
}

bool Entity::LoadAttributes(pugi::xml_node attributes)
{
	return true;
}

bool Entity::LoadAnimations(std::string file)
{
	return true;
}

int Entity::CheckSpace(float new_x, float new_y)

{
	int ret = true;

	// TileCheck
	
	ret = App->map->TileCheck(new_x, new_y);
	//0 walkable
	//1 wall
	//2 hole

	if (ret != 1) {
		SDL_Rect r = HitBox->rect;
		r.x = new_x;
		r.y = new_y;

		Room* room = App->scene_manager->GetCurrentScene()->GetRoom(App->player->room.x, App->player->room.y);

		// Enemy Check
		if(room->enemies.empty() == false)
		for (std::list<Enemy*>::iterator it = room->enemies.begin(); it != room->enemies.end(); it++) {
			if (it._Ptr->_Myval != nullptr) {
				if (it._Ptr->_Myval == this)
					continue;
				if (CheckIntersec(r, it._Ptr->_Myval->HitBox->rect) == true) {
					ret = 1;
					break;
				}
			}
		}

		// Block Check
		if (ret != false) {

			for (std::list<Block*>::iterator it = room->blocks.begin(); it != room->blocks.end(); it++) {
				if (it._Ptr->_Myval != nullptr) {
					if (it._Ptr->_Myval == this)
						continue;
					if (CheckIntersec(r, it._Ptr->_Myval->HitBox->rect) == true) {
						ret = 1;
						break;
					}
				}
			}
		}

		// Player Check
		if (ret != false) {
			if (CheckIntersec(r, App->player->mov_coll->rect))
				ret = 1;
		}

	}

	return ret;
};
