#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load("gui/HUD.png");
	
	for (std::list<UIElement*>::const_iterator it = elements.cbegin(); it != elements.cend(); it++) {
		it._Ptr->_Myval->Start();
	}
	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	for (std::list<UIElement*>::const_iterator it = elements.cbegin(); it != elements.cend(); it++) {

		if (it._Ptr->_Myval->active)
			it._Ptr->_Myval->PreUpdate();
	}
	
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{


	for (std::list<UIElement*>::const_iterator it = elements.cbegin(); it != elements.cend(); it++) {

		if (it._Ptr->_Myval->active)
			it._Ptr->_Myval->Update();
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	DeleteElements();
	App->tex->UnLoad(atlas);

	return true;
}

UIElement * j1Gui::CreateElement(GuiType type)
{
	UIElement* ret = nullptr;

	switch (type)
	{
	case GuiType::image:
		ret = new GuiImage();
		ret->type = image;
		ret->texture = atlas;
		break;

	case GuiType::text:
		ret = new GuiText();
		ret->type = text;
		ret->texture = nullptr;
		ret->texture_rect.x = 0;
		ret->texture_rect.y = 0;

		break;

	case GuiType::button:
		ret = new GuiButton();
		ret->type = button;
		ret->texture = atlas;
		break;

	case GuiType::window:
		ret = new Window();
		ret->type = window;
		ret->texture = atlas;
		break;

	case GuiType::dialog_box:
		ret = new UI_DialogBox();
		ret->type = dialog_box;
		ret->texture = atlas;
		break;

	case GuiType::UI_string:
		ret = new UI_String();
		ret->type = UI_string;
		ret->texture = atlas;
		break;
	}
	if (ret != nullptr) {
		ret->pos.x = 0;
		ret->pos.y = 0;
		//ret->texture = atlas;
		ret->active = true;
		ret->Start();
		elements.push_back(ret);
	}

	return ret;
}

UIElement * j1Gui::CreateElement(GuiType type, const char* path)
{

	UIElement* ret = nullptr;

	switch (type)
	{
	case GuiType::image:
		ret = new GuiImage();
		ret->type = image;
		break;

	case GuiType::text:
		ret = new GuiText();
		ret->type = text;
		ret->texture = nullptr;
		break;

	case GuiType::button:
		ret = new GuiButton();
		ret->type = button;
		break;
	case GuiType::window:
		ret = new Window();
		ret->type = window;
		break;

	}

	if (ret != nullptr) {
		ret->pos.x = 0;
		ret->pos.y = 0;
		ret->texture = App->tex->Load(path);
		ret->active = true;
		ret->Start();
		elements.push_back(ret);
	}

	return ret;
}

void j1Gui::DeleteElements()
{
	for (std::list<UIElement*>::const_iterator it = elements.cbegin(); it != elements.cend(); it++) {
		if (it._Ptr->_Myval != nullptr)
			delete it._Ptr->_Myval;
	}
}

void j1Gui::DeleteElement(UIElement * del)
{

	std::list<UIElement*>::iterator aux = std::find(elements.begin(), elements.end(), del);

	elements.erase(aux);
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

void GuiImage::Start()
{
	//this->texture = atlas;
}

void GuiImage::Update()
{
	if (active) {
		App->render->toDraw(texture,10000, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &texture_rect);
	}


}

void GuiText::Start()
{
	//font = App->font->Load("fonts/ReturnofGanon.ttf");
}



void GuiText::Update()
{
	if (texture != nullptr) {
		App->tex->UnLoad(this->texture);
	}
	if (active) {

		this->texture = App->font->Print(str.c_str());
		App->font->CalcSize(str.c_str(), texture_rect.w, texture_rect.h);
		if (movable) {
				App->render->toDraw(texture, 10000, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &texture_rect);
			
		}
		else {
			App->render->toDraw(texture,0, pos.x, pos.y, &texture_rect);
		}
		
	}
}

void GuiButton::Start()
{
	state = standard;

	text = new GuiText();
	for (int i = standard; i < GuiButton::Unknown; i++) {
		image[i] = new GuiImage();
		image[i]->active = true;
	}

	text->pos.y = this->pos.y;

}

void GuiButton::Update()
{


	if (state != disabled) {

		iPoint mousepos;
		App->input->GetMousePosition(mousepos.x, mousepos.y);

		iPoint mousemotion;
		App->input->GetMouseMotion(mousemotion.x, mousemotion.y);
		if (((mousepos.x > pos.x) && (mousepos.x < pos.x + image[standard]->texture_rect.w)) && (mousepos.y > pos.y) && (mousepos.y < pos.y + image[standard]->texture_rect.h)) {

			state = hover;

			if (App->input->GetMouseButtonDown(RI_MOUSE_LEFT_BUTTON_DOWN) == KEY_REPEAT) {
				state = left_clicked;
				if (movable) {
					this->Move(mousemotion.x, mousemotion.y);
				}

			}
			if (App->input->GetMouseButtonDown(RI_MOUSE_RIGHT_BUTTON_DOWN) == KEY_REPEAT) {
				state = right_clicked;
			}
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) {
				state = disabled;
			}
		}

		else {
			state = standard;
		}
		image[state]->pos.x = this->pos.x;
		image[state]->pos.y = this->pos.y;
		text->pos.x = this->pos.x + text->texture_rect.w;
		text->pos.y = this->pos.y;

		if (state > standard && state < Unknown) {
			image[state]->Update();
		}
		else
			image[standard]->Update();
		this->text->Update();

	}
}
void UIElement::Set_Interactive_Box(SDL_Rect new_rect)
{
	texture_rect = new_rect;
}
void UIElement::Set_Active_state(bool act)
{
	active = act;
}
void UIElement::Move(int x, int y) {

	pos.x += x;
	pos.y += y;

	for (std::list<UIElement*>::const_iterator it = children.cbegin(); it != children.cend(); it++) {
		it._Ptr->_Myval->Move(x, y);
	}


}
void GuiInput::Start() {



}
void GuiInput::Update() {

	text->Update();


}
GuiInput::GuiInput() {
	//text->string = "Hello world";
	//text->pos.create(1920 / 2, 950);
}

Window::Window()
{
	selector = nullptr;

}
Window::~Window()
{
}

void Window::Update()
{
	if (active) {
		App->render->toDraw(texture, 9999, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &texture_rect);
		if (selector != nullptr) {
			if (this->selected != nullptr) {
				selector->active = true;
				selector->pos.x = selected->pos.x - 5;
				selector->pos.y = selected->pos.y - 5;
			}
		}

		for (std::list<UIElement*>::const_iterator it = win_elements.cbegin(); it != win_elements.cend(); it++) {
			if (Inside(it._Ptr->_Myval)) {
				it._Ptr->_Myval->active = true;
			}
		}
	}
}


void Window::CleanUp()
{
	if (!win_elements.empty()) {
		win_elements.clear();
	}
	selected = nullptr;
}

void Window::Disable()
{
	active = false;
	if (!win_elements.empty()) {
		selector->active = false;
		if (selected != nullptr) {
			selected = win_elements.front();
		}
		for (std::list<UIElement*>::const_iterator it = win_elements.cbegin(); it != win_elements.cend(); it++) {
			it._Ptr->_Myval->active = false;
		}
	}


}

void Window::AddElement(UIElement * element)
{
	if (element != nullptr) {
		element-> max_prior = true;
		if (!win_elements.empty()) {
			if (win_elements.back()->pos.x + element->texture_rect.w + offset_x < pos.x + texture_rect.w - offset_x) {
				element->pos.x = win_elements.back()->pos.x + element->texture_rect.w + offset_x;
				element->pos.y = win_elements.back()->pos.y;
				win_elements.push_back(element);
			}
			else {
				element->pos.x = pos.x + offset_x;
				element->pos.y = win_elements.back()->pos.y + offset_y + element->texture_rect.h;
				win_elements.push_back(element);
			}
		}
		else {
			element->pos.x = pos.x + offset_x;
			element->pos.y = pos.y + offset_y;
			win_elements.push_back(element);
			selected = element;
		}
	}

}

bool Window::Inside(UIElement*element)
{
	if ((element->pos.x < pos.x + this->texture_rect.w) && (element->pos.x > pos.x) && (element->pos.y > pos.y) && (element->pos.y < pos.y + this->texture_rect.h)) {
		return true;
	}
	else {
		return false;
	}
}

void Window::Scroll()
{
}

void Window::SetOffset(int x, int y)
{
	offset_x = x;
	offset_y = y;
}

void Window::Set_Sel_Rect(SDL_Rect rect)
{
	selector->texture_rect = rect;
}

void Window::Move_Sel_forward()
{
	if (selected != nullptr) {
		selected = Next();
	}
}

UIElement * Window::Next()
{
	if(selected!=nullptr){
		if (!win_elements.empty()) {
			if (selected == win_elements.back()) {
				return win_elements.back();
			}
			else {
				for (std::list<UIElement*>::const_iterator it = win_elements.cbegin(); it != win_elements.cend(); it++) {
					if (selected == it._Ptr->_Myval) {
						if (selected == win_elements.back()) {
							return win_elements.back();
						}
						else {
							it++;
							if (it._Ptr != nullptr)
								return it._Ptr->_Myval;
							else
								return win_elements.back();
						}
					}
				}
			}
		}
	}
}

UIElement * Window::Prev()
{
	if (selected != nullptr) {
		if (!win_elements.empty()) {
			if (selected == win_elements.front()) {
				return win_elements.front();
			}
			for (std::list<UIElement*>::const_iterator it = win_elements.cend(); it != win_elements.cbegin(); it--) {
				if (selected == it._Ptr->_Myval) {
					if (selected == win_elements.front()) {
						return win_elements.front();
					}
					else {
						it--;
						if (it._Ptr != nullptr)
							return it._Ptr->_Myval;
						else
							return win_elements.back();
					}
				}


			}
		}
	}
	return nullptr;
}

UIElement * Window::current()
{
	return selected;
}


void Window::Sel_First()
{
	if (!win_elements.empty())
		selected = win_elements.front();
}

void Window::Start_Sel(SDL_Rect rect)
{
	selected = nullptr;
	selector = (GuiImage*)App->gui->CreateElement(GuiType::image);
	selector->pos.x = this->pos.x + offset_x - 5;
	selector->pos.y = this->pos.y + offset_y - 5;
	selector->active = false;
	Set_Sel_Rect(rect);
}

bool Window::Empty()
{
	return win_elements.empty();
}

void Window::clear()
{
	if (!win_elements.empty()) {
		win_elements.clear();
	}
	selected = nullptr;
}

void Window::Move_Sel_backwards()
{
	if (selected != nullptr) {
		selected = Prev();
	}
}

void Window::Move_Sel_up()
{
	if (selected != nullptr) {
		if (!win_elements.empty()) {
			if (selected->pos.y != win_elements.front()->pos.y) {
				for (std::list<UIElement*>::const_iterator it = win_elements.cbegin(); it != win_elements.cend(); it++) {
					if (selected != nullptr) {
						if ((selected->pos.y == it._Ptr->_Myval->pos.y + offset_y + it._Ptr->_Myval->texture_rect.h) && (selected->pos.x == it._Ptr->_Myval->pos.x)) {
							selected = it._Ptr->_Myval;
						}
					}
				}
			}
		}
	}
}

void Window::Move_Sel_down()
{
	if(selected!=nullptr){
		if (!win_elements.empty()) {
			if (selected->pos.y != win_elements.back()->pos.y) {
				for (std::list<UIElement*>::const_iterator it = win_elements.cbegin(); it != win_elements.cend(); it++) {
					if (selected != nullptr) {
						if ((selected->pos.y <= it._Ptr->_Myval->pos.y - offset_y - it._Ptr->_Myval->texture_rect.h) && (selected->pos.x == it._Ptr->_Myval->pos.x)) {
							selected = it._Ptr->_Myval;
							break;
						}
					}
				}
			}
		}
	}
}

void Window::Select(UIElement * el)
{
	selected = el;
}

UIElement * Window::Selected()
{
	if (selected != nullptr)
		return selected;
	else return nullptr;
}


UI_DialogBox::~UI_DialogBox()
{
	RELEASE(Box);
}

bool UI_DialogBox::Update_Draw()
{
	//blit img
	if (Box)
	{
		App->render->toDraw(texture, 10000, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &texture_rect);
	}
	//Child_Update_Draw();
	return false;
}

void UI_DialogBox::SetImage(const GuiImage* new_img)
{
	Box = (GuiImage*)new_img;
}

void UI_DialogBox::SetText(const GuiText* new_txt)
{
	Dialog_Text = (GuiText*)new_txt;
}

void UI_DialogBox::SetViewport(SDL_Rect new_rect)
{
	Dialog_ViewPort = new_rect;
}

bool UI_String::Update_Draw()
{
	if (active)
	{
		SDL_Rect tmp = { 0, 0, 405,75 };
		App->render->toDraw(texture, 10000, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &tmp);
		App->render->toDraw(texture, 10000, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &texture_rect);

	}

	//Child_Update_Draw();

	return true;
}


void UI_String::SetBlitTimeMS(int time)
{
	blit_time = time;
}

void UI_String::ForcedFinish()
{
	blit_text = text;
	if (text_texture)
		App->tex->UnLoad(text_texture);

	text_texture = App->font->Print(blit_text.c_str());
}

void UI_String::Update()
{

	if (dialog_state == MID_TEXT && active)
		BlitDialog();

	//Return_state();
}

bool UI_String::Set_String(char* new_text)
{
	text = new_text;
	blit_text.clear();

	if (text_texture)
		App->tex->UnLoad(text_texture);

	char_blit_time.Start();
	dialog_state = MID_TEXT;

	return (text.c_str() != nullptr) ? true : false;
}

void UI_String::Load_text_texture()
{
	text_texture = App->font->Print(text.c_str());
}


void UI_String::BlitDialog()
{
	if (blit_text.size() < text.size())
	{
		if (char_blit_time.Read() >= (blit_time))
		{
			blit_text += text.at(blit_text.size());
			//looks if the text is already loaded and unloads
			if (text_texture)
				App->tex->UnLoad(text_texture);

			text_texture = App->font->Print(blit_text.c_str());
			char_blit_time.Start();
		}
	}
	else dialog_state = FINISHED_TEXT;


}

