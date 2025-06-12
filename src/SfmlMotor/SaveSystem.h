#pragma once
#include "SystemInterface.h"
#include "ECS_Manager.h"

class SaveSystem : public ISystem {
private:
    ECS_Manager* ecsManager;

public:
    SaveSystem() : ecsManager(nullptr) {}
    virtual ~SaveSystem() = default;

    virtual void setECSManager(ECS_Manager* manager) override {
        ecsManager = manager;
    }

    virtual void start() override {
    }

    virtual void update() override {
    }

    virtual void addEntity(Entity* entity) override {
    }
};

