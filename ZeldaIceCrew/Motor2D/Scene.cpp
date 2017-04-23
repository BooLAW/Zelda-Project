#include "Scene.h"
#include "j1Map.h"
#include "j1Window.h"

void Scene::DoorUpdate(float dt)
{
	if (doorways.empty() == false) {
		for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr) {
				it._Ptr->_Myval->Update(dt);
			}
		}
	}
}

bool Scene::CleanUp()
{

	App->map->CleanUp();

	if (items.empty() == false) {
		for (std::list<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if(it._Ptr->_Myval != nullptr)
				App->entitymanager->DestroyEnity((*it));
		}
		items.clear();
	}
	if (enemies.empty() == false) {
		for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				App->entitymanager->DestroyEnity((*it));
		}
		enemies.clear();
	}

	if (blocks.empty() == false) {
		for (std::list<Block*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
			if (it._Ptr->_Myval != nullptr)
				App->entitymanager->DestroyEnity((*it));
		}
		blocks.clear();
	}

	if (doorways.empty() == false) {
		for (std::list<Doorway*>::iterator it = doorways.begin(); it != doorways.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr)
				it._Ptr->_Myval->CleanUp();
			RELEASE(*it);
		}
		doorways.clear();
	}

	return true;
}

Item * Scene::AddItem(uint subtype, float x, float y)
{
	Item* ret = App->entitymanager->CreateItem(subtype);
	ret->pos = { x, y };

	items.push_back(ret);

	return ret;
}

Block * Scene::AddBlock(uint subtype, float x, float y)
{
	Block* nb = App->entitymanager->CreateBlock(subtype);
	nb->pos = { x, y };

	blocks.push_back(nb);

	return nb;
}

Doorway * Scene::AddDoorway(uint subtype, uint dir, int x, int y)
{
	Doorway* ret = nullptr;

	switch (subtype) {
	case dw_dungeon:
		ret = new DwDungeon();
		break;
	case dw_scene:
		ret = new DwScene();
		break;
	}

	ret->Start();
	ret->SetUp(dir);

	ret->SetRoomPos(x, y);

	doorways.push_back(ret);

	return ret;
}

Enemy* Scene::AddEnemy(int subtype, float x, float y)
{
	LOG("ADD ENEMY");
	Enemy* new_enemy = nullptr;
	new_enemy = App->entitymanager->CreateEnemy(subtype);
	new_enemy->pos = { x, y };

	this->enemies.push_back(new_enemy);

	return new_enemy;
}

bool Scene::IsEnemy(Enemy * en)
{
	bool ret = false;

	if (en != nullptr) {
		for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			if ((*it) == en)
				ret = true;
		}
	}

	return ret;
}

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