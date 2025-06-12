#include "pch.h"
#include "StateMachineSystem.h"

StateMachineSystem::StateMachineSystem()
    : timer(nullptr)
{
}

void StateMachineSystem::setTimer(TimerSystem* timer) {
    this->timer = timer;
}

void StateMachineSystem::start() {
}

void StateMachineSystem::update() {
    if (!timer) return;

    float deltaTime = timer->DeltaTime();

    for (auto* entity : ecsManager->getAllEntities()) {
        auto* stateMachineComponent = ecsManager->getComponent<StateMachineComponent>(entity);
        if (stateMachineComponent) {
            stateMachineComponent->update(deltaTime);
        }
    }
}

void StateMachineSystem::handleEvent(const sf::Event& event) {
    for (auto* entity : ecsManager->getAllEntities()) {
        auto* stateMachineComponent = ecsManager->getComponent<StateMachineComponent>(entity);
        if (stateMachineComponent) {
            stateMachineComponent->handleEvent(event);
        }
    }
}
