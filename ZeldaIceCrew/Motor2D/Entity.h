#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "j1Textures.h"
#include "MathHelpers.h"
#include "j1Render.h"
#include "Log.h"

enum ENTITYTYPE
{
	drop = 0,
	item,
	block,
	enemy,
	bomb,
	doorway,
	npc,
	unknown
};


class Entity {
public:
	Entity() {};
	virtual ~Entity() {};
	virtual void Update(float dt) {};
	virtual void CleanUp();
	virtual void Draw(float dt) {};


public:

	void SetTexture(SDL_Texture* texture) {
		tex = texture;
		if (tex == nullptr)
			LOG("Error Setting Texture for entity ID: %d", type);
	}
	SDL_Texture* GetTexture() {
		return tex;
	}
	SDL_Rect GetRect() {
		return rect;
	}
	void SetRect(SDL_Rect rectangle) {
		rect = rectangle;
	}

	virtual int CheckSpace(float new_x, float new_y);

protected:
	SDL_Texture* tex = nullptr;
	SDL_Rect rect;
	bool inverse_draw = false;


public:
	bool to_delete = false;

	bool active = true;

	Collider* HitBox = nullptr;
	fPoint pos;
	uint type;

	iPoint room;

};


#endif // !__ENTITY_H__
