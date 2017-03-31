#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Player.h"

j1Collision::j1Collision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_BUSH] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PL_WEAPON] = false;
	matrix[COLLIDER_WALL][COLLIDER_ITEM] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BUSH] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PL_WEAPON] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ITEM] = true;

	matrix[COLLIDER_BUSH][COLLIDER_BUSH] = false;
	matrix[COLLIDER_BUSH][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BUSH][COLLIDER_PL_WEAPON] = true;
	matrix[COLLIDER_BUSH][COLLIDER_ITEM] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PL_WEAPON] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ITEM] = false;

	matrix[COLLIDER_PL_WEAPON][COLLIDER_PL_WEAPON] = false;
	matrix[COLLIDER_PL_WEAPON][COLLIDER_ITEM] = false;

	matrix[COLLIDER_ITEM][COLLIDER_ITEM] = false;

}

j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
{
	bool ret = true;
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return ret;
}

bool j1Collision::Update(float dt)
{
	bool ret = true;
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	DebugDraw();

	return ret;
}

void j1Collision::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_BUSH: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_WALL: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_ENEMY: // Purple
			App->render->DrawQuad(colliders[i]->rect, 204, 0, 204, alpha);
			break;
		case COLLIDER_PL_WEAPON:
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_ITEM:
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ARROW:
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		}
	}
}

bool j1Collision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool j1Collision::EraseCollider(Collider* collider)
{
	if (collider != nullptr)
	{
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] == collider)
			{
				collider->to_delete = true;
				break;
			}
		}
	}
	return false;
}

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}
