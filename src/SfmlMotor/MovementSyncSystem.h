#pragma once
#include "SystemInterface.h"
#include "ECS_Manager.h"
#include "Entity.h"
#include "RigidBody.h"
#include "SpriteComponent.h"

class MovementSyncSystem : public ISystem {
private:
    ECS_Manager* ecsManager;
public:
    MovementSyncSystem() : ecsManager(nullptr) {}

    void setECSManager(ECS_Manager* manager) override {
        ecsManager = manager;
    }

    void start() override {
    }

    void update() override {
        const auto& entities = ecsManager->getAllEntities();
        for (Entity* entity : entities) {
            RigidBody* rigidBody = ecsManager->getComponent<RigidBody>(entity);
            SpriteComponent* sprite = ecsManager->getComponent<SpriteComponent>(entity);
            if (rigidBody && sprite) {
                Vector2 pos = rigidBody->getPosition();
                sprite->setPosition(pos.x, pos.y);
            }
        }
    }

    void addEntity(Entity* entity) override {
    }
};
