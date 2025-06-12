#pragma once
#include "SystemInterface.h"
#include "Entity.h"
#include "ECS_Manager.h"

class System : public ISystem {
protected:
    ECS_Manager* ecsManager;
    std::vector<Entity*> entities;

public:
    System() : ecsManager(nullptr) {}
    virtual ~System() = default;

    void setECSManager(ECS_Manager* manager) override;
    void addEntity(Entity* entity) override;

    virtual void start() override = 0;
    virtual void update() override = 0;
};