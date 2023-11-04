#pragma once
#include "ECS.h"
#include "SDL.h"
#include "Components.h"
#include <string>
using namespace std;
class CollisionComponent : public Component
{
	


	TransformComponent* transform;

	string tag; // helps assign tags to entities and distinguish entities apart from each other. EX: The player object would be assigned the 'player' tag

public:

	SDL_Rect collider;

	CollisionComponent()
	{
		tag = "None";
	}

	CollisionComponent(string tagName)
	{
		tag = tagName;
	}
	

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())//if entity does not have the transform component
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getcomponent<TransformComponent>();
	}

	void update() override
	{
		collider.x = transform->position.x;
		collider.y = transform->position.y;
		collider.h = transform->height * transform->scale;
		collider.w = transform->width * transform->scale;
	}

	void setTag(string tag)
	{
		this->tag = tag;
	}

	string getTag()
	{
		return tag;
	}
};