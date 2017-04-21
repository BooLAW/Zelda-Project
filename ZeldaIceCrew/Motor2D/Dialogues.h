#ifndef __DIALOGUES_H__
#define __DIALOGUES_H__

#include "j1Gui.h"
#include "SDL/include/SDL_rect.h"
#include "j1Input.h"
#include "SDL/include/SDL.h"

class Text_Line {

public:

	int lenght = 10;
	std::string text;
};

class Dialogue {

public: 

	std::list<Text_Line*>lines;
	GuiText* visible_text = nullptr;
	bool displaying=false;
	GuiImage* dialogue_box= nullptr;
	SDL_Texture* tex;
	SDL_Rect tex_rect;

public:

	
	void Create(std::string text);
	void Display();
	void Clean();


};




#endif 
