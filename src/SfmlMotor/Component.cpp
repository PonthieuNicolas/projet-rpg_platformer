#include "pch.h"
#include "Component.h"

Component::Component() :entityId(-1)
{
}

void Component::SetEntityId(int id)
{
	entityId = id;
}

int Component::GetEntityId() const
{
	return entityId;
}