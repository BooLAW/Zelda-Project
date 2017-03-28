#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1Fonts.h"
#include "j1App.h"

#define CREATEIMAGE(path) (GuiImage*)App->gui->CreateElement(GuiType::image, path);
#define CREATETEXT (GuiText*)App->gui->CreateElement(GuiType::text);

#define CURSOR_WIDTH 2

enum GuiType 
{
	image = 0,
	text,
	button,
	Input
};

// UI ELEMENT
class UIElement {
public:
	iPoint pos;
	GuiType type;

	bool active;
	bool movable;

	SDL_Texture* texture;
	SDL_Rect texture_rect;
	p2List<UIElement*> children;
	UIElement* parent;
public:
	virtual void Start() {};
	virtual void Update() {};

protected:
	void Move(int x, int y);
};

// IMAGE
class GuiImage : public UIElement {
public:
	void Update();
};

// TEXT BANNER
class GuiText : public UIElement {
public:
	_TTF_Font* font;
	SDL_Color color;
	std::string str;

public:

	GuiText() {}
	~GuiText() {}

public:
	void Update();
};

// BUTTON
class GuiButton : public UIElement {
public:
	enum State {
		standard = 0,
		left_clicked,
		right_clicked,
		hover,
		disabled,
		Unknown
	} state;

	GuiText* text;
	GuiImage* image[State::Unknown];

public:
	GuiButton() {}
	~GuiButton() {
		if (text != nullptr)
			delete text;
		if (image != nullptr)
			delete image;
	}

	void Start();
	void Update();

};
class GuiInput : public UIElement {
public:
	GuiText* text;
	bool triggered;
public:
	GuiInput();
	~GuiInput() {};
	void Start();
	void Update();

};

class Window : public UIElement {
public:
	void Update();
	void CleanUp();
	void AddElement(UIElement* element);
	bool Inside(UIElement*element);
	void Scroll();
	void SetOffset(int x, int y);
	
private:
	std::list<UIElement*>win_elements;
	int offset_x;
	int offset_y;
	

};

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	UIElement* CreateElement(GuiType type);
	UIElement* CreateElement(GuiType type, const char* path);
	void DeleteElements();

	SDL_Texture* GetNonConstAtlas() const {
		return atlas;
	}

	const SDL_Texture* GetAtlas() const;
public:
	std::list<UIElement*> elements;
private:
	

	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__