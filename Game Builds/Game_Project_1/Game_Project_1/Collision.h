#pragma once
#include "SDL.h"
class collision
{
public:
	static bool CollisionDetected(const SDL_Rect& rectA, const SDL_Rect& rectB)
	{
		return SDL_IntersectRect(&rectA, &rectB, new SDL_Rect);
	}
};