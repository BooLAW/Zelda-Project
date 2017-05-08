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

	bool CleanUp();

private:

	std::list<UIElement*> ui_elements;
	std::list<UIElement*> settings_elements;
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

	GuiImage* Controls;
	GuiImage* Mute;
	GuiImage* Back;
	GuiText* controls;
	GuiText* mute;
	GuiText* back;
};

#endif //__Main_Screen_H__

