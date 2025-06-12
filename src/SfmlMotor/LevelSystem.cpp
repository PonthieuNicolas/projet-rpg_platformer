#include "pch.h"
#include "LevelSystem.h"

LevelSystem::LevelSystem(ECS_Manager* manager) : ecsManager(manager) {
}

void LevelSystem::start() {
    std::vector<PlatformData> defaultLevel = {
        {100.f, 600.f, 200.f, 30.f, "platform", ""},
        {400.f, 500.f, 200.f, 30.f, "platform", ""},
        {700.f, 400.f, 200.f, 30.f, "platform", ""}
    };
    loadLevel(defaultLevel);
}

void LevelSystem::update() {
}

void LevelSystem::loadLevel(const std::vector<PlatformData>& platforms) {
    clearLevel();
    for (const auto& platform : platforms) {
        createPlatform(platform);
    }
}

void LevelSystem::clearLevel() {
    for (auto entity : levelEntities) {
        if (entity) {
            ecsManager->removeComponent<Transform>(entity);
            ecsManager->removeComponent<ColliderComponent>(entity);
            ecsManager->removeComponent<SpriteComponent>(entity);
        }
    }
    levelEntities.clear();
}

void LevelSystem::createPlatform(const PlatformData& data) {
    Entity* platform = ecsManager->createEntity("Platform");
    
    auto transform = ecsManager->addComponent<Transform>(platform);
    transform->setPosition(data.x, data.y);
    
    auto collider = ecsManager->addComponent<ColliderComponent>(platform);
    collider->setPosition(data.x, data.y);
    collider->setSize(data.width, data.height);
    collider->setBoundingBox(sf::FloatRect({data.x, data.y}, {data.width, data.height}));
    
    if (!data.texturePath.empty()) {
        auto sprite = ecsManager->addComponent<SpriteComponent>(platform);
    }
    
    levelEntities.push_back(platform);
}
