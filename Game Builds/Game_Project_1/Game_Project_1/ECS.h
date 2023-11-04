#pragma once

//Entity Component System

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;


using namespace std;

//abstract the Component ID and Groups to be equal to size_t
using ComponentID = std::size_t;
using Group = std::size_t;


inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() 
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr size_t maxComponents = 32;
constexpr size_t maxGroups = 32;

//provide abstraction for both the component and group bit sets
using ComponentBitSet = bitset<maxComponents>;
using GroupBitSet = bitset<maxGroups>;

//provide abstraction for an array of component pointers with the size of maximum components
using ComponentArray = array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	Component() {};

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity
{
public:
	Entity(Manager& mManager) : manager(mManager) {}
	
	void Update()
	{
     		for (auto& c : components) if(this->isActive() == true) c->update();
		
	}

	void draw() {
    		for (auto& c : components) c->draw(); 
	}

	bool isActive() const { return active; }
	void destroy() 
	{ 
		active = false; 
		
	}

	template <typename T> bool hasComponent() const
	{
		return componentBitSet [getComponentTypeID <T>()];
	}

	template <typename T, typename...TArgs> 
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));
		
		//Insert Component into the list of components deployed
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	
	template<typename T> T& getcomponent() const
	{
		auto ptr = componentArray[getComponentTypeID<T>()];
		return *static_cast<T*>(ptr);
	}

	bool HasGroup(Group someGroup)
	{
		return groupBitSet[someGroup];
	}

	void AddGroup(Group someGroup);

	void DelGroup(Group someGroup)
	{
		groupBitSet[someGroup] = false; //group no longer exists in the bitset
	}

private:
	Manager& manager;
	bool active = true;
	vector<unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
	
};

class Manager //Manage the components of game objects
{

public:
	void update()
	{
		for (auto& e : entities) if(e->isActive()==true) e ->Update();
	}

	void draw()
	{
		for (auto& e : entities) if(e->isActive()) e->draw();
	}

	void refresh()
	{
		for (auto i = 0u; i < maxGroups; i++)
		{
			auto v = groupsofEntities[i];
			v.erase(remove_if(begin(v), end(v), [i](Entity* someEntity) // if an entity in a certain group is neither active nor belong anywhere, then it is destroyed/erased
				{
					return someEntity->isActive()==false || !someEntity->HasGroup(i); //return if the entity is active or it has a group
				}),
				end(v));
		}
		
		
		entities.erase(remove_if(begin(entities), end(entities), [](const unique_ptr<Entity>& mEntity) 
			{
				return mEntity->isActive()==false;
			}),
			end(entities));
	}

	void AddToGroup(Entity* someEntity, Group someGroup)
	{
		groupsofEntities[someGroup].emplace_back(someEntity);//insert an entity to a specific group
	}

	vector<Entity*>& GetGroup(Group someGroup)
	{
		return groupsofEntities[someGroup];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		unique_ptr<Entity> uPtr{e};
		entities.emplace_back(move(uPtr));
		return *e;
	}

private:
	vector<unique_ptr<Entity>> entities;
	array<vector<Entity*>, maxGroups> groupsofEntities;
};