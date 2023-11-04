#pragma once
#include "Components.h"
#include "2DVector.h"
class TransformComponent : public Component
{

public:

	Vector2D position; //has x or y values
	Vector2D velocity;
	int speed = 3;
	int height =150, width = 150;
	int scale = 1;

	TransformComponent()
	{

		position.zero(); //zero things out
	}

	TransformComponent(int scaleDegree)
	{
		position.zero();
		this->scale = scaleDegree;
	}

	TransformComponent(float tempX, float tempY)//get x and y coordinates
	{
		position.x = tempX;
		position.y = tempY;
	}

	TransformComponent(float tempX, float tempY,int w, int h, int sc) //get width and dimensions of the entity
	{
		position.x = tempX;
		position.y = tempY;
		height = h;
		width = w;
		scale = sc;
	}


	void init() override
	{
		velocity.zero();
	}
	void update() override
	{
			position.x += velocity.x * speed;
			position.y += velocity.y * speed;
	}

};