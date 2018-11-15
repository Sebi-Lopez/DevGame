#include "j1App.h"
#include "j1Entity.h"
#include "j1Collision.h"
#include "j1Entities.h"
#include "j1Render.h"
#include "j1Scene.h"

#include "Entity_Player.h"

j1Entity::j1Entity( int x, int y) : position(x, y)
{
}

j1Entity::~j1Entity()
{

}

const Collider* j1Entity::GetCollider() const
{
	return collider;
}

void j1Entity::Draw()
{
	SDL_Rect r = animation->GetCurrentFrame();
	App->render->Blit(sprites, (int)position.x, (int)position.y, &r, 1.0F, App->entities->player->flip);
	if(collider!=nullptr)
		collider->SetPos(position.x, position.y);
	
	
}

void j1Entity::OnCollision(Collider* collider)
{

}