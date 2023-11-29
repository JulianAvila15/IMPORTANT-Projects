#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <stdio.h>

//forward declare objects
class AssetManager;
class CollisionComponent;

using namespace std;
class Game {

public:
	Game();
	~Game();

	bool running();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();

	void update();

	void render();

	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static AssetManager* assets;
	static enum groupLabels : size_t
	{
		groupPlayer,
		groupWalls,
		groupProjectiles

	};
private: 
	
	int cnt=0;
	bool isRunning;
	SDL_Window* window;


};