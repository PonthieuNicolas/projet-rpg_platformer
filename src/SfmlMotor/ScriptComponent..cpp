#include "pch.h"
#include "Script.h"

Script::Script() : attachedEntity(nullptr), ecsManager(nullptr)
{
}

void Script::setEntity(Entity* entity)
{
	attachedEntity = entity;
}

void Script::setECSManager(ECS_Manager* manager)
{
	ecsManager = manager;
}

Entity* Script::getEntity() const
{
	return attachedEntity;
}