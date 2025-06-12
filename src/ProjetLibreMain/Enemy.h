#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
    int damage;

public:
    Enemy(std::string name, size_t id, int damage);
    int getDamage() const;
};

