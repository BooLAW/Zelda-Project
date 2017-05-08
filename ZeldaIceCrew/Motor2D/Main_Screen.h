#ifndef __MAIN_SCREEN_H__
#define __MAIN_SCREEN_H__

#include "j1Module.h"
#include <vector>
#include "Scene.h"
#include "j1Gui.h"

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
	void Scroll_Up();
	void Scroll_Down();

	bool IsInsideCam(UIElement* element);

	bool CleanUp();

private:

	std::list<UIElement*> ui_elements;
	std::list<UIElement*> settings_elements;
	std::list<UIElement*> controls_elements;
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

	///////

	bool in_settings;
	bool in_controls;

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
};

#endif //__Main_Screen_H__


