#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "SDL/include/SDL.h"
#include "Point.h"
#include "j1Module.h"
#include "j1PerfTimer.h"
#include <deque>

struct Sprite {
	SDL_Rect* rect;
	SDL_Texture* texture;

	fPoint pos;

	float speed;
	double angle;
	int pivot_x, pivot_y;
	bool max_priority = false;
	float priority;
};

class j1Render : public j1Module
{
public:

	j1Render();

	// Destructor
	virtual ~j1Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	// Utils
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	iPoint ScreenToWorld(int x, int y) const;

	// Draw & Blit
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

	void MoveCam(float x, float y);
	void SetCamPos(float x, float y);
	void SetCamBoundaries(SDL_Rect rect);
	void CamBoundOrigin();
	void ScaleCamBoundaries(int x, int y, int w, int h);
	void ScaleCamBoundaries(int scale);

	bool IsCameraCull(SDL_Rect rect);

	void toDraw(SDL_Texture* texture, float priority, int x, int y, SDL_Rect* section = NULL, bool prior = false, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX);

public:

	SDL_Renderer*	renderer;
	SDL_Rect		camera;
	SDL_Rect		culling_cam;
	SDL_Rect		viewport;
	SDL_Color		background;
	bool			cam_travel = false;
private:
	// camera
	SDL_Rect cam_boundaries;

	// Sprites Drawing
	std::deque<Sprite*> sprites_toDraw;

public:
	//Camera Shake
	void Coord_Shake();
	void Activate_Shake(float quantity_, float duration_);

protected:
	float quantity;
	float duration;
	int counter;
	int shake_interval;
	int shake_ret;
	bool trigger_shake;
};

#endif // __j1RENDER_H__