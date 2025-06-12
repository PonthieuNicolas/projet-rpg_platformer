#include "pch.h"
#include "Entity.h"

Entity::Entity(std::string name, size_t id) : name(name), id(id) {}
std::string Entity::getName() const { return name; }
size_t Entity::getId() const { return id; }