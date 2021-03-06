#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Input.h"

#define VSYNC true

j1Render::j1Render() : j1Module()
{
	name.create("renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

// Destructor
j1Render::~j1Render()
{}

// Called before render is available
bool j1Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;
	// load flags
	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if(config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(App->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		camera.w = App->win->screen_surface->w;
		camera.h = App->win->screen_surface->h;
		camera.x = 0;
		camera.y = 0;

		culling_cam = camera;

	}

	// Variables
	cam_boundaries.x = 0;
	cam_boundaries.y = 0;
	cam_boundaries.w = App->win->screen_surface->w;
	cam_boundaries.h = App->win->screen_surface->h;

	//Camera Shake

	quantity = 0;
	duration = 0;
	counter = 1;
	shake_interval = 3;
	shake_ret = 0;
	trigger_shake = false;

	return ret;
}

// Called before the first frame
bool j1Render::Start()
{
	LOG("render start");
	// back background
	SDL_RenderGetViewport(renderer, &viewport);

	return true;
}

// Called each loop iteration
bool j1Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool j1Render::Update(float dt) {

	if (App->debug == true) {
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			App->render->MoveCam(0, 200.0f * dt);

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			App->render->MoveCam(0, -200.0f * dt);

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			App->render->MoveCam(-200.0f * dt, 0);

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) 
			App->render->MoveCam(200.0f * dt, 0);
	}
	else if(cam_travel == false) {
		//if (camera.x > App->scene_manager->GetCurrentScene()->camera_limit.x && camera.x < App->scene_manager->GetCurrentScene()->camera_limit.x + App->scene_manager->GetCurrentScene()->camera_limit.w)
		//	if (camera.y > App->scene_manager->GetCurrentScene()->camera_limit.y && camera.y < App->scene_manager->GetCurrentScene()->camera_limit.y + App->scene_manager->GetCurrentScene()->camera_limit.y)
		if(App->scene_manager->GetCurrentScene()->follow_cam == true)
			SetCamPos(-(App->player->GetPos().x - camera.w / 2), -(App->player->GetPos().y - camera.h / 2));
		else {
			SetCamPos(-(App->scene_manager->GetCurrentScene()->GetCurrentRoom()->coords.x * ROOM_W), -(App->scene_manager->GetCurrentScene()->GetCurrentRoom()->coords.y * ROOM_H - (camera.h/2 - ROOM_H/2)));
		}

	}
	if(trigger_shake == true )
		App->render->camera.x += shake_ret;
	App->render->Coord_Shake();

	return true;
}

bool j1Render::PostUpdate()
{

	culling_cam.x = -camera.x;
	culling_cam.y = -camera.y;

	SDL_Rect cam = App->render->culling_cam;

	if (sprites_toDraw.size() > 1) {
		for (int it = 0; it < sprites_toDraw.size() - 1; it++) {
			if(sprites_toDraw[it] != nullptr)
			if (sprites_toDraw[it]->priority > sprites_toDraw[it + 1]->priority) {
				SWAP(sprites_toDraw[it], sprites_toDraw[it + 1]);
			}
		}
	}

	for (int it = 0; it < sprites_toDraw.size(); it++) {
		if(sprites_toDraw[it]->pos.x + sprites_toDraw[it]->rect->w >= cam.x && sprites_toDraw[it]->pos.x <= cam.x + cam.w)
			if(sprites_toDraw[it]->pos.y + sprites_toDraw[it]->rect->h > cam.y && sprites_toDraw[it]->pos.y < cam.y + cam.h)
				App->render->Blit(sprites_toDraw[it]->texture, sprites_toDraw[it]->pos.x, sprites_toDraw[it]->pos.y, sprites_toDraw[it]->rect);
		RELEASE(sprites_toDraw[it]);
	}

	//for (int it = 0; it < max_prior_sprites.size(); it++) {
	//	if (max_prior_sprites[it]->pos.x + max_prior_sprites[it]->rect->w >= cam.x && max_prior_sprites[it]->pos.x <= cam.x + cam.w)
	//		if (max_prior_sprites[it]->pos.y + max_prior_sprites[it]->rect->h > cam.y && max_prior_sprites[it]->pos.y < cam.y + cam.h)
	//			App->render->Blit(max_prior_sprites[it]->texture, max_prior_sprites[it]->pos.x, max_prior_sprites[it]->pos.y, max_prior_sprites[it]->rect);
	//	RELEASE(max_prior_sprites[it]);
	//}

	sprites_toDraw.clear();
	//max_prior_sprites.clear();

	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

// Called before quitting
bool j1Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

// Load Game State
bool j1Render::Load(pugi::xml_node& data)
{
	camera.x = data.child("camera").attribute("x").as_int();
	camera.y = data.child("camera").attribute("y").as_int();

	return true;
}

// Save Game State
bool j1Render::Save(pugi::xml_node& data) const
{
	pugi::xml_node cam = data.append_child("camera");

	cam.append_attribute("x") = camera.x;
	cam.append_attribute("y") = camera.y;

	return true;
}

void j1Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void j1Render::MoveCam(float x, float y)
{
	camera.x -= x;
	camera.y += y;
	culling_cam.x += x;
	culling_cam.y -= y;
}

void j1Render::SetCamPos(float x, float y)
{
	camera.x = floor(x);
	camera.y = floor(y);
	culling_cam.x = -floor(x);
	culling_cam.y = -floor(y);
}

void j1Render::SetCamBoundaries(SDL_Rect rect)
{
	cam_boundaries = rect;
}

void j1Render::CamBoundOrigin()
{
	cam_boundaries.x = 0;
	cam_boundaries.y = 0;
	cam_boundaries.w = App->win->screen_surface->w;
	cam_boundaries.h = App->win->screen_surface->h;
}

void j1Render::ScaleCamBoundaries(int x, int y, int w, int h)
{
	cam_boundaries.x -= x;
	cam_boundaries.y -= y;
	cam_boundaries.w += w;
	cam_boundaries.h += h;
}

void j1Render::ScaleCamBoundaries(int scale)
{
	cam_boundaries.x -= scale;
	cam_boundaries.y -= scale;
	cam_boundaries.w += 2 * scale;
	cam_boundaries.h += 2 * scale;
}

bool j1Render::IsCameraCull(SDL_Rect rect)
{
	bool ret = true;

	SDL_Rect cam = culling_cam;

	if (App->scene_manager->GetCurrentScene()->curr_id == dungeon && App->scene_manager->dungeon_id != 6) {
		cam.h -= (culling_cam.h / 2 - ROOM_H / 2) * 2;
		cam.y += (culling_cam.h / 2 - ROOM_H / 2);
	}


	if (rect.x + rect.w >= cam.x && rect.x <= cam.x + cam.w)
		if (rect.y + rect.h > cam.y && rect.y < cam.y + cam.h)
			ret = false;

	return ret;
}

void j1Render::toDraw(SDL_Texture * texture, float priority, int x, int y, SDL_Rect* section, bool prior , float speed, double angle, int pivot_x, int pivot_y)
{
	Sprite* aux = new Sprite();
	aux->pos.x = x;
	aux->pos.y = y;
	aux->texture = texture;
	aux->rect = section;
	aux->priority = priority;

	aux->speed = speed;
	aux->angle = angle;
	aux->pivot_x = pivot_x;
	aux->pivot_y = pivot_y;

	App->render->sprites_toDraw.push_back(aux);
}

void j1Render::Coord_Shake()
{

	counter++;
	
	if(counter % shake_interval == 0){
		if ((counter % 2) == 0)
			shake_ret = (camera.w / 10) * ( quantity / 100 );
		else
			shake_ret = -((camera.w / 10) * ( quantity / 100 ) );
	}
	else {
		if(shake_ret < 0)
			shake_ret = -((camera.w / 10) * (quantity / 100));
		else
			shake_ret = (camera.w / 10) * (quantity / 100);
	}
			
	quantity -= quantity / (duration * 60);
	

	if (counter >= duration * 60) {
		trigger_shake = false;
		shake_ret = 0;
		counter = 0;
		duration = 0;
	}
	
}

void j1Render::Activate_Shake(float quantity_, float duration_) {
	if (trigger_shake != true) {
		trigger_shake = true;
		quantity = quantity_;
		duration = duration_;

		//repair numbers

		if (quantity > 100) quantity = 100;
		if (quantity < 0) quantity = 0;

		if (duration < 0) duration *= -1;
		if (duration > 10) duration = 10;
	}
}

void j1Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void j1Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

iPoint j1Render::ScreenToWorld(int x, int y) const
{
	iPoint ret;
	int scale = App->win->GetScale();

	ret.x = (x - camera.x / scale);
	ret.y = (y - camera.y / scale);

	return ret;
}

// Blit to screen
bool j1Render::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, double angle, int pivot_x, int pivot_y) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * scale;
	rect.y = (int)(camera.y * speed) + y * scale;

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= scale;
	rect.h *= scale;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if(pivot_x != INT_MAX && pivot_y != INT_MAX)
	{
		pivot.x = pivot_x;
		pivot.y = pivot_y;
		p = &pivot;
	}

	if(SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
	{
		//LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if(use_camera)
	{
		rec.x = (int)(camera.x + rect.x * scale);
		rec.y = (int)(camera.y + rect.y * scale);
		rec.w *= scale;
		rec.h *= scale;
	}

	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;

	if(use_camera)
		result = SDL_RenderDrawLine(renderer, camera.x + x1 * scale, camera.y + y1 * scale, camera.x + x2 * scale, camera.y + y2 * scale);
	else
		result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for(uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor));
		points[i].y = (int)(y + radius * sin(i * factor));
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}