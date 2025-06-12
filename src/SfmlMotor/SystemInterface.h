#pragma once
#include <vector>

class Entity;
class ECS_Manager;

class ISystem {
public:
    virtual ~ISystem() = default;
    virtual void setECSManager(ECS_Manager* manager) = 0;
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void addEntity(Entity* entity) = 0;
};