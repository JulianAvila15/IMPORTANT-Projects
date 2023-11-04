#include "AssetManager.h"
#include "Components.h"
AssetManager::AssetManager(Manager* man) : localMan(man)
{}

AssetManager::~AssetManager()
{

}

void AssetManager::CreateProjectiles(Vector2D pos, Vector2D vel, int range, int sp, string id)
{
	auto& projectile(localMan->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 100, 100, 1);
	projectile.addComponent<SpriteComponent>(id);
	projectile.addComponent<ProjectileComponent>(range,sp,vel);
	projectile.addComponent <CollisionComponent> ("Projectile");
	projectile.AddGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(string id)
{
	return textures[id];
}