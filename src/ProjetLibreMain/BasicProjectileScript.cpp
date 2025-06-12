#include "pch.h"
#include "BasicProjectileScript.h"
#include "Transform.h"
#include "TimerSystem.h"
#include <iostream>

BasicProjectileScript::BasicProjectileScript()
    : Projectile(), mElapsedTime(0.f), mLifeTime(12.f) // ou initialisation dans la déclaration en header
{
}

void BasicProjectileScript::start() {
    Transform* transform = ecsManager->getComponent<Transform>(attachedEntity);
    if (transform) {
        setPosition(transform->getPosition());
        if (getVelocity().x == 0 && getVelocity().y == 0) {
            setVelocity({ 200.f, 0.f });
        }
        damage = 10.f;
    }
    else {
        std::cerr << "BasicProjectileScript::start - Transform component not found for the attached entity." << std::endl;
    }
}

void BasicProjectileScript::update() {
    TimerSystem* timer = ecsManager->getSystem<TimerSystem>();
    float deltaTime = timer ? timer->DeltaTime() : 0.016f;

    // Mise à jour des déplacements et du compteur de vie
    update(deltaTime);

    Transform* transform = ecsManager->getComponent<Transform>(attachedEntity);
    if (transform) {
        transform->setPosition(getPosition());
    }
}

void BasicProjectileScript::update(float deltaTime) {
    if (!isActive())
        return;

    mElapsedTime += deltaTime;

    if (mElapsedTime >= mLifeTime) {
        auto* destroyComp = ecsManager->getComponent<DestroyComponent>(attachedEntity);
        if (!destroyComp) {
            destroyComp = ecsManager->addComponent<DestroyComponent>(attachedEntity);
        }
        destroyComp->markForDestruction();
        setActive(false);
        return;
    }

    move(deltaTime);
}

void BasicProjectileScript::onCollision(Entity* other) {
    if (!other)
        return;
    std::cout << "BasicProjectileScript collided with entity: " << other->getName() << std::endl;
    
    Life* life = ecsManager->getComponent<Life>(other);
    if (life) {
        life->takeDamage(1);
    }
    
    auto* destroyComp = ecsManager->getComponent<DestroyComponent>(attachedEntity);
    if (!destroyComp) {
        destroyComp = ecsManager->addComponent<DestroyComponent>(attachedEntity);
    }
    destroyComp->markForDestruction();

    setActive(false);
}
