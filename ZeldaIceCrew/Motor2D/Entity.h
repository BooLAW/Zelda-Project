#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "EntityManager.h"
#include "j1App.h"
#include "j1Textures.h"

enum ENTITYTYPE
{
	drop = 0,
	item,
	block,
	enemy,
	bomb,
	doorway,
	unknown
};


class Entity {
public:
	Entity() {};
	virtual ~Entity() {};
	virtual void Update(float dt) {};
	virtual void CleanUp() {
		if(tex != nullptr)
			App->tex->UnLoad(tex);
	}
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

protected:
	SDL_Texture* tex;
	SDL_Rect rect;
	bool inverse_draw = false;

public:
	fPoint pos;
	uint type;


};


#endif // !__ENTITY_H__
