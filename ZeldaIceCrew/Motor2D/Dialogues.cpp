#include "Dialogues.h"

void Dialogue::Create(std::string text)
{
	tex = App->gui->GetNonConstAtlas();
	tex_rect = { 698,591,435,114 };
	Text_Line* line;
	int line_num = 0;
	for (int i = 0; i < text.length(); i++) {

		if (i % 10 == 0) {
			if (i != 0) {
				lines.push_back(line);
			}
			line = new Text_Line();
			line_num = 0;
		}
		text[i] = line->text[line_num];
	}
}

void Dialogue::Display()
{
	displaying = true;
	dialogue_box = (GuiImage*)App->gui->CreateElement(GuiType::image);
	dialogue_box->texture = tex;
	dialogue_box->texture_rect = tex_rect;
	dialogue_box->pos = { 100, 550 };
	dialogue_box->active = true;
	dialogue_box->movable = true;
	
	visible_text = (GuiText*)App->gui->CreateElement(GuiType::text);
	visible_text->active = true;
	visible_text->movable = true;
	visible_text->pos = { dialogue_box->pos.x+20,dialogue_box->pos.y+20 };

	std::list<Text_Line*>::const_iterator it = lines.cbegin();
	while (displaying) {

		visible_text->str = it._Ptr->_Myval->text;

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			if (it != lines.cend()) {
				it++;
			}
			else {
				displaying = false;
			}
		}
	}

	App->gui->DeleteElement(dialogue_box);
	App->gui->DeleteElement(visible_text);
}



void Dialogue::Clean()
{
	for (std::list<Text_Line*>::const_iterator it = lines.cbegin(); it != lines.cend(); it++) {
		delete it._Ptr->_Myval;
	}
}
