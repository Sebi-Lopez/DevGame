#include "j1App.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Module.h"
#include "p2Log.h"

j1Collision::j1Collision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_CAR] = false;
	matrix[COLLIDER_WALL][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_WALL][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_WALL][COLLIDER_BALL] = true; // false;
	matrix[COLLIDER_WALL][COLLIDER_BALL2] = false;
	matrix[COLLIDER_WALL][COLLIDER_GOD] = false;
	matrix[COLLIDER_WALL][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_WALL][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER1_EXPLOSION] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER2_EXPLOSION] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_CAR] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_L] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_S] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BALL] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BALL2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_G] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_H] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER2_EXPLOSION] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_CAR] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_BALL2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER1_EXPLOSION] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER2_EXPLOSION] = true;


	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_CAR] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BALL] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BALL2] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER2_EXPLOSION] = false;

	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_CAR] = true;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_BALL] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_BALL2] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER2_EXPLOSION] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_CAR] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BALL2] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER2_EXPLOSION] = false;

	matrix[COLLIDER_CAR][COLLIDER_WALL] = false;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_CAR][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_CAR][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_CAR][COLLIDER_CAR] = false;
	matrix[COLLIDER_CAR][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_CAR][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_CAR][COLLIDER_BALL] = true;
	matrix[COLLIDER_CAR][COLLIDER_BALL2] = true;
	matrix[COLLIDER_CAR][COLLIDER_GOD] = false;
	matrix[COLLIDER_CAR][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_CAR][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER1_EXPLOSION] = true;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER2_EXPLOSION] = true;



	matrix[COLLIDER_POWERUP_L][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_L][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_CAR] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_BALL] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_BALL2] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_GOD] = true;
	matrix[COLLIDER_POWERUP_L][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_L][COLLIDER_PLAYER2_EXPLOSION] = false;


	matrix[COLLIDER_POWERUP_S][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_S][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_CAR] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_BALL] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_BALL2] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_GOD] = true;
	matrix[COLLIDER_POWERUP_S][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_S][COLLIDER_PLAYER2_EXPLOSION] = false;

	matrix[COLLIDER_BALL][COLLIDER_WALL] = true; // false;
	matrix[COLLIDER_BALL][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BALL][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BALL][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_BALL][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BALL][COLLIDER_CAR] = false;
	matrix[COLLIDER_BALL][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_BALL][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_BALL][COLLIDER_BALL] = false;
	matrix[COLLIDER_BALL][COLLIDER_BALL2] = false;
	matrix[COLLIDER_BALL][COLLIDER_GOD] = false;
	matrix[COLLIDER_BALL][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_BALL][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_BALL][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_BALL][COLLIDER_PLAYER2_EXPLOSION] = false;

	matrix[COLLIDER_BALL2][COLLIDER_WALL] = false;
	matrix[COLLIDER_BALL2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BALL2][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BALL2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BALL2][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_BALL2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BALL2][COLLIDER_CAR] = false;
	matrix[COLLIDER_BALL2][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_BALL2][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_BALL2][COLLIDER_BALL] = false;
	matrix[COLLIDER_BALL2][COLLIDER_BALL2] = false;
	matrix[COLLIDER_BALL2][COLLIDER_GOD] = false;
	matrix[COLLIDER_BALL2][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_BALL2][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_BALL2][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_BALL2][COLLIDER_PLAYER2_EXPLOSION] = false;


	matrix[COLLIDER_GOD][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_GOD][COLLIDER_WALL] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_CAR] = false;
	matrix[COLLIDER_GOD][COLLIDER_POWERUP_L] = true;
	matrix[COLLIDER_GOD][COLLIDER_POWERUP_S] = true;
	matrix[COLLIDER_GOD][COLLIDER_BALL] = false;
	matrix[COLLIDER_GOD][COLLIDER_BALL2] = false;
	matrix[COLLIDER_GOD][COLLIDER_GOD] = false;
	matrix[COLLIDER_GOD][COLLIDER_POWERUP_G] = true;
	matrix[COLLIDER_GOD][COLLIDER_POWERUP_H] = true;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER2_EXPLOSION] = false;




	matrix[COLLIDER_POWERUP_G][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_G][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_CAR] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_BALL] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_BALL2] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_GOD] = true;
	matrix[COLLIDER_POWERUP_G][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_G][COLLIDER_PLAYER2_EXPLOSION] = false;


	matrix[COLLIDER_POWERUP_H][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_H][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_CAR] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_BALL] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_BALL2] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_GOD] = true;
	matrix[COLLIDER_POWERUP_H][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_H][COLLIDER_PLAYER2_EXPLOSION] = false;


	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_CAR] = true;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_BALL] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_BALL2] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER1_EXPLOSION][COLLIDER_PLAYER2_EXPLOSION] = false;

	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_CAR] = true;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_POWERUP_L] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_POWERUP_S] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_BALL] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_BALL2] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_POWERUP_G] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_POWERUP_H] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_PLAYER1_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER2_EXPLOSION][COLLIDER_PLAYER2_EXPLOSION] = false;
}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
{
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
bool j1Collision::Update(float dt)
{

	DebugDraw();
	return true;
}

void j1Collision::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
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
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_CAR: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_POWERUP_L: // pink
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_POWERUP_S: // pink
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_BALL:		// IDK
			App->render->DrawQuad(colliders[i]->rect, 0, 146, 146, alpha);
			break;
		case COLLIDER_BALL2:	// IDK
			App->render->DrawQuad(colliders[i]->rect, 0, 146, 146, alpha);
			break;
		case COLLIDER_GOD:
			App->render->DrawQuad(colliders[i]->rect, 127, 255, 0, alpha);
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
	// TODO 0: Return true if there is an overlap
	// between argument "r" and property "rect"

	bool ret = true;

	if (r.x + r.w < rect.x) ret = false;
	else if (r.x > rect.x + rect.w) ret = false;
	else if (r.y + r.h < rect.y)ret = false;
	else if (r.y > rect.h + rect.y)ret = false;

	return ret;
}