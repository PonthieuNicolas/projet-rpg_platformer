#pragma once
#include "Event.h"
#include "Entity.h"
#include <iostream>

class CollisionEvent : public Event {
public:
    CollisionEvent(Entity* a, Entity* b) : entityA(a), entityB(b) {

        if (!entityA || !entityB) {
            std::cout << "Warning: Null entity in CollisionEvent constructor!" << std::endl;
        }
        else {
            std::cout << "CollisionEvent created between: "
                << entityA->getName() << " (ID: " << entityA->getId() << ") and "
                << entityB->getName() << " (ID: " << entityB->getId() << ")" << std::endl;
        }
    }

    Entity* entityA;
    Entity* entityB;
};