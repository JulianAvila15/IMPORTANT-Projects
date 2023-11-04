 #pragma once
#include "Game.h"

class Map
{
public:

	Map();
	~Map();//avoid memory leaks

	void LoadMap(int arr[20][25]);
	void DrawMap();

private:

	SDL_Rect srcRect, destRect;
	SDL_Texture* space;
	SDL_Texture* stars;
	
	int rows = 20, cols=25;
	int map[20][25];


};