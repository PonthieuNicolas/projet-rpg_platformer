#include "pch.h"
#include "AnimationSystem.h"
#include <iostream>

AnimationSystem::AnimationSystem()
    : ecsManager(nullptr), timerSystem(nullptr), frameCounter(0)
{
}

AnimationSystem::~AnimationSystem() = default;

void AnimationSystem::setECSManager(ECS_Manager* manager) {
    ecsManager = manager;
    timerSystem = ecsManager->getSystem<TimerSystem>();
    std::cout << "AnimationSystem: ECS Manager set, TimerSystem "
        << (timerSystem ? "found" : "not found") << std::endl;
}

void AnimationSystem::start() {
    if (!timerSystem) {
        timerSystem = ecsManager->getSystem<TimerSystem>();
        std::cout << "AnimationSystem: Start - TimerSystem "
            << (timerSystem ? "found" : "not found") << std::endl;
    }
}

void AnimationSystem::addEntity(Entity* entity) {
}

void AnimationSystem::update() {
    frameCounter++;

    if (!timerSystem) {
        std::cout << "AnimationSystem: TimerSystem non disponible" << std::endl;
        return;
    }

    float deltaTime = timerSystem->DeltaTime();

    const std::vector<Entity*>& entities = ecsManager->getAllEntities();
    for (Entity* entity : entities) {
        SpriteComponent* spriteComp = ecsManager->getComponent<SpriteComponent>(entity);
        AnimationComponent* animComp = ecsManager->getComponent<AnimationComponent>(entity);

        if (spriteComp && animComp) {
            sf::IntRect currentFrame = animComp->getCurrentFrame();
            animComp->update(deltaTime);
            spriteComp->getSprite().setTextureRect(animComp->getCurrentFrame());
        }
    }
}

