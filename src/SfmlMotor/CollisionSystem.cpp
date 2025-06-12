#include "pch.h"
#include "CollisionSystem.h"

CollisionSystem::CollisionSystem() : m_eventSystem(nullptr) {}

void CollisionSystem::start() {
    m_eventSystem = ecsManager->getEventSystem();
}

void CollisionSystem::update() {
    for (size_t i = 0; i < entities.size(); ++i) {
        auto colliderA = ecsManager->getComponent<ColliderComponent>(entities[i]);
        if (!colliderA)
            continue;

        for (size_t j = i + 1; j < entities.size(); ++j) {
            auto colliderB = ecsManager->getComponent<ColliderComponent>(entities[j]);
            if (!colliderB)
                continue;

            if (colliderA->isCollidingWith(*colliderB)) {
                std::cout << "Collision detected between: " << entities[i]->getName() 
                         << " and " << entities[j]->getName() << std::endl;
                notifyCollision(entities[i], entities[j]);
            }
        }
    }
}

void CollisionSystem::notifyCollision(Entity* entity1, Entity* entity2) {
    if (entity1->getName() == "Player" || entity2->getName() == "Player") {
        if (entity2->getName() == "Player") {
            std::swap(entity1, entity2);
        }
        std::cout << "Emitting collision event for Player and " << entity2->getName() << std::endl;
        CollisionEvent* event = new CollisionEvent(entity1, entity2);
        m_eventSystem->emit("Collision", event);
        delete event;
    }
}
