#ifndef __j1ENTITY_H__
#define __j1ENTITY_H__

#include "p2Point.h"
#include "Animation.h"
#include"j1Module.h"

struct SDL_Texture;
struct Collider;

class j1Entity
{

public:
	Animation* animation;
	Collider* collider = nullptr;
	fPoint position;
	int entitytype = 0;
	SDL_Texture* texture;
	

public:
	j1Entity(int x, int y);
	virtual ~j1Entity();

	const Collider* GetCollider() const;

	virtual void Update(float dt) {};
	bool Draw();
	virtual void OnCollision(Collider* collider);

	virtual void SetAnimation(pugi::xml_node& node, Animation& animation);

	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}

	
};

#endif // __ENTITY_H__
