#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include<deque>

#define CURSOR_WIDTH 2

enum TYPE
{
	IMAGE,
	LABEL,
	BUTTON,
	TEXT_BOX,
	SELECTOR,
	WINDOW,
	WINDOWED_IMAGE
};

class Element
{
public:

	Element(const char* name, TYPE type, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	virtual ~Element();

	virtual void Update() {}
	virtual void Draw() {}
	virtual void Handle_Input() {}

public:

	const char* name;
	iPoint pos;
	SDL_Rect rect;
	TYPE type;
	SDL_Texture* texture;

	unsigned int ChangeTab_id(unsigned int id);

	uint tab_id = 0;

	bool moving = false;

};

// ------------------------------------------------------------------

class Image : public Element
{
public:

	Image(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	SDL_Rect OriginalRect;
	iPoint Changer;
	void ChangeImage(iPoint& change);
	~Image();

	void Update();
	void Draw();
public:
};
//--------------------------------------------
class Windowed_Image : public Element
{
public:

	Windowed_Image(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	std::deque<SDL_Rect> rects;
	std::deque<iPoint> points;
	uint cur_rect;
	SDL_Rect Window_Rect;//the one that is visible
	iPoint Changer;
	void ChangeImage();
	~Windowed_Image();

	void Update();
	void Draw();
	bool is_Windowed();
public:
	bool windowed;
};
// ------------------------------------------------------------------

class Label : public Element
{
public:

	Label(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect, p2SString text);
	~Label();

	void Update();
	void Draw();

private:

	p2SString text;
};

// ------------------------------------------------------------------

class Interactive : public Element
{
public:

	Interactive(const char* name, TYPE type, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	virtual ~Interactive();

	int MouseState();
	bool IsOnTop();
	void Move();

	void Attach(Element* element);

protected:

	uint tab_id = 0;
	std::deque<Element*> linked_elements;

private:
	iPoint curr_mouse_pos;
	iPoint prev_mouse_pos;
};

// ------------------------------------------------------------------

class Text_Box : public Interactive
{
public:
	Text_Box(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect, p2SString text);
	~Text_Box();

	void Update();
	void Draw();
	void Handle_Input() {}

private:
	p2SString text;
	uint cursor = 0;
	bool editing;
};

// ----------------------------------------------------------------------

class Button : public Interactive
{
public: 
	Button(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	~Button();

	void Update();
	void Draw();
	void Handle_Input() {}
};

// ----------------------------------------------------------------------
class Selector : public Image {
public:
	iPoint SelectorPosition=iPoint(0,0);
	iPoint MovementLimitsMin;
	iPoint MovementLimitsMax;
	iPoint OriginalPosition;
	bool activated = false;
	
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	
	SDL_Rect MoveRect;
public:
	Selector(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	void Draw();
	void Update();
};

class Window : public Interactive
{
public:

	Window(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	~Window();

	void Update();
	void Draw();
	void Handle_Input() {}
};
// ======================================================================
class j1Gui : public j1Module
{
public:
	j1Gui();
	virtual ~j1Gui();

	bool Awake(pugi::xml_node&);  
	bool Start();	              
	bool PreUpdate();             
	bool PostUpdate();            
	bool CleanUp();               
	
	
	const SDL_Texture* GetAtlas() const;

	Element* Create_Element(const char* name, TYPE type, iPoint pos, SDL_Rect rect, p2SString text = nullptr, _TTF_Font* font = NULL);
	void Destroy_Element(const char* name);

	bool Element_Moving();

private:

	std::deque<Element*> elements;
	uint curr_id = 0;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
	
};

#endif // __j1GUI_H__