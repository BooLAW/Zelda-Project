#ifndef __HUD_H__
#define __HUD_H__

#include "j1Module.h"
#include "Animation.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1App.h"
#include "EntityManager.h"
#include "j1Gui.h"

class Item;
class HUD :public j1Module {
private:

	bool Start();
	bool Update(float dt);
	bool CleanUp();
	void GenerateHP();
	void GenerateKeys();
	void UpdateKeys();
	void Disable_keys();
	void Enable_keys();
	void UpdateHP();
	void check_item_collision();
	UIElement* menu_next();
	UIElement* menu_prev();
	
	
public:

	void Enable_map();
	void Disable_map();

public:

	bool minimap = false;
	void AddItem(Item* obj);
	void AddWeapon(Item* wep);
	SDL_Texture* items;
	GuiImage* rupees;
	//GuiImage* bombs;
	GuiImage* life_icon;
	GuiText* rupees_num;
	//GuiText* bombs_num;
	std::list<GuiImage*>lifes;
	Window* inv;
	//Window* weapons;
	GuiImage* descriptions_rect;
	GuiText* item_description;
	GuiImage* stats_rect;
	GuiImage* speed;
	GuiImage* power;
	GuiText* speed_num;
	GuiText* power_num;
//	GuiImage* weapon_rect;
//	GuiImage* pl_weapon;
	GuiImage* dialog_rect;
	GuiText* dialog;

	GuiImage* Menu;
	GuiImage* Continue;
	GuiImage* titlescreen;
	GuiImage* Exit;
	GuiImage* Controls;
	GuiImage* Minimap;
	GuiImage* link_point;

	GuiText* cont;
	GuiText* title;
	GuiText* exit;
	GuiText* controls;

	//CONTROLS

	GuiText* up;
	GuiText* down;
	GuiText* right;
	GuiText* left;
	GuiText* move_up;
	GuiText* move_down;
	GuiText* move_right;
	GuiText* move_left;
	GuiText* menu_inv;
	GuiText* action;
	GuiText* dash;

	GuiText* up_key;
	GuiText* down_key;
	GuiText* left_key;
	GuiText* right_key;
	GuiText* move_up_key;
	GuiText* move_down_key;
	GuiText* move_left_key;
	GuiText* move_right_key;
	GuiText* menu_key;
	GuiText* action_key;
	GuiText* dash_key;

	GuiImage* item_desc;
	GuiText* desc;
	bool in_controls=false;

	UIElement* menu_selected;

	std::list <UIElement*> menu;
	std::list<UIElement*>pl_keys;

	int dialog_num = 0;
	uint max_keys = 5;
	SDL_Texture* map0;
	SDL_Texture* map1;
	SDL_Texture* map2;
	SDL_Texture* map3;
	SDL_Texture* map4;

	uint move_fx;
	uint press_fx;

	GuiText* arena_round;
	GuiText* round;
	GuiImage* round_box;

};









#endif
