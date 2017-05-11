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
	UIElement* menu_next();
	UIElement* menu_prev();
	
public:

	bool minimap = false;;
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
	GuiImage* weapon_rect;
	GuiImage* pl_weapon;
	GuiImage* dialog_rect;
	GuiText* dialog;

	GuiImage* Menu;
	GuiImage* Continue;
	GuiImage* titlescreen;
	GuiImage* Exit;
	GuiImage* Minimap;
	GuiImage* link_point;

	GuiText* cont;
	GuiText* title;
	GuiText* exit;

	UIElement* menu_selected;

	std::list <UIElement*> menu;
	std::list<UIElement*>pl_keys;

	int dialog_num = 0;
	uint max_keys = 5;
};









#endif
