#include "j1App.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Module.h"
#include "p2Log.h"
#include "Brofiler/Brofiler.h"

j1Collision::j1Collision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_FLOOR][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_DEAD] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_END] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_GOD] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_ENEMY] = true;

	matrix[COLLIDER_DEAD][COLLIDER_DEAD] = false;
	matrix[COLLIDER_DEAD][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_DEAD][COLLIDER_END] = false;
	matrix[COLLIDER_DEAD][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DEAD][COLLIDER_GOD] = true;
	matrix[COLLIDER_DEAD][COLLIDER_ENEMY] = true;

	matrix[COLLIDER_END][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_END][COLLIDER_DEAD] = false;
	matrix[COLLIDER_END][COLLIDER_END] = false;
	matrix[COLLIDER_END][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_END][COLLIDER_GOD] = true;
	matrix[COLLIDER_END][COLLIDER_ENEMY] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_DEAD] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_END] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;

	matrix[COLLIDER_GOD][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_GOD][COLLIDER_DEAD] = false;
	matrix[COLLIDER_GOD][COLLIDER_END] = true;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_GOD][COLLIDER_GOD] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_DEAD] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_END] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::Update(float dt)
{
	BROFILER_CATEGORY("Collision Logic", Profiler::Color::LightSeaGreen);

	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
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

	return true;
}



// Called before render is available

bool j1Collision::PostUpdate()
{
	DebugDraw();
	return true;
}

void j1Collision::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		if (debug == false) debug = true;
		else debug = false;
		LOG("Showing Colliders ");
	}

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
		case COLLIDER_FLOOR: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY:
			App->render->DrawQuad(colliders[i]->rect, 255, 200, 0, alpha);
			break;
		case COLLIDER_END: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_DEAD: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;

		case COLLIDER_GOD:
			App->render->DrawQuad(colliders[i]->rect, 128, 0, 128, alpha);
			break;
		}
	}
}

// Called before quitting
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

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return !(r.x + r.w < rect.x || r.x > rect.x + rect.w || r.y + r.h < rect.y || r.y > rect.h + rect.y);
}