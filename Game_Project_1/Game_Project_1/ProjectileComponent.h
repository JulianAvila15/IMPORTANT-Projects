#pragma once
#include "ECS.h"
#include "Components.h"
#include "2Dvector.h"

class ProjectileComponent : public Component
{

public:

	ProjectileComponent(int rng, int sp, Vector2D vel):  range (rng) ,  speed (sp), velocity(vel)
	{}

	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getcomponent <TransformComponent>(); 
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed; // add speed to distance each frame
	
		if (distance > range)
		{
			entity->destroy();
			
		}
	}

private:
	TransformComponent* transform = NULL;

	int range=0, speed=0, distance=0;
	Vector2D velocity;
};