#ifndef __MAIN_SCREEN_H__
#define __MAIN_SCREEN_H__

#include "j1Module.h"
#include <vector>
#include "Scene.h"
#include "j1Gui.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;
//UI forward declarations
class Image;
class Label;
class Text_Box;
class Button;
class Window;
class Selector;
class Windowed_Image;
class Main_Screen : public Scene
{
public:

	Main_Screen();

	// Destructor
	virtual ~Main_Screen();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	UIElement* Next();
	UIElement* Prev();
	UIElement* Settings_Next();
	UIElement* Settings_Prev();
	UIElement* Controls_Prev();
	UIElement* Controls_Next();
	UIElement* Dungeons_Next();
	UIElement* Dungeons_Prev();
	UIElement* Choosing_Next();
	UIElement* Choosing_Prev();
	void Erasekeys();
	void Scroll_Up();
	void Scroll_Down();
	void Generatekeys();
	void UpdateKeys();
	void Enablekeys();
	void Disablekeys();

	bool IsInsideCam(UIElement* element);

	bool CleanUp();

	void Disable_dungeons();
	void Enable_dungeons();


private:

	std::list<UIElement*> ui_elements;
	std::list<UIElement*> settings_elements;
	std::list<UIElement*> controls_elements;
	std::list<UIElement*> dungeons;
	std::list<UIElement*> keys;
	std::list<UIElement*> choosing;
	UIElement* selected;
	GuiImage* New_game;
	GuiImage* Continue;
	GuiImage* Settings;
	GuiImage* Exit;
	GuiImage* background;
	GuiText* new_game;
	GuiText* cont;
	GuiText* settings;
	GuiText* exit;
	uint fx;
	uint press_fx;
	uint error;

	///////

	bool in_settings;
	bool in_controls;
	bool in_dungeons;
	bool changing_controls = false;
	bool in_keyboard;
	bool in_pad;

	GuiImage* Controls;
	GuiImage* Mute;
	GuiImage* Back;
	GuiText* controls;
	GuiText* mute;
	GuiText* back;

	////////////
	GuiImage* Up;
	GuiImage* Down;
	GuiImage* Right;
	GuiImage* Left;
	GuiImage* Move_up;
	GuiImage* Move_down;
	GuiImage* Move_right;
	GuiImage* Move_left;
	GuiImage* Menu;
	GuiImage* Action;
	GuiImage* Dash;
	GuiImage* Back_controls;

	GuiText* up;
	GuiText* down;
	GuiText* right;
	GuiText* left;
	GuiText* move_up;
	GuiText* move_down;
	GuiText* move_right;
	GuiText* move_left;
	GuiText* menu;
	GuiText* action;
	GuiText* dash;
	GuiText* back_controls;


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

	GuiImage* d1;
	GuiImage* d2;
	GuiImage* d3;
	GuiImage* d4;
	GuiImage* d5;
	GuiImage* dungeon_boss;
	GuiImage* Back_dung;
	GuiImage* preset1;
	GuiImage* preset2;


	GuiImage* key1;
	GuiImage* key2;
	GuiImage* key3;
	GuiImage* key4;
	GuiImage* key5;

	GuiImage* Screen;
	GuiText* screen;

	GuiText* D1;
	GuiText* D2;
	GuiText* D3;
	GuiText* D4;
	GuiText* D5;
	GuiText* DB;
	GuiText* back_dung;
	GuiText* arena;
	GuiImage* img_dung;

	GuiText* d1_lvl;
	GuiText* d2_lvl;
	GuiText* d3_lvl;
	GuiText* d4_lvl;
	GuiText* d5_lvl;

	GuiImage* Key;
	GuiImage* Pad;

	GuiText* key;
	GuiText* pad;


	GuiImage* Arena;
	


	SDL_Texture* tex;
	SDL_Texture* controlers;
	SDL_Texture* controlers_sel;
};

#endif //__Main_Screen_H__


