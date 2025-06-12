#include "pch.h"
#include "System.h"

void System::setECSManager(ECS_Manager* manager)
{
	ecsManager = manager;
}

void System::addEntity(Entity* entity)
{
	if (entity)
	{
		entities.push_back(entity);
	}
}