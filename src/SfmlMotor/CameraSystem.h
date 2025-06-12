#pragma once

#include "System.h"
#include "Entity.h"
#include "Transform.h"
#include <SFML/Graphics.hpp>
#include "ECS_Manager.h"

class CameraSystem : public System {
public:
    CameraSystem(sf::View& view, ECS_Manager* ecsManager);
    virtual ~CameraSystem() = default;

    void start() override;
    void update() override;

    void setTarget(Entity* entity) { target = entity; }
    void setBoundaries(float left, float right, float top, float bottom);
    void setOffset(const sf::Vector2f& offset) { this->offset = offset; }
    void setDeadzone(const sf::Vector2f& deadzone) { this->deadzone = deadzone; }
    void setLerpFactor(float factor) { lerpFactor = factor; }

private:
    void updateCamera(const sf::Vector2f& targetPos);
    sf::Vector2f clampPosition(const sf::Vector2f& pos) const;

    sf::View& gameView;
    Entity* target;
    ECS_Manager* ecsManager;
    sf::Vector2f boundaries[2];  // min et max
    sf::Vector2f offset;        // décalage de la caméra par rapport à la cible
    sf::Vector2f deadzone;      // zone morte où la caméra ne bouge pas
    float lerpFactor;          // facteur de lissage du mouvement
};
