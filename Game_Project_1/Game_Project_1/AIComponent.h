#pragma once
#include "Components.h"
#include "2DVector.h"
#include <string>
#include <math.h>
using namespace std;
class AIMovementComponent : public Component
{
public:
	TransformComponent* transform;
	CollisionComponent* collision;
	float originX, originY;
	float Yveloc;
	bool inverseX = false;
	bool inverseY = false;
	SDL_Window* window;
	int temp;
	int randomInterval;
	
	AIMovementComponent(){}

	AIMovementComponent(SDL_Window* win)
	{
		window = win;
	}

	void init() override
	{
		//get information about the AI's transform and collision components

		if (!entity->hasComponent<TransformComponent>())//if entity does not have the transform component
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getcomponent<TransformComponent>();
		originX = transform->position.x;
		originY = transform->position.y;

		if (!entity->hasComponent<CollisionComponent>())//if entity does not have the transform component
		{
			entity->addComponent<CollisionComponent>();
		}
		collision = &entity->getcomponent<CollisionComponent>();
		if (collision->getTag() == "Enemy1")
		transform->velocity.x = .5;//When initialized, start moving at a constant speed

	}

	void update() override
	{
		if (collision->getTag() == "Enemy1") //Enemy 1's AI
		{
			if (transform->velocity.y == -1 && transform->position.y == originY)
			{
				transform->velocity.y = 0;
				Yveloc = transform->position.y;
			}

			if (transform->position.y >= (SDL_GetWindowSurface(window)->h) - 300 )
			{
				transform->velocity.y = -1;
				
			}
			else {
				if (transform->position.x >= (SDL_GetWindowSurface(window)->w) - 200)
				{
					transform->velocity.x = -.5;
					Yveloc = transform->position.y;
					transform->velocity.y = 1;
				}
				else if (transform->position.x <= 0)
				{
					transform->velocity.x = .5;
					Yveloc = transform->position.y;
					transform->velocity.y = 1;
				}

				if (transform->position.y > Yveloc + 50)
				{

					transform->velocity.y = 0;
				}

			}
			
			

		}
	}
};