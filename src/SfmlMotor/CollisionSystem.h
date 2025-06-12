#pragma once
#include "System.h"
#include "Entity.h"
#include "ColliderComponent.h"
#include "EventSystem.h"
#include "CollisionEvent.h"
#include <vector>

class CollisionSystem : public System {
public:
    CollisionSystem();
    virtual ~CollisionSystem() = default;

    void start() override;
    void update() override;

private:
    EventSystem* m_eventSystem;

    void notifyCollision(Entity* entity1, Entity* entity2);
};
