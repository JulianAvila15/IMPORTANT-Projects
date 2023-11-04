#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "AssetManager.h"

class SpriteComponent : public Component
{

public:
	SpriteComponent() = default;
	SpriteComponent(string filePath) //get file path of sprite
	{
		SetTexture(filePath);
	}
	~SpriteComponent()
	{
	}

	int getWidth()
	{
		return srcRect.w;
	}

	int getHeight()
	{
		return srcRect.h;
	}

	void SetDimensions(int width, int height)
	{
		destRect.w = width;
		destRect.h = height;
	}

	void SetTexture(string filePath)
	{
		texture = Game::assets->GetTexture(filePath);

	}
	void init() override
	{

		transform = &entity->getcomponent<TransformComponent>(); //set the position of the sprite to a specified position using the position component

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height* transform->scale;


	}

	void update() override
	{
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}



private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
};