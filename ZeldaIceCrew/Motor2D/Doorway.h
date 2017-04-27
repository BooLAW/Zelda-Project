#ifndef __DOORWAY_H__
#define __DOORWAY_H__

#include "EntityManager.h"
#include "j1Collision.h"
#include "Entity.h"


#define DOORWAY_UP		iPoint( { 32 * 25, 16 * 3  } )
#define DOORWAY_DOWN	iPoint( { 32 * 25, 32 * 16 } )
#define DOORWAY_LEFT	iPoint( { 32 * 11, 32 * 8 + 16  } )
#define DOORWAY_RIGHT	iPoint( { 32 * 40 - 16, 32 * 8 + 16  } )
#define DOORWAY_SIZE	iPoint( { 32, 16 } )

class Scene;

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

	virtual void SetTarget(Scene*) {};

	virtual void SetPos(int x, int y) {
		pos.x = x;
		pos.y = y;
	};

public:
	bool open = true;
	uint direction;
	Collider* collider;

	fPoint target_pos;

	fPoint pos;

protected:
	bool crossed = false;

};

class DwDungeon : public Doorway {
public:
	bool Cross();

	void SetPos(int x, int y);
};

class DwScene : public Doorway {
	public:
	bool Cross();

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