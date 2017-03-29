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

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
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
		break;

	case GuiType::text:
		ret = new GuiText();
		ret->type = text;
		ret->texture_rect.x = 0;
		ret->texture_rect.y = 0;
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
		ret->texture = atlas;
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

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

void GuiImage::Update()
{
	if (active) {
		App->render->Blit(texture, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &texture_rect);
	}

	
}

void GuiText::Update()
{
	if (active) {
		texture = App->font->Print(str.c_str());
		App->font->CalcSize(str.c_str(), texture_rect.w, texture_rect.h);

		App->render->Blit(texture, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &texture_rect);
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
}

Window::~Window()
{
}

void Window::Update()
{
	if (active) {
		App->render->Blit(texture, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &texture_rect);
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
}

void Window::Disable()
{
	active = false;
	for (std::list<UIElement*>::const_iterator it = win_elements.cbegin(); it != win_elements.cend(); it++) {
		it._Ptr->_Myval->active = false;
	}
	
}

void Window::AddElement(UIElement * element)
{
	if (element != nullptr) {
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
