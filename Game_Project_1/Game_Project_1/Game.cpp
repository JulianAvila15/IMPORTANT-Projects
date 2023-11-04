#include "Game.h"
#include "TextureManager.h"
#include "Collision.h"
#include "Components.h"
#include "Map.h"
#include "AssetManager.h"
#include <iostream>
#include<queue>
using namespace std;

Map* GameMap;

//declare renderer
SDL_Renderer* Game::renderer = nullptr;

//create objects
Manager manager;
Entity& newPlayer = manager.addEntity();
Entity& rightWall = manager.addEntity();
Entity& leftWall = manager.addEntity();
Entity& Enemy1 = manager.addEntity();
Entity& PlayerProjectile = manager.addEntity();

vector<Entity> EnemyType1;
vector<Entity> playerBullets;

SDL_Event Game::event;
TransformComponent& positionTracker(newPlayer.addComponent<TransformComponent>());

AssetManager* Game::assets = new AssetManager(&manager);

int numofBullets=0;

Game::Game() {}

Game::~Game() {}

bool Game::running() { return isRunning; }

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	//Initialize Windows and Renderers
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		isRunning = true;
		cout << "Subsystems Initialized!..." << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		//Window was successfully created
		if (window)
		{
			cout << "Window created!" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		//renderer was successfully created
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			cout << "Renderer created!" << endl;
		}

	}

	//add sprites of objects to asset manager
	assets->AddTexture("player", "C:/Users/jayli/Documents/Game Builds/Game_Project_1/Game_Project_1/Assets/Player.png");
	assets->AddTexture("enemy 1", "C:/Users/jayli/Documents/Game Builds/Game_Project_1/Game_Project_1/Assets/Enemy 1.png");
	assets->AddTexture("projectile_test", "C:/Users/jayli/Documents/Game Builds/Game_Project_1/Game_Project_1/Assets/Player Bullet.png");

	//declare game objects

	//player
	newPlayer.addComponent<TransformComponent>( (SDL_GetWindowSurface(window)->w)/2.20f, SDL_GetWindowSurface(window)->h-200);
	newPlayer.addComponent<SpriteComponent>("player");
	newPlayer.addComponent<KeyboardContorller>();
	newPlayer.addComponent<CollisionComponent>("Player");
	newPlayer.AddGroup(groupPlayer);


//walls
rightWall.addComponent<TransformComponent>(SDL_GetWindowSurface(window)->w - 200, newPlayer.getcomponent<TransformComponent>().position.y);
rightWall.addComponent<CollisionComponent>("wall");
rightWall.AddGroup(groupWalls);

leftWall.addComponent<TransformComponent>(10, newPlayer.getcomponent<TransformComponent>().position.y);

leftWall.addComponent<CollisionComponent>("wall");
leftWall.AddGroup(groupWalls);





for (size_t i = 0; i < 5; i++)
{
	EnemyType1.emplace_back(move(manager.addEntity()));

	srand(time(NULL) + rand());
	EnemyType1.at(i).addComponent<TransformComponent>((SDL_GetWindowSurface(window)->w - (250 * (i + 1))), SDL_GetWindowSurface(window)->h - 500);


	EnemyType1.at(i).addComponent<SpriteComponent>("enemy 1");
	EnemyType1.at(i).addComponent<CollisionComponent>("Enemy1");
	EnemyType1.at(i).addComponent<AIMovementComponent>(window);
}



GameMap = new Map();
}


auto& players(manager.GetGroup(Game::groupPlayer));
auto& walls(manager.GetGroup(Game::groupWalls));

void Game::handleEvents()
{

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;

	}
}

void Game::update()
{

	//here we keep all of the game object types being used
	manager.update();

	manager.refresh();

	if (Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_SPACE)
	{
		playerBullets.emplace_back(move(PlayerProjectile));
		playerBullets.at(playerBullets.size()-1).addComponent <CollisionComponent>("Projectile");
		playerBullets.at(playerBullets.size() - 1).addComponent<TransformComponent>(newPlayer.getcomponent<TransformComponent>().position.x + 26, newPlayer.getcomponent<TransformComponent>().position.y - 50, 100, 100, 1);
		playerBullets.at(playerBullets.size() - 1).addComponent<SpriteComponent>("projectile_test");
		playerBullets.at(playerBullets.size() - 1).addComponent<ProjectileComponent>(200, 2, Vector2D(0, -2));
	}
		//assets->CreateProjectiles(Vector2D(newPlayer.getcomponent<TransformComponent>().position.x + 26, newPlayer.getcomponent<TransformComponent>().position.y - 50), Vector2D(0, -2), 200, 2, "projectile_test");



	if (collision::CollisionDetected(newPlayer.getcomponent<CollisionComponent>().collider, rightWall.getcomponent<CollisionComponent>().collider))
	{
		newPlayer.getcomponent<TransformComponent>().velocity.x = 0;
		if (Game::event.type == SDL_KEYDOWN)
		{
			if (Game::event.key.keysym.sym == SDLK_LEFT) //if player is pressing right arrow key
			{
				newPlayer.getcomponent<TransformComponent>().velocity.x = -2;
			}
		}
	}

	if (collision::CollisionDetected(newPlayer.getcomponent<CollisionComponent>().collider, leftWall.getcomponent<CollisionComponent>().collider))
	{
		newPlayer.getcomponent<TransformComponent>().velocity.x = 0;
		if (Game::event.type == SDL_KEYDOWN)
		{
			if (Game::event.key.keysym.sym == SDLK_RIGHT) //if player is pressing right arrow key
			{
				newPlayer.getcomponent<TransformComponent>().velocity.x = 2;
			}
		}
	}

	for (size_t i = 0; i < EnemyType1.size(); i++)
	EnemyType1.at(i).Update();

	for (size_t i = 0; i < playerBullets.size(); i++)
		playerBullets.at(i).Update();

	if (playerBullets.size() > 10)
	{
		for (size_t i = 0; i < playerBullets.size(); i++)
		{
			if (playerBullets.at(i).isActive())
			{
				playerBullets.at(i).destroy();
			}
		}
		manager.refresh();
		vector<Entity>().swap(playerBullets);
		playerBullets.clear();
		
	}

	

	//for (auto& p : projectiles)
	//{
	//	if (collision::CollisionDetected(newPlayer.getcomponent<CollisionComponent>().collider,p->getcomponent<CollisionComponent>().collider))
	//	{
	//		cout << "Collision detected";
	//	}
	//}

	//GameMap->LoadMap(new int [20][25]);

	
}


void Game::render()
{
		manager.refresh();
		SDL_RenderClear(renderer);
		GameMap->DrawMap();
		//adds stuff to render
		for (auto pl : players)
		{
			pl->draw();
		}
		
		for (size_t i = 0; i < EnemyType1.size(); i++)
		{
			EnemyType1.at(i).draw();
		}

		for (size_t i = 0; i < playerBullets.size(); i++)
			playerBullets.at(i).draw();

		SDL_RenderPresent(renderer);
}

void Game::clean()
{
	
		SDL_RenderClear(renderer);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		cout << "Game Cleaned" << endl;
	
}
