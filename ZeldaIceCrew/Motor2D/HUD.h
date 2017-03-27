#ifndef __HUD_H__
#define __HUD_H__

#include "j1Module.h"
#include "Animation.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Map.h"
#include "EntityManager.h"
#include "j1Gui.h"
#include "j1Player.h"

class HUD :public j1Module {
private:

	bool Start();
	bool Update(float dt);
	bool CleanUp();
	void GenerateHP();
	void UpdateHP();
public:

	GuiImage* rupees;
	GuiImage* arrows;
	GuiImage* bombs;
	GuiImage* life_icon;
	GuiText* rupees_num;
	GuiText* arrows_num;
	GuiText* bombs_num;
	std::list<GuiImage*>lifes;
};









#endif
