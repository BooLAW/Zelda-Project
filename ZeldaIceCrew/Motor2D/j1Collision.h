#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 50

#define FARLANDS iPoint({5000, 5000})

#include "j1Module.h"
#include "p2Defs.h"
#include "Animation.h"
class SDL_Rect;
enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_ACTION,
	COLLIDER_BLOCK,
	COLLIDER_ENEMY,
	COLLIDER_PL_WEAPON,
	COLLIDER_ITEM,
	COLLIDER_ARROW,
	COLLIDER_TO_OVERWORLD_SHOP,
	COLLIDER_TO_OVERWORLD_HOUSE,
	COLLIDER_TO_SHOP,
	COLLIDER_TO_HOUSE,
	COLLIDER_TO_DUNGEON,
	COLLIDER_DUNGEON_DOORWAY,
	COLLIDER_DUNGEON_UP,
	COLLIDER_DUNGEON_DOWN,
	COLLIDER_DUNGEON_LEFT,
	COLLIDER_DUNGEON_RIGHT,

	COLLIDER_ENEMY_PROJECTILE
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;

	bool active = true;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	//Directions ColliderHit(const SDL_Rect& r) const;
	bool CheckCollision(const SDL_Rect& r) const;
};

class j1Collision : public j1Module
{
public:

	j1Collision();
	~j1Collision();

	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
	bool EraseCollider(Collider* collider);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__
