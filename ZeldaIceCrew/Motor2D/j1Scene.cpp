#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Fonts.h"
#include "j1Player.h"

#define MAX_TABS 2

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	
	if (App->map->Load("FirstMap.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	Bush_Rect = { 8*32,2*32,32,32 };
	House_Rect = {0,0,195,195};
	debug_tex = App->tex->Load("maps/Exteriors.png"); /// CHANGE THIS TO PROPER SPRITESHEET DON'T CHARGE FROM MAPS TEXTURE

	App->player->SetPosTile(2, 2);

	App->render->CamBoundOrigin();

	App->render->ScaleCamBoundaries(300);

	BS = App->entitymanager->CreateEnemy(BlueSoldier);
	BS->pos = { 20, 20 };

	//we can do that with an iterator that recieves the positions readed from the xml file

	App->player->SetPos(500, 100);
	GenerateHUD();

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	// debug pathfing ------------------
	if (App->debug == true) {
		static iPoint origin;
		static bool origin_selected = false;

		int x, y;
		App->input->GetMousePosition(x, y);
		iPoint p = App->render->ScreenToWorld(x, y);
		p = App->map->WorldToMap(p.x, p.y);

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			if (origin_selected == true)
			{
				App->pathfinding->CreatePath(origin, p);
				origin_selected = false;
			}
			else
			{
				origin = p;
				origin_selected = true;
			}
		}
	}
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->SaveGame("save_game.xml");
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;

	App->map->Draw();

	for (int i = 0; i < Bushes.size(); i++) {
		App->render->Blit(Bushes[i]->GetTexture(), Bushes[i]->pos.x, Bushes[i]->pos.y, &Bushes[i]->GetRect());

	}
	
	// Debug pathfinding ------------------------------
	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.size(),
		map_coordinates.x, map_coordinates.y);

	//int x, y;
	if (App->debug == true) {
		App->input->GetMousePosition(x, y);
		iPoint p = App->render->ScreenToWorld(x, y);
		p = App->map->WorldToMap(p.x, p.y);
		p = App->map->MapToWorld(p.x, p.y);
		App->win->SetTitle(title.GetString());
		//App->render->Blit(debug_tex, p.x, p.y);
	}
	//this is for testing must be removed before relising
	if (App->input->GetKey(SDL_SCANCODE_R)==KEY_DOWN) {
		App->player->rupees += 1;
	}
	if (App->player->curr_life_points != 0) {
		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {
			App->player->curr_life_points -= 1;
		}
	}
	///////////
	//UI updating

	rupees_num->str = std::to_string(App->player->rupees);
	bombs_num->str = std::to_string(App->player->bombs);
	arrows_num->str = std::to_string(App->player->arrows);

	i=2;
	for (std::list<GuiImage*>::const_iterator it = lifes.cbegin(); it != lifes.cend(); it++) {
		if (i <= App->player->curr_life_points) {
			if ((i % 2 == 0)) {
				it._Ptr->_Myval->texture_rect = { 897,418,28,28 };
			}
		
		if ((i == App->player->curr_life_points) && (i % 2 != 0)) {
			it._Ptr->_Myval->texture_rect = { 940,416,28,28 };
		}
	}
		if ((i > App->player->curr_life_points) && (i <= App->player->max_life_points)) {
			it._Ptr->_Myval->texture_rect = { 986,416,28,28 };
		}
		i+=2;
	}
		return true;
	
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::GenerateHUD()
{
	rupees = (GuiImage*)App->gui->CreateElement(GuiType::image);
	rupees->texture_rect = { 644,411,32,32 };
	rupees->active = true;
	rupees->pos = { 50,10 };

	bombs = (GuiImage*)App->gui->CreateElement(GuiType::image);
	bombs->texture_rect = { 702,411,32,32 };
	bombs->active = true;
	bombs->pos = { 125,10 };

	arrows = (GuiImage*)App->gui->CreateElement(GuiType::image);
	arrows->texture_rect = { 766,412,57,32 };
	arrows->active = true;
	arrows->pos = { 200,10 };

	life_icon = (GuiImage*)App->gui->CreateElement(GuiType::image);
	life_icon->texture_rect = { 735,462,176,28};
	life_icon->active = true;
	life_icon->pos = { 750,10 };
	
	rupees_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	rupees_num->active = true;
	rupees_num->str=std::to_string(App->player->rupees);
	rupees_num->pos = { 50,40 };

	bombs_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	bombs_num->active = true;
	bombs_num->str=std::to_string(App->player->bombs);
	bombs_num->pos = { 125,40 };

	arrows_num = (GuiText*)App->gui->CreateElement(GuiType::text);
	arrows_num->active = true;
	arrows_num->str=std::to_string(App->player->arrows);
	arrows_num->pos = { 200,40 };

	iPoint heart_pos = { 750,50 };

	for (uint i = 0; i <= App->player->max_life_points; i++){
		if (i <= App->player->curr_life_points) {
			if ((i % 2 == 0) && (i != 0)) {
				GuiImage* img;
				img = (GuiImage*)App->gui->CreateElement(GuiType::image);
				img->active = true;
				img->texture_rect = { 897,418,28,28 };
				img->pos = heart_pos;;
				heart_pos += {30, 0};
				lifes.push_back(img);
			}

			if ((i == App->player->curr_life_points) && (i % 2 != 0)) {
				GuiImage* img;
				img = (GuiImage*)App->gui->CreateElement(GuiType::image);
				img->active = true;
				img->texture_rect = { 940,416,28,28 };
				img->pos = heart_pos;
				heart_pos += {30, 0};
				lifes.push_back(img);
			}
		}
			
		 if(i>App->player->curr_life_points) {
			 if ((i % 2 == 0) && (i != 0)) {
				 GuiImage* img;
				 img = (GuiImage*)App->gui->CreateElement(GuiType::image);
				 img->active = true;
				 img->texture_rect = { 986,416,28,28 };
				 img->pos = heart_pos;
				 heart_pos += {30, 0};
				 lifes.push_back(img);
			 }
		}
		
	}
	
}
