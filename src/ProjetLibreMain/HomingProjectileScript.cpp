// HomingProjectileScript.cpp
#include "pch.h"
#include "HomingProjectileScript.h"
#include "Transform.h"
#include "TimerSystem.h"
#include "DestroyComponent.h"
#include <cmath>
#include <iostream>

namespace {
    inline float vectorLength(const sf::Vector2f& v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }
    inline sf::Vector2f normalize(const sf::Vector2f& v) {
        float len = vectorLength(v);
        return (len != 0.f) ? sf::Vector2f(v.x / len, v.y / len) : sf::Vector2f(0.f, 0.f);
    }
    inline sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t) {
        return a + (b - a) * t;
    }
}

HomingProjectileScript::HomingProjectileScript()
    : BasicProjectileScript()
    , targetEntity(nullptr)
    , homingStrength(5.0f)
{
}

void HomingProjectileScript::setTarget(Entity* target) {
    targetEntity = target;
}

void HomingProjectileScript::start() {
    BasicProjectileScript::start();
}

void HomingProjectileScript::update() {
    TimerSystem* timer = ecsManager->getSystem<TimerSystem>();
    float deltaTime = timer ? timer->DeltaTime() : 0.016f;
    update(deltaTime);

    Transform* transform = ecsManager->getComponent<Transform>(attachedEntity);
    if (transform) {
        transform->setPosition(getPosition());
    }
}

void HomingProjectileScript::update(float deltaTime) {
    if (!isActive())
        return;

    mElapsedTime += deltaTime;

    float speed = 300.f;

    if (targetEntity) {
        Transform* targetTransform = ecsManager->getComponent<Transform>(targetEntity);
        if (targetTransform) {
            sf::Vector2f targetPos = targetTransform->getPosition();
            sf::Vector2f currentPos = getPosition();
            sf::Vector2f direction = normalize(targetPos - currentPos);
            sf::Vector2f newVelocity = direction * speed;
            newVelocity = lerp(getVelocity(), newVelocity, homingStrength * deltaTime);
            setVelocity(newVelocity);
        }
    }

    move(deltaTime);

    if (mElapsedTime >= mLifeTime) {
        auto* destroyComp = ecsManager->getComponent<DestroyComponent>(attachedEntity);
        if (!destroyComp) {
            destroyComp = ecsManager->addComponent<DestroyComponent>(attachedEntity);
        }
        destroyComp->markForDestruction();
        setActive(false);
        return;
    }
}
