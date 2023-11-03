#pragma once
#include<map>
#include <string>
#include "TextureManager.h"
#include "2DVector.h"
#include "ECS.h"
using namespace std;

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	//Gameobjects

	void CreateProjectiles(Vector2D pos, Vector2D vel, int range, int sp, string id);
	
		//Texture Management
		void AddTexture(string id,const char* path);
		SDL_Texture* GetTexture(string id);
private:
	Manager* localMan;
	std::map<string, SDL_Texture*> textures;

};