#include "Scene.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Window.h"

bool Scene::Update(float dt)
{
	return stdUpdate(dt);
}

bool Scene::stdUpdate(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;

	if (App->map->active)
		App->map->Draw();

	int i = 0;

	for (std::list<Room*>::iterator it = rooms.begin(); it != rooms.end(); it++) {
		if (it._Ptr->_Myval != nullptr) {
			//LOG("ROOM_UPDATE N� %d", i);
			it._Ptr->_Myval->Update(dt);
			i++;
		}
	}

	return true;
}

bool Scene::CleanUp()
{
	return stdCleanUp();
}

bool Scene::stdCleanUp()
{
	App->map->CleanUp();

	if (rooms.empty() == false) {
		for (std::list<Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr) {
				it._Ptr->_Myval->CleanUp();
				DestroyRoom(it._Ptr->_Myval);
			}
			RELEASE(*it);
		}
		rooms.clear();
	}

	return true;

}

Room * Scene::GetRoom(int x, int y)
{
	Room* ret = nullptr;

	for (std::list<Room*>::iterator it = rooms.begin(); it != rooms.end(); it++) {
		if (it._Ptr->_Myval->coords.x == x && it._Ptr->_Myval->coords.y == y) {
			ret = it._Ptr->_Myval;
			break;
		}
	}

	return ret;
}

Room * Scene::GetCurrentRoom()
{
	return GetRoom(App->player->room.x, App->player->room.y);
}

void Scene::DestroyItem(Item * ent)
{
	if (ent != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++)
			for (std::list<Item*>::iterator it = room_it._Ptr->_Myval->items.begin(); it != room_it._Ptr->_Myval->items.end(); it++) {
				if (it._Ptr->_Myval == ent) {
					it._Ptr->_Myval->to_delete = true;
					room_it._Ptr->_Myval->items.erase(it);
					//App->entitymanager->DestroyEnity(ent);
				}
			}
	}


}

void Scene::DestroyEnemy(Enemy * ent)
{
	if (ent != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++)
			for (std::list<Enemy*>::iterator it = room_it._Ptr->_Myval->enemies.begin(); it != room_it._Ptr->_Myval->enemies.end(); it++) {
				if (it._Ptr->_Myval == ent) {
					//App->entitymanager->DestroyEnity(ent);
					it._Ptr->_Myval->to_delete = true;
					room_it._Ptr->_Myval->enemies.erase(it);
				}
			}
	}
}
void Scene::DestroyBlock(Block * ent)
{
	if (ent != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++)
			for (std::list<Block*>::iterator it = room_it._Ptr->_Myval->blocks.begin(); it != room_it._Ptr->_Myval->blocks.end(); it++) {
				if (it._Ptr->_Myval == ent) {
					it._Ptr->_Myval->to_delete = true;
					room_it._Ptr->_Myval->blocks.erase(it);
					//App->entitymanager->DestroyEnity(ent);
				}
			}
	}
}
void Scene::DestroyDoorway(Doorway * ent)
{
	if (ent != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++) {
			if (room_it._Ptr->_Myval != nullptr);
			for (std::list<Doorway*>::iterator it = room_it._Ptr->_Myval->doorways.begin(); it != room_it._Ptr->_Myval->doorways.end(); it++) {
				if (it._Ptr->_Myval == ent) {
					//ent->CleanUp();
					room_it._Ptr->_Myval->doorways.erase(it);
				}
			}
		}
	}
}
void Scene::DestroyRoom(Room * ent)
{
	if (ent != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++)
			if (room_it._Ptr->_Myval == ent) {
				rooms.erase(room_it);
			}
	}

}
;

Item * Scene::AddItem(uint subtype, int coord_x, int coord_y, float x, float y)
{
	Room* r = GetRoom(coord_x, coord_y);
	
	Item* ret = nullptr;

	if (r != nullptr) {

		ret = App->entitymanager->CreateItem(subtype);
		ret->pos = { x + r->coords.x * ROOM_W , y + r->coords.y * ROOM_H };

		r->items.push_back(ret);
	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Block * Scene::AddBlock(uint subtype, int coord_x, int coord_y, float x, float y)
{
	Room* r = GetRoom(coord_x, coord_y);

	Block* ret = nullptr;

	if (r != nullptr) {

		ret = App->entitymanager->CreateBlock(subtype);
		ret->pos = { x + r->coords.x * ROOM_W , y + r->coords.y * ROOM_H };

		r->blocks.push_back(ret);
	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Doorway * Scene::AddDoorway(uint subtype, int coord_x, int coord_y, uint dir, int x, int y)
{
	Room* r = GetRoom(coord_x, coord_y);

	Doorway* ret = nullptr;

	if (r != nullptr) {

		switch (subtype) {
		case dw_scene:
			ret = new DwScene();
			break;
		case dw_cam:
			break;
		}

		ret->Start();
		ret->SetUp(dir);

		ret->SetPos(x + ROOM_W * coord_x, y + ROOM_H * coord_y);

		r->doorways.push_back(ret);
	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Doorway * Scene::AddDungeonDoorway(uint dir, int coord_x, int coord_y)
{
	Room* r = GetRoom(coord_x, coord_y);

	Doorway* ret = nullptr;

	if (r != nullptr) {

		ret = new DwDungeon();

		ret->Start();
		ret->SetUp(dir);

		ret->SetPos(coord_x, coord_y);

		r->doorways.push_back(ret);

	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Enemy* Scene::AddEnemy(int subtype, int coord_x, int coord_y, float x, float y)
{
	//LOG("ADD ENEMY");
	Room* r = GetRoom(coord_x, coord_y);

	Enemy* ret = nullptr;

	if (r != nullptr) {

		ret = App->entitymanager->CreateEnemy(subtype);
		ret->pos = { x + r->coords.x * ROOM_W , y + r->coords.y * ROOM_H };

		r->enemies.push_back(ret);
	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Room * Scene::AddRoom(int coord_x, int coord_y, int w, int h)
{
	Room* ret = nullptr;

	ret = new Room();

	ret->coords.x = coord_x;
	ret->coords.y = coord_y;
	ret->room_rect = { coord_x * w, coord_y * h , w, h };

	ret->SetParentScene(this);

	rooms.push_back(ret);

	return ret;
}

bool Scene::IsEnemy(Enemy * en)
{
	bool ret = false;

	if (en != nullptr) {
		for(std::list<Room*>::iterator r_it = rooms.begin(); r_it != rooms.end(); r_it++)
			for (std::list<Enemy*>::iterator it = r_it._Ptr->_Myval->enemies.begin(); it != r_it._Ptr->_Myval->enemies.end(); it++) {
				if ((*it) == en)
					ret = true;
			}
	}

	return ret;
}

void Scene::AllEnemyActive(bool flag)
{
	for (std::list<Room*>::iterator r_it = rooms.begin(); r_it != rooms.end(); r_it++) {
		for (std::list<Enemy*>::iterator it = (*r_it)->enemies.begin(); it != (*r_it)->enemies.end(); it++) {
			it._Ptr->_Myval->active = flag;
		}
	}
};

pugi::xml_node Scene::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;
	int size = 0;
	pugi::xml_parse_result result;
	char* buf = nullptr;
	switch (curr_id)
	{
	case null:
		break;
	case village:
		size = App->fs->Load("Village.xml", &buf);
		break;
	case dungeon:
		size = App->fs->Load("Dungeon.xml", &buf);
		break;
	case intro:
		//we have to stablish what do we need in the intro scene
		size = App->fs->Load("Intro.xml", &buf);
		break;
	default:
		break;
	}
	if(size != 0 && buf!=nullptr)
		result = config_file.load_buffer(buf, size);
	RELEASE(buf);

	if (result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
	{
		switch (curr_id)
		{
		case null:
			break;
		case village:
			ret = config_file.child("village");
			break;
		case dungeon:
			ret = config_file.child("dungeon");
			break;
		case intro:
			//we have to stablish what do we need in the intro scene
			ret = config_file.child("intro");
			break;
		default:
			break;
		}
	}
	return ret;
}
bool Scene::Load_new_map(int id)
{
	bool stop_rearch = false;

	pugi::xml_document	config_file;
	pugi::xml_node		config;
	config = LoadConfig(config_file);

	for (pugi::xml_node temp = config.child("maps").child("map"); stop_rearch == false; temp = temp.next_sibling())
	{
		if (temp.attribute("id").as_int(0) == id)
		{
			if (id == 1)//add more conditions
			{
				//player position
				App->player->pos.x = temp.child("Link").attribute("pos_x").as_int(0);
				App->player->pos.y = temp.child("Link").attribute("pos_y").as_int(0);
			}
			//Items
			if (temp.child("items").attribute("num").as_int() != 0)
			{
				pugi::xml_node temp_item = temp.child("items").child("item");
				for (int i = 0; i < temp.child("items").attribute("num").as_int(0); i++)
				{
					items.push_back(App->entitymanager->CreateItem(temp_item.attribute("id").as_int(0)));
					temp_item = temp_item.next_sibling();
				}
			}
			//Blocks
			if (temp.child("blocks").attribute("num").as_int() != 0)
			{
				pugi::xml_node temp_block= temp.child("blocks").child("block");
				for (int i = 0; i < temp.child("blocks").attribute("num").as_int(0); i++)
				{
					blocks.push_back(App->entitymanager->CreateBlock(temp_block.attribute("id").as_int(0)));
					temp_block = temp_block.next_sibling();
				}
			}
			//Doorways
			if (temp.child("doorways").attribute("num").as_int() != 0)
			{
				pugi::xml_node temp_item = temp.child("doorways").child("doorway");
				for (int i = 0; i < temp.child("doorways").attribute("num").as_int(0); i++)
				{
					items.push_back(App->entitymanager->CreateItem(temp_item.attribute("id").as_int(0)));
					temp_item = temp_item.next_sibling();
				}
			}
			//Enemies
			if (temp.child("enemies").attribute("num").as_int(0) != 0)
			{
				pugi::xml_node temp_enemy = temp.child("enemies").child("enemy");
				for (int i = 0; i < temp.child("enemies").attribute("num").as_int(0); i++)
				{
					enemies.push_back(App->entitymanager->CreateEnemy(temp_enemy.attribute("id").as_int(0)));
					temp_enemy = temp_enemy.next_sibling();
				}
			}
			//map
			std::string name_map = temp.attribute("file").as_string("");
			App->map->Load(name_map.c_str());

			//Camera position
			int scale = App->win->GetScale();
			App->player->camera_follow = temp.child("camera").attribute("follow").as_bool();
			// ------------NEEDED???
			//if (App->player->camera_follow == true)
			//{
			//	int h = App->win->GetHeight() / scale;
			//	int w = App->win->GetWidth() / scale;
			//	App->render->camera.x = -((player->position.x - (w / scale)) * scale);
			//	App->render->camera.y = -((player->position.y - (h / scale)) * scale);

			//	iPoint size_map = App->map->MapToWorld(App->map->data.width, App->map->data.height);
			//	if (-App->render->camera.x < 0)
			//	{
			//		App->render->camera.x = 0;
			//	}
			//	if (-App->render->camera.y < 0)
			//	{
			//		App->render->camera.y = 0;
			//	}
			//	if (((-App->render->camera.x / scale) + App->win->GetWidth() / scale) > size_map.x)
			//	{
			//		App->render->camera.x = (-size_map.x + App->win->GetWidth() / scale) * scale;
			//	}
			//	if (((-App->render->camera.y / scale) + App->win->GetHeight() / scale) > size_map.y)
			//	{
			//		App->render->camera.y = (-size_map.y + App->win->GetHeight() / scale) * scale;
			//	}
			//}
			//else
			//{
				iPoint size_pos = App->map->MapToWorld(App->map->data.width, App->map->data.height);
				App->render->camera.x = (App->win->GetWidth() / scale - size_pos.x);
				App->render->camera.y = (App->win->GetHeight() / scale - size_pos.y);
		//	}
			stop_rearch = true;
		}
	}
	return true;
}
