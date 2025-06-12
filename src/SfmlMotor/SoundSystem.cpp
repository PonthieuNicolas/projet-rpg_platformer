#include "pch.h"
#include "SoundSystem.h"
#include "SoundComponent.h"

SoundSystem::SoundSystem()
    : ecsManager(nullptr)
{
}

void SoundSystem::setECSManager(ECS_Manager* manager) {
    this->ecsManager = manager;
}

void SoundSystem::start() {
    if (!ecsManager)
        return;

    const auto& allEntities = ecsManager->getAllEntities();
    for (Entity* entity : allEntities) {
        if (ecsManager->getComponent<SoundComponent>(entity)) {
            soundEntities.push_back(entity);
        }
    }
}

void SoundSystem::update() {
    for (Entity* entity : soundEntities) {
        SoundComponent* sndComp = ecsManager->getComponent<SoundComponent>(entity);
        if (sndComp) {
            if (!sndComp->isPlaying()) {
            }
        }
    }
}

void SoundSystem::addEntity(Entity* entity) {
    if (entity && ecsManager->getComponent<SoundComponent>(entity)) {
        soundEntities.push_back(entity);
    }
}