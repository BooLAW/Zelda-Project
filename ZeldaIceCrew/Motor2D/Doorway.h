#ifndef __DOORWAY_H__
#define __DOORWAY_H__

#include "EntityManager.h"
#include "j1Collision.h"
#include "Entity.h"
#include "j1Textures.h"

#define CHANGE_SPEED 10

#define DOORWAY_UP		iPoint( { 16 * 31, 16 * 3  } )
#define DOORWAY_DOWN	iPoint( { 16 * 31, 16 * 32 } )
#define DOORWAY_LEFT	iPoint( { 16*3 , 16*17  } )
#define DOORWAY_RIGHT	iPoint( { 16 * 60, 16 * 17  } )
#define DOORWAY_SIZE	iPoint( { 32, 16 } )

class Scene;

enum DWSTATE {
	open = 0,
	close,
	LASTDWSTATE
};

enum DOORWAYTYPE {
	dw_cam = 0,
	dw_dungeon,
	dw_scene,
	__LAST_DOORWAYTYPE
};

class Doorway {
public:
	virtual void Start();
	virtual void SetUp(uint dir);
	virtual void Update(float dt);
	virtual bool Cross() { return true;  };
	virtual void CleanUp();

	virtual void SetUp() {};

	virtual void Draw();

	virtual void SetTarget(Scene*) {};

	virtual void SetPos(int x, int y) {
		pos.x = x;
		pos.y = y;
	};

public:
	uint state;
	uint direction;
	Collider* collider;
	fPoint target_pos;

	fPoint pos;

	bool animating = false;

	SDL_Texture* tex;
	SDL_Rect sprite[Direction::LastDir][LASTDWSTATE];

protected:
	bool crossed = false;

};

class DwDungeon : public Doorway {
public:
	bool Cross();

	void SetUp();
	void Draw();
	void SetPos(int x, int y);
};

class DwScene : public Doorway {
	public:
	bool Cross();

	void SetUp(uint dir);

	void SetTarget(Scene* scene) { target = scene; };
	Scene* GetTarget() { return target; };

private:
	Scene* target;
};

class DwCam : public Doorway {
public:
	bool Cross();

	void SetTargetPos(float x, float y) { target = { x, y }; };
	fPoint GetTargetPos() { return target; };

private:
	fPoint target;

};

#endif // !_DOORWAY_H__