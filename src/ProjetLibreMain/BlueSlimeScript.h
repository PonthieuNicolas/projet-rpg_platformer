#pragma once
#include "Script.h"
#include "StateMachineComponent.h"
#include "Transform.h"
#include "Life.h"
#include "AnimationComponent.h"
#include "TimerSystem.h"
#include <SFML/Window/Event.hpp>
#include "ColliderComponent.h"
#include "CollisionEvent.h"

class BlueSlimeScript : public Script {
private:
    StateMachineComponent* stateMachine;
    Transform* transform;
    AnimationComponent* animationComponent;
    Life* stats;
    bool isDead;
    float detectionRange;
    float attackCooldown;
    float attackRange;
    int attackDamage;
    const float attackCooldownDuration = 2.0f;
    bool movingLeft;
    bool facingLeft;

    // Variables pour la patrouille
    float patrolTimer;
    const float patrolDuration = 3.0f; // Durée avant changement de direction
    float initialX; // Position initiale pour définir les limites de patrouille
    const float patrolRange = 200.0f; // Distance maximale de patrouille depuis la position initiale

public:
    BlueSlimeScript();
    void start() override;
    void update() override;
    void handleEvent(const sf::Event& event);
    void attack();
    void takeDamage(int damage);
    void die();
    
    int getCurrentHealth() const;
    int getMaxHealth() const;
    bool isAlive() const;
}; 