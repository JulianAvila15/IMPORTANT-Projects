#include "ECS.h"

void Entity::AddGroup(Group someGroup)
{
	groupBitSet[someGroup] = true; //some group exists
	manager.AddToGroup(this, someGroup);
}