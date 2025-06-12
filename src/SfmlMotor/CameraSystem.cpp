#include "pch.h"
#include "CameraSystem.h"
#include "Transform.h"

CameraSystem::CameraSystem(sf::View& view, ECS_Manager* manager)
    : gameView(view)
    , target(nullptr)
    , ecsManager(manager)
    , offset(0.f, 0.f)
    , deadzone(10.f, 10.f)
    , lerpFactor(0.1f)
{
    // Initialiser les limites à l'infini par défaut
    boundaries[0] = sf::Vector2f(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
    boundaries[1] = sf::Vector2f(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
}

void CameraSystem::start() {
    if (target && ecsManager) {
        Transform* transform = ecsManager->getComponent<Transform>(target);
        if (transform) {
            sf::Vector2f pos = transform->getPosition() + offset;
            gameView.setCenter(pos);
        }
    }
}

void CameraSystem::update() {
    if (target && ecsManager) {
        Transform* transform = ecsManager->getComponent<Transform>(target);
        if (transform) {
            updateCamera(transform->getPosition());
        }
    }
}

void CameraSystem::setBoundaries(float left, float right, float top, float bottom) {
    boundaries[0] = sf::Vector2f(left, top);
    boundaries[1] = sf::Vector2f(right, bottom);
}

void CameraSystem::updateCamera(const sf::Vector2f& targetPos) {
    sf::Vector2f currentCenter = gameView.getCenter();
    sf::Vector2f targetCenter = targetPos + offset;
    
    // Vérifier si la cible est hors de la zone morte
    sf::Vector2f delta = targetCenter - currentCenter;
    
    bool moveX = std::abs(delta.x) > deadzone.x;
    bool moveY = std::abs(delta.y) > deadzone.y;
    
    sf::Vector2f newCenter = currentCenter;
    
    if (moveX) {
        float targetX = targetCenter.x;
        if (delta.x > 0) targetX -= deadzone.x;
        else targetX += deadzone.x;
        newCenter.x = currentCenter.x + (targetX - currentCenter.x) * lerpFactor;
    }
    
    if (moveY) {
        float targetY = targetCenter.y;
        if (delta.y > 0) targetY -= deadzone.y;
        else targetY += deadzone.y;
        newCenter.y = currentCenter.y + (targetY - currentCenter.y) * lerpFactor;
    }
    
    // Appliquer les limites
    newCenter = clampPosition(newCenter);
    
    gameView.setCenter(newCenter);
}

sf::Vector2f CameraSystem::clampPosition(const sf::Vector2f& pos) const {
    return sf::Vector2f(
        std::clamp(pos.x, boundaries[0].x, boundaries[1].x),
        std::clamp(pos.y, boundaries[0].y, boundaries[1].y)
    );
}

