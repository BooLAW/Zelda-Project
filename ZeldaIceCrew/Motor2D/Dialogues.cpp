#include "Dialogues.h"

void Dialogue::Create(std::string text)
{

	/*if (!text.empty()) {
		tex = App->gui->GetNonConstAtlas();
		tex_rect = { 698,591,435,114 };
		Text_Line* line = nullptr;
		int char_num = 0;
		for (int i = 0; i < text.size(); i++) {
			if (i % line_length == 0) {
				line = new Text_Line();
				lines.push_back(line);
				char_num = 0;
			}
			lines.cend()._Ptr->_Prev->_Myval->text[char_num] = text[i];
			char_num++;*/

	/*if (!text.empty()) {
		tex = App->gui->GetNonConstAtlas();
		tex_rect = { 698,591,435,114 };
		Text_Line* line = nullptr;
		int char_num = 0;
		for (int i = 0; i < text.size(); i++) {
			if (i % line_length == 0) {
				if (i == 0) {
					line = new Text_Line();
				}
				else {
					lines.push_back(line);
					line = new Text_Line();
					char_num = 0;
				}
			}
			text[i] = line->text[char_num];
			char_num++;
		}
		

		}*/

	this->dialog = text;
}

void Dialogue::Display()
{

	displaying = true;
	dialogue_box = (GuiImage*)App->gui->CreateElement(GuiType::image);
	dialogue_box->texture = tex;
	dialogue_box->texture_rect = tex_rect;
	dialogue_box->pos = { 50,50 };
	dialogue_box->active = true;
	dialogue_box->movable = true;

	visible_text = (GuiText*)App->gui->CreateElement(GuiType::text);
	visible_text->active = true;
	visible_text->movable = true;
	visible_text->pos = { dialogue_box->pos.x + 20,dialogue_box->pos.y + 20 };
	if (!dialog.empty())
	visible_text->str = dialog;

	/*if (!lines.empty()) {
		displaying = true;
		dialogue_box = (GuiImage*)App->gui->CreateElement(GuiType::image);
		dialogue_box->texture = tex;
		dialogue_box->texture_rect = tex_rect;
		dialogue_box->pos = { 50,50 };
		dialogue_box->active = true;
		dialogue_box->movable = true;


		visible_text = (GuiText*)App->gui->CreateElement(GuiType::text);
		visible_text->active = true;
		visible_text->movable = true;
		visible_text->pos = { dialogue_box->pos.x + 20,dialogue_box->pos.y + 20 };
		visible_text->str = lines[0]->text;

		//std::list<Text_Line*>::const_iterator it = lines.cbegin();
		int curr_line = 0;

		if (displaying) {
			visible_text->str = lines[curr_line]->text;
			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
				if (curr_line != lines.size()) {
					curr_line++;
				}
				else if (curr_line==lines.size()) {

					displaying = false;
				}
			}
		}
		
			App->gui->DeleteElement(dialogue_box);
			App->gui->DeleteElement(visible_text);
		
	}*/
}

void Dialogue::Update()
{
	if (displaying) {
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			displaying = false;
			App->gui->DeleteElement(dialogue_box);
			App->gui->DeleteElement(visible_text);
		}
	}
}



void Dialogue::Clean()
{
	for (int i = 0; i < lines.size();i++) {
		delete lines[i];
	}
}
