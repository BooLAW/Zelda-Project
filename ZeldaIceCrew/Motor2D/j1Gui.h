#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "SDL\include\SDL_rect.h"

#define CREATEIMAGE(path) (GuiImage*)App->gui->CreateElement(GuiType::image, path);
#define CREATETEXT (GuiText*)App->gui->CreateElement(GuiType::text);

#define CURSOR_WIDTH 2

class Item;
enum GuiType 
{
	image = 0,
	text,
	button,
	Input,
	window,
	dialog_box,
	UI_string

};
enum TEXTSTATE
{
	FINISHED_TEXT,
	MID_TEXT,
	
};

// UI ELEMENT
class UIElement {
public:
	iPoint pos;
	GuiType type;

	bool active;
	bool movable;
	Item* obj;
	SDL_Texture* texture;
	SDL_Rect texture_rect;
	std::list<UIElement*> children;
	UIElement* parent;
	bool max_prior = false;
public:
	void Set_Interactive_Box(SDL_Rect);
	void Set_Active_state(bool);
	virtual void Start() {};
	virtual void Update() {};
	virtual void PreUpdate() {}
	virtual void PostUpdate() {}
protected:
	void Move(int x, int y);
};

// IMAGE
class GuiImage : public UIElement {
public:
	void Start();
	void Update();
};

// TEXT BANNER
class GuiText : public UIElement {
public:
	_TTF_Font* font;
	SDL_Color color;
	std::string str;
	void Start();

public:

	GuiText() {};
	~GuiText() {}

public:
	void Update();
};

class UI_String : public UIElement
{
public:
	std::string			text;
	int				text_size;
	_TTF_Font*		text_font = nullptr;
	SDL_Texture*	text_texture = nullptr;

	TEXTSTATE		dialog_state = FINISHED_TEXT;
	int				blit_time = 0;

public:

	UI_String(const UI_String* other);
	UI_String() {};


	bool Set_String(char* new_text);				//Changes the string
	void Load_text_texture();						//Loads the text texture

	void Update();
	bool Update_Draw();
	bool Handle_input();

	bool Draw_console(int height);					//Blits the string in the console [takes into account the height where it is the string]

	void SetBlitTimeMS(int);
	void ForcedFinish();

private:

	void LookEnter();

	std::string	blit_text;
	j1Timer	char_blit_time;
	void	BlitDialog();


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
	//void PreUpdate();
	void Update();
	//void PostUpdate();

};

class Window : public UIElement {
public:
	Window();
	~Window();
	void Update();
	void CleanUp();
	void Disable();
	void AddElement(UIElement* element);
	bool Inside(UIElement*element);
	void Scroll();
	void SetOffset(int x, int y);
	void Set_Sel_Rect(SDL_Rect rect);
	void Move_Sel_forward();
	UIElement* Next();
	UIElement* Prev();
	UIElement* current();
	void Sel_First();
	void Start_Sel(SDL_Rect rect);
	bool Empty();
	void clear();
	void Move_Sel_backwards();
	void Move_Sel_up();
	void Move_Sel_down();
	void Select(UIElement* el);
	UIElement* Selected();
	UIElement* selected;
private:
	GuiImage* selector;
	std::list<UIElement*>win_elements;
	int offset_x;
	int offset_y;
	

};

class UI_DialogBox : public UIElement
{
public:

//	UI_DialogBox(GuiType, j1Module*);
	UI_DialogBox() {};
	~UI_DialogBox();

	bool Update_Draw();

	void SetImage(const GuiImage*);
	void SetText(const GuiText*);
	void SetViewport(SDL_Rect);

private:

	GuiImage*	Box = nullptr;
	GuiText*	Dialog_Text = nullptr;
	SDL_Rect	Dialog_ViewPort;
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
	void DeleteElement(UIElement* del);
	SDL_Texture* GetNonConstAtlas() const {
		return atlas;
	}

	const SDL_Texture* GetAtlas() const;
public:
	bool in_video = false;
	std::list<UIElement*> elements;
private:
	

	SDL_Texture* atlas;
	std::string atlas_file_name;
};

#endif // __j1GUI_H__