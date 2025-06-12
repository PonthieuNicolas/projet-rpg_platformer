#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(std::string name, size_t id, int damage) : Entity(name, id), damage(damage) {}

int Enemy::getDamage() const { return damage; }