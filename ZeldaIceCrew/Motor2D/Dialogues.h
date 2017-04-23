#ifndef __DIALOGUES_H__
#define __DIALOGUES_H__

#include "j1Gui.h"
#include "j1Input.h"
#include "SDL/include/SDL.h"
#include <vector>

struct Text_Line {

	std::string text;
	//GuiText* line;
};


class Dialogue {

public: 

	std::string dialog;
	std::vector<Text_Line*>lines;
	//GuiText* visible_text = nullptr;
	bool displaying=false;
	GuiImage* dialogue_box= nullptr;
	SDL_Texture* tex;
	SDL_Rect tex_rect;
	GuiText* visible_text;
	int line_length = 10;
	int chunk_length = 3;

public:

	void Create(std::string text);
	void Display();
	void Update();
	void Clean();

};




#endif 
