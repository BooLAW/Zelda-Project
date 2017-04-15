#include "Entity.h"
#include "j1Map.h"

bool Entity::CheckSpace(float new_x, float new_y)
{
	bool ret = true;

	// TileCheck
	ret = !App->map->TileCheck(new_x, new_y);

	if (ret != false) {
		SDL_Rect r = HitBox->rect;
		r.x = new_x;
		r.y = new_y;

		Scene* scene = App->scene_manager->GetCurrentScene();

		// Enemy Check
		for (std::list<Enemy*>::iterator it = scene->enemies.begin(); it != scene->enemies.end(); it++) {
			if (it._Ptr->_Myval != nullptr) {
				if (it._Ptr->_Myval == this)
					continue;
				if (scene->IsInside(r, it._Ptr->_Myval->HitBox->rect) == true) {
					ret = false;
					break;
				}
			}
		}

		// Block Check
		if (ret != false) {
		
			for (std::list<Block*>::iterator it = scene->blocks.begin(); it != scene->blocks.end(); it++) {
				if (it._Ptr->_Myval != nullptr) {
					if (it._Ptr->_Myval == this)
						continue;
					if (scene->IsInside(r, it._Ptr->_Myval->HitBox->rect) == true) {
						ret = false;
						break;
					}
				}
			}
		}

		// Player Check
		if (ret != false) {
			if (scene->IsInside(r, App->player->mov_coll->rect))
				ret = false;
		}

	}

	return ret;
}
