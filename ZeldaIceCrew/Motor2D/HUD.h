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
	void UpdateHP();
public:
	void AddItem(Item* obj);
	SDL_Texture* items;
	GuiImage* rupees;
	GuiImage* bombs;
	GuiImage* life_icon;
	GuiText* rupees_num;
	GuiText* bombs_num;
	std::list<GuiImage*>lifes;
	Window* inv;
	GuiImage* descriptions_rect;
	GuiText* item_description;
	GuiImage* stats_rect;
	GuiImage* speed;
	GuiImage* power;
	GuiText* speed_num;
	GuiText* power_num;
	GuiImage* weapon_rect;
	GuiImage* pl_weapon;
};









#endif
