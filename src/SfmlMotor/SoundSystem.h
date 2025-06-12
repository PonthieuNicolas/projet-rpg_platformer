#pragma once
#include "SystemInterface.h"
#include "ECS_Manager.h"
#include <vector>

class SoundSystem : public ISystem {
private:
    ECS_Manager* ecsManager;
    std::vector<Entity*> soundEntities;

public:
    SoundSystem();

    virtual void setECSManager(ECS_Manager* manager) override;

    virtual void start() override;
    virtual void update() override;
    virtual void addEntity(Entity* entity) override;
};
