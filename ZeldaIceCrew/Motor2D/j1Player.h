#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Map.h"

#define MAX_SPRITE_FRAMES 8

#define PL_OFFSET 12

enum Direction {
	FirstDir = 0,
	Up,
	Left,
	Right,
	Down,
	LastDir
};

class j1Player : public j1Module {
public:
	enum Sprites {
		__FIRST = 0,
		Idle,
		Walk,
		Pickup,
		Pull,
		Walk_Shield,
		Push,
		Unknown,
		__LAST
	};

private:

	SDL_Texture* Link_Movement = nullptr;

	// All player sprites / animations
	Animation animations[Sprites::__LAST][Direction::LastDir];
	SDL_Rect sprites[Sprites::__LAST][Direction::LastDir][MAX_SPRITE_FRAMES];

	unsigned int curr_dir;

public:
	j1Player();
	virtual ~j1Player();

private:
	bool Awake();
	bool Start();
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();

public:
	bool SetPosTile(int x, int y);
	Point<float> GetPos();

};

#endif // !__PLAYER_H__
