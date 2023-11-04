#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardContorller : public Component
{
public:
	TransformComponent* position;
	bool shoot_bullet;
	void init() override
	{
		position = &entity->getcomponent<TransformComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			if (Game::event.key.keysym.sym == SDLK_RIGHT) //if player is pressing right arrow key
			{
				position->velocity.x = 2;
			}

			else if (Game::event.key.keysym.sym == SDLK_LEFT)
			{
				position->velocity.x = -2;
			}
			else if (Game::event.key.keysym.sym == SDLK_SPACE)
			{
				shoot_bullet = true;
			}
			
			
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				position->velocity.x = 0;
				break;
			case SDLK_LEFT:
				position->velocity.x = 0;
				break;
			case SDLK_SPACE:
				shoot_bullet = false;
				break;
			default:
				break;
			}
		}

	}

};