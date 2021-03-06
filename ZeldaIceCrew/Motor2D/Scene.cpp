#include "Scene.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Player.h"
#include <string>

bool Scene::stdStart()
{
	App->scene_manager->loading_screen->active = true;
	Load_new_map(App->scene_manager->dungeon_id);
	App->player->pos = pl_start_pos;

	scene_node = LoadConfig(scene_file);

	for (scene = scene_node.child("maps").child("map"); scene; scene = scene.next_sibling("map")) {
		if (scene.attribute("id").as_int(0) != App->scene_manager->dungeon_id)
			continue;
		else
			break;
	}

	return true;

	enemy_selector = t_bluesoldier;
}

bool Scene::Update(float dt)
{
	return stdUpdate(dt);
}

bool Scene::stdUpdate(float dt)
{
	if(App->debug)
		ShowCoords();
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

	switch (App->input->returnkey()) {		
		case SDL_SCANCODE_1:
			enemy_selector = t_bluesoldier;
			break;
		case SDL_SCANCODE_2:
			enemy_selector = t_greensoldier;
			break;
		case SDL_SCANCODE_3:
			enemy_selector = t_redsoldier;
			break;
		case SDL_SCANCODE_4:
			enemy_selector = t_bluearcher;
			break;
		case SDL_SCANCODE_5:
			enemy_selector = t_geldman;
			break;
		case SDL_SCANCODE_6:
			enemy_selector = t_freezor;
			break;
		case SDL_SCANCODE_7:
			enemy_selector = t_beamos;
			break;
		case SDL_SCANCODE_8:
			enemy_selector = t_GBat;
			break;
		case SDL_SCANCODE_9:
			enemy_selector = t_hinox;
			break;

	}

	//if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
	//	Room* aux_r = nullptr;
	//	int mx = 0, my = 0;
	//
	//	App->input->GetMousePosition(mx, my);
	//
	//	aux_r = GetCurrentRoom();
	//
	//	if (aux_r != nullptr) {
	//		Enemy* new_en = nullptr;
	//		new_en = AddEnemy(enemy_selector, aux_r->coords.x, aux_r->coords.y, mx, my - (App->render->camera.h / 2 - ROOM_H / 2));
	//	//	if (new_en != nullptr) {
	//	//		pugi::xml_node node_room;
	//	//		for (pugi::xml_node node_rooms = scene.child("rooms"); node_rooms; node_rooms = node_rooms.next_sibling("rooms")) {
	//	//			for (node_room = node_rooms.child("room"); node_room; node_room = node_room.next_sibling("room")) {
	//	//				if (node_room.attribute("x").as_int() != aux_r->coords.x || (node_room.attribute("y").as_int() != aux_r->coords.y))
	//	//					continue;
	//	//				else
	//	//					break;
	//	//			}
	//	//		}
	//	//		LOG("ROOM %d %d", node_room.attribute("x").as_int(), node_room.attribute("y").as_int());
	//	//		pugi::xml_node enemies_node = node_room.child("enemies");
	//	//		if (enemies_node == NULL) {
	//	//			enemies_node = node_room.append_child("enemies");
	//	//		}
	//	//		pugi::xml_node enemy_node = enemies_node.append_child("enemy");
	//	//		enemy_node.append_attribute("subtype") = new_en->subtype;
	//	//		enemy_node.append_attribute("x") = new_en->pos.x - aux_r->coords.x * ROOM_W;
	//	//		enemy_node.append_attribute("y") = new_en->pos.y - aux_r->coords.y * ROOM_H;
	//	//		LOG("ENEMY %d", enemy_node.attribute("subtype").as_int(22));
	//	//	}
	//	}
	//}

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

	//App->entitymanager->DestroyEntities();

	return true;

}

void Scene::Clear()
{
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
					//it._Ptr->_Myval->to_delete = true;
					it._Ptr->_Myval->HitBox->SetPos(0, 0);
					App->entitymanager->DestroyEnity(ent);
					room_it._Ptr->_Myval->items.erase(it);
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
					App->entitymanager->DestroyEnity(ent);
					//it._Ptr->_Myval->to_delete = true;
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
					//it._Ptr->_Myval->to_delete = true;
					room_it._Ptr->_Myval->blocks.erase(it);
					App->entitymanager->DestroyEnity(ent);
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
void Scene::DestroyNPC(Npc * npc)
{
	if (npc != nullptr) {
		for (std::list<Room*>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++)
			for (std::list<Npc*>::iterator it = room_it._Ptr->_Myval->npcs.begin(); it != room_it._Ptr->_Myval->npcs.end(); it++) {
				if (it._Ptr->_Myval == npc) {
					App->entitymanager->DestroyEnity(npc);
					//it._Ptr->_Myval->to_delete = true;
					room_it._Ptr->_Myval->npcs.erase(it);
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

		ret->room = { coord_x, coord_y };

		ret->coords.x = r->coords.x;
		ret->coords.y = r->coords.y;

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

		ret->room = { coord_x, coord_y };

		r->blocks.push_back(ret);
	}
	else
		LOG("UNACCESIBLE ROOM: %d %d", coord_x, coord_y);

	return ret;
}

Doorway * Scene::AddSceneDoorway(Scene* target, int coord_x, int coord_y, uint dir, float x, float y)
{
	Room* r = GetRoom(coord_x, coord_y);

	DwScene* ret = nullptr;

	if (r != nullptr) {

		ret = new DwScene();

		ret->Start();
		ret->SetUp(dir);

		ret->SetPos(x + ROOM_W * coord_x, y + ROOM_H * coord_y);

		ret->SetTarget(target);

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

Doorway * Scene::AddCamDoorway(float target_x, float target_y, int coord_x, int coord_y, uint dir, float x, float y)
{
	Room* r = GetRoom(coord_x, coord_y);

	DwCam* ret = nullptr;

	if (r != nullptr) {

		ret = new DwCam();

		ret->Start();
		ret->SetUp(dir);

		ret->SetPos(x + ROOM_W * coord_x, y + ROOM_H * coord_y);

		ret->SetTargetPos(target_x, target_y);

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

		ret->room = { coord_x, coord_y };

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
	ret->room_rect = { coord_x * ROOM_W, coord_y * ROOM_H , w, h };

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

void Scene::ShowCoords()
{
	iPoint mouse_pos;
	App->input->GetMousePosition(mouse_pos.x, mouse_pos.y);

	mouse_pos.y -= (App->render->camera.h / 2 - ROOM_H / 2);

	std::string title = "MOUSE x: ";
	title.append(std::to_string(mouse_pos.x));
	title.append(" y: ");
	title.append(std::to_string(mouse_pos.y));

	App->win->SetTitle(title.c_str());

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
		LOG("SIZE %d", size);
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
		LOG("Could not load map XML. pugi error: %s \n ---Offset: %d", result.description(), result.offset);
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
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	config = LoadConfig(config_file);

	pugi::xml_node temp;

	for (temp = config.child("maps").child("map"); temp; temp = temp.next_sibling("map")) {
		if (temp.attribute("id").as_int(0) != id)
			continue;
		else
			break;
	}

	LOG("MAP %d", temp.attribute("id").as_int());

			// Camera 
			follow_cam = temp.child("camera").attribute("follow").as_bool(false);

				//Music
				App->audio->PlayMusic(temp.child_value("music"));
				App->audio->SetVolumeMusic(temp.child("music").attribute("volume").as_uint(60)*App->audio->volume_percentatge);

				//player position
				pl_start_pos.x = temp.child("Link").child("pos").attribute("x").as_int(0) + ROOM_W * temp.child("Link").child("room").attribute("x").as_int(0);
				pl_start_pos.y = temp.child("Link").child("pos").attribute("y").as_int(0) + ROOM_H * temp.child("Link").child("room").attribute("y").as_int(0);

				App->player->room.x = temp.child("Link").child("room").attribute("x").as_int(0);
				App->player->room.y = temp.child("Link").child("room").attribute("y").as_int(0);

				//Rooms

				for (pugi::xml_node node_rooms = temp.child("rooms"); node_rooms; node_rooms = node_rooms.next_sibling("rooms")) {
					for (pugi::xml_node node_room = node_rooms.child("room"); node_room; node_room = node_room.next_sibling("room")) {
						SDL_Rect room_coords;
						room_coords = { node_room.attribute("x").as_int(-999), node_room.attribute("y").as_int(-999), node_room.attribute("w").as_int(1024), node_room.attribute("h").as_int(576) };

						Room* r = AddRoom(room_coords.x, room_coords.y);
						r->room_rect.w = room_coords.w;
						r->room_rect.h = room_coords.h;

						if (r != nullptr) {

							//Items
							for (pugi::xml_node node_items = node_room.child("items"); node_items; node_items = node_items.next_sibling("items")) {
								for (pugi::xml_node node_item = node_items.child("item"); node_item; node_item = node_item.next_sibling("item")) {
									LOG("XML ITEMS");
									uint st = 0;
									Item* item_p = nullptr;
									char* sub = (char*)node_item.attribute("subtype").as_string("");

									if (strcmp(sub, "power_gauntlet") == 0)
										st = power_gauntlet;
									if (strcmp(sub, "pegasus_boots") == 0)
										st = pegasus_boots;
									if (strcmp(sub, "heart_container") == 0)
										st = heart_container;
									if (strcmp(sub, "boss_key") == 0)
										st = boss_key;
									if (strcmp(sub, "drop_heart") == 0)
										st = drop_heart;
									if (strcmp(sub, "drop_bomb") == 0)
										st = drop_bomb;
									if (strcmp(sub, "drop_potion") == 0)
										st = drop_potion;
									if (strcmp(sub, "drop_rupee") == 0)
										st = drop_rupee;
									if (strcmp(sub, "drop_fiverupee") == 0)
										st = drop_fiverupee;
									if (strcmp(sub, "drop_tenrupee") == 0)
										st = drop_tenrupee;
									if (strcmp(sub, "weapon_sword") == 0)
										st = weapon_sword;
									if (strcmp(sub, "weapon_bow") == 0)
										st = weapon_bow;
									if (strcmp(sub, "gold_gauntlet") == 0)
										st = gold_gauntlet;
									if (strcmp(sub, "wind_cape") == 0)
										st = wind_cape;
									if (strcmp(sub, "magic_hammer") == 0)
										st = magic_hammer;
									if (strcmp(sub, "small_shield") == 0)
										st = small_shield;
									if (strcmp(sub, "vanguard_emblem") == 0)
										st = vanguard_emblem;
									if (strcmp(sub, "magic_sphere") == 0)
										st = magic_sphere;
									if (strcmp(sub, "magic_mirror") == 0)
										st = magic_mirror;
									if (strcmp(sub, "golden_shield") == 0)
										st = golden_shield;
									if (strcmp(sub, "mysterious_dust") == 0)
										st = mysterious_dust;
									if (strcmp(sub, "odd_mushroom") == 0)
										st = odd_mushroom;
									if (strcmp(sub, "bag_of_rupees") == 0)
										st = bag_of_rupees;
									if (strcmp(sub, "icon_of_power") == 0)
										st = icon_of_power;
									if (strcmp(sub, "icon_of_valor") == 0)
										st = icon_of_valor;
									if (strcmp(sub, "icon_of_wisdom") == 0)
										st = icon_of_wisdom;
									if (strcmp(sub, "rnd_item") == 0) {
										do {
											st = rand() % 14;
										} while (st == golden_shield || st == odd_mushroom);
									}

									item_p = r->AddItem(st, node_item.attribute("x").as_float(0), node_item.attribute("y").as_float(0));    
									item_p->SetPrice(node_item.attribute("pricetag").as_uint(0));

								}
							}

							//Blocks
							for (pugi::xml_node node_blocks = node_room.child("blocks"); node_blocks; node_blocks = node_blocks.next_sibling("blocks")) {
								for (pugi::xml_node node_block = node_blocks.child("block"); node_block; node_block = node_block.next_sibling("block")) {
									LOG("XML BLOCKS");

									uint st = 0;

									const pugi::char_t* sub = node_block.attribute("subtype").as_string("");

									if (strcmp(sub, "bush") == 0)
										st = bush;
									if (strcmp(sub, "pot") == 0)
										st = pot;
									if (strcmp(sub, "statue") == 0)
										st = statue;
									if (strcmp(sub, "torch_bowl") == 0)
										st = torch_bowl;
									//if (strcmp(sub, "torch_pillar") == 0)
										//st = torch_pillar;
									if (strcmp(sub, "slabs") == 0)
										st = slabs;
									if (strcmp(sub, "slabs_no_move") == 0)
										st = slabs_no_move;
									if (strcmp(sub, "slabs_spikes") == 0)
										st = slabs_spikes;
									if (strcmp(sub, "button_wall") == 0)
										st = button_wall;
									if (strcmp(sub, "pressure_plate") == 0)
										st = pressure_plate;

									r->AddBlock(st, node_block.attribute("x").as_float(), node_block.attribute("y").as_float());
								}
							}

							//Doorways
							LOG("XML DW");
							for (pugi::xml_node node_dws = node_room.child("doorways"); node_dws; node_dws = node_dws.next_sibling("doorways")) {
								for (pugi::xml_node node_dw = node_dws.child("doorway"); node_dw; node_dw = node_dw.next_sibling("doorway")) {

									uint st = 0;
									uint dir = Down;

									const pugi::char_t* sub = node_dw.attribute("subtype").as_string("");
									const pugi::char_t* direction = node_dw.attribute("dir").as_string("");

									if (strcmp(direction, "Up") == 0)
										dir = Up;
									if (strcmp(direction, "Down") == 0)
										dir = Down;
									if (strcmp(direction, "Left") == 0)
										dir = Left;
									if (strcmp(direction, "Right") == 0)
										dir = Right;

									if (strcmp(sub, "dw_cam") == 0) {
										st = dw_cam;
										r->AddCamDoorway(node_dw.attribute("target_x").as_float(0), node_dw.attribute("target_y").as_float(0), dir, node_dw.attribute("x").as_float(), node_dw.attribute("y").as_float());
									}
									if (strcmp(sub, "dw_dungeon") == 0) {
										st = dw_dungeon;
										r->AddDungeonDoorway(dir);
									}
									if (strcmp(sub, "dw_scene") == 0) {
										st = dw_scene;

										Scene* target = nullptr;

										const pugi::char_t* t = node_dw.attribute("scene").as_string("");
										if (strcmp(t, "") != 0) {

											if (strcmp(t, "village") == 0)
												target = (Scene*)App->scene_manager->village_scene;
											if (strcmp(t, "dungeon") == 0)
												target = (Scene*)App->scene_manager->dungeon_scene;

											if (target != nullptr) {
												r->AddSceneDoorway(target, dir, node_dw.attribute("x").as_float(), node_dw.attribute("y").as_float());
											}
										}
									}
								}
							}

							//Enemies
							for (pugi::xml_node node_ens = node_room.child("enemies"); node_ens; node_ens = node_ens.next_sibling("enemies")) {
								for (pugi::xml_node node_en = node_ens.child("enemy"); node_en; node_en = node_en.next_sibling("enemy")) {
									LOG("XML ENEMIES");

									uint st = 0;

									const pugi::char_t* sub = node_en.attribute("subtype").as_string("");

									if (strcmp(sub, "t_bluesoldier") == 0)
										st = t_bluesoldier;
									if (strcmp(sub, "t_bluearcher") == 0)
										st = t_bluearcher;
									if (strcmp(sub, "t_redsoldier") == 0)
										st = t_redsoldier;
									if (strcmp(sub, "t_greensoldier") == 0)
										st = t_greensoldier;
									if (strcmp(sub, "t_hinox") == 0)
										st = t_hinox;
									if (strcmp(sub, "t_rope") == 0)
										st = t_rope;
									if (strcmp(sub, "t_geldman") == 0)
										st = t_geldman;
									if (strcmp(sub, "t_freezor") == 0)
										st = t_freezor;
									if (strcmp(sub, "t_GBat") == 0)
										st = t_GBat;
									if (strcmp(sub, "t_beamos") == 0)
										st = t_beamos;
									if (strcmp(sub, "t_boss_ballandchain") == 0)
										st = t_boss_ballandchain;
									if (strcmp(sub, "t_boss_agahnim") == 0)
										st = t_boss_agahnim;

									r->AddEnemy(st, node_en.attribute("x").as_float(), node_en.attribute("y").as_float());

								}
							}
						}
					}
				}

			//map
			std::string name_map = temp.child_value("file");
			App->map->Load(name_map.c_str());

			//Camera position
			int scale = App->win->GetScale();
			App->player->camera_follow = temp.child("camera").attribute("follow").as_bool(false);
		
	
			iPoint size_pos = App->map->MapToWorld(App->map->data.width, App->map->data.height);
			App->render->camera.x = (App->win->GetWidth() / scale - size_pos.x);
			App->render->camera.y = (App->win->GetHeight() / scale - size_pos.y);
			//	}

	return true;
}
