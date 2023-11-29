#include "Map.h"
#include "TextureManager.h"

void randomizeMap(int map[20][25])
{
	for (int i = 0; i < 100; i++)
	{
		srand(time(NULL) + rand());
		map[rand()%25][rand()%20] = 1;
	}
}

int lvl1[20][25];


Map::Map() {
	space = TextureManager::LoadTexture("C:/Users/jayli/Documents/Game Builds/Game_Project_1/Game_Project_1/Assets/space.png");
	stars = TextureManager::LoadTexture("C:/Users/jayli/Documents/Game Builds/Game_Project_1/Game_Project_1/Assets/Star.png");
	randomizeMap(lvl1);
	LoadMap(lvl1);

	srcRect.x = srcRect.y = 0;
	srcRect.h = srcRect.w = 100;

	destRect.x = destRect.y = 0;
	destRect.h = destRect.w = 100;

}

Map::~Map()
{
	SDL_DestroyTexture(stars);
	SDL_DestroyTexture(space);
}

void Map::LoadMap(int arr[20][25])
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			map[r][c] = arr[r][c];
		}
	}

}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 20; row++)
	{
		for (int cols = 0; cols < 25; cols++)
		{
			type = map[row][cols];

			destRect.x = cols * 100;
			destRect.y = row * 100;

			switch (type)
			{
			case 1:
				TextureManager::Draw(stars, srcRect, destRect);
				break;
			default:
				break;

			}
		}
	}

}