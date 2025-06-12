#pragma once

#include "SystemInterface.h"
#include "ECS_Manager.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "TimerSystem.h"
#include <SFML/Graphics.hpp>
#include <vector>

class AnimationSystem : public ISystem {
private:
    ECS_Manager* ecsManager;
    TimerSystem* timerSystem;
    int frameCounter;

public:
    AnimationSystem();
    virtual ~AnimationSystem();

    virtual void setECSManager(ECS_Manager* manager) override;
    virtual void start() override;
    virtual void addEntity(Entity* entity) override;
    virtual void update() override;
};
