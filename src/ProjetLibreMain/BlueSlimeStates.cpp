#include "pch.h"
#include "BlueSlimeStates.h"
#include "BlueSlimeScript.h"
#include "PlayerScript.h"
#include <SFML/Window/Keyboard.hpp>

// Implémentation de BlueSlimeIdleState
BlueSlimeIdleState::BlueSlimeIdleState(Entity* entity, ECS_Manager* ecsManager)
    : State(entity, ecsManager), idleTimer(0.0f) {}

void BlueSlimeIdleState::enter() {
    idleTimer = 0.0f;
    if (auto anim = ecsManager->getComponent<AnimationComponent>(entity)) {
        std::vector<sf::IntRect> idleFrames = AnimationData::getSlimeIdleFrames();
        anim->setFrames(idleFrames);
        anim->reset();
    }
}

void BlueSlimeIdleState::exit() {}

void BlueSlimeIdleState::update(float deltaTime) {
    idleTimer += deltaTime;
}

void BlueSlimeIdleState::handleEvent(const sf::Event& event) {}

bool BlueSlimeIdleState::shouldTransitionTo(const std::string& stateName) {
    if (idleTimer >= idleDuration) {
        return stateName == "Move";
    }
    return false;
}

std::string BlueSlimeIdleState::getName() const {
    return "Idle";
}

// Implémentation de BlueSlimeMoveState
BlueSlimeMoveState::BlueSlimeMoveState(Entity* entity, ECS_Manager* ecsManager)
    : State(entity, ecsManager), moveTimer(0.0f), moveSpeed(100.0f), movingRight(true) {}

void BlueSlimeMoveState::enter() {
    moveTimer = 0.0f;
    if (auto anim = ecsManager->getComponent<AnimationComponent>(entity)) {
        std::vector<sf::IntRect> moveFrames = AnimationData::getSlimeIdleFrames();
        anim->setFrames(moveFrames);
        anim->reset();
    }
}

void BlueSlimeMoveState::exit() {}

void BlueSlimeMoveState::update(float deltaTime) {
    moveTimer += deltaTime;
    
    if (auto transform = ecsManager->getComponent<Transform>(entity)) {
        float movement = moveSpeed * deltaTime * (movingRight ? 1.0f : -1.0f);
        transform->position.x += movement;
        
        // Changer de direction si on atteint les limites
        if (transform->position.x <= 100.0f || transform->position.x >= 1100.0f) {
            movingRight = !movingRight;
            if (auto sprite = ecsManager->getComponent<SpriteComponent>(entity)) {
                sprite->setScale(movingRight ? 1.0f : -1.0f, 1.0f);
            }
        }
    }
}

void BlueSlimeMoveState::handleEvent(const sf::Event& event) {}

bool BlueSlimeMoveState::shouldTransitionTo(const std::string& stateName) {
    if (moveTimer >= moveDuration) {
        return stateName == "Idle";
    }
    return false;
}

std::string BlueSlimeMoveState::getName() const {
    return "Move";
}

// Implémentation de BlueSlimeAttackState
BlueSlimeAttackState::BlueSlimeAttackState(Entity* entity, ECS_Manager* ecsManager)
    : State(entity, ecsManager), attackTimer(0.0f) {}

void BlueSlimeAttackState::enter() {
    attackTimer = 0.0f;
    if (auto anim = ecsManager->getComponent<AnimationComponent>(entity)) {
        std::vector<sf::IntRect> attackFrames = AnimationData::getSlimeIdleFrames();
        anim->setFrames(attackFrames);
        anim->reset();
    }
}

void BlueSlimeAttackState::exit() {}

void BlueSlimeAttackState::update(float deltaTime) {
    attackTimer += deltaTime;
    
    // Vérifier si le joueur est à portée d'attaque
    if (auto transform = ecsManager->getComponent<Transform>(entity)) {
        Entity* player = nullptr;
        // Rechercher le joueur dans l'ECS
        const std::vector<Entity*>& entities = ecsManager->getAllEntities();
        for (Entity* entity : entities) {
            if (entity && entity->getName() == "Player") {
                player = entity;
                break;
            }
        }
        
        if (player) {
            auto playerTransform = ecsManager->getComponent<Transform>(player);
            if (playerTransform) {
                float distance = std::abs(transform->position.x - playerTransform->position.x);
                if (distance <= attackRange) {
                    // Infliger des dégâts au joueur
                    auto playerScript = ecsManager->getScript<PlayerScript>(player);
                    if (playerScript) {
                        playerScript->takeDamage(attackDamage);
                    }
                }
            }
        }
    }
}

void BlueSlimeAttackState::handleEvent(const sf::Event& event) {}

bool BlueSlimeAttackState::shouldTransitionTo(const std::string& stateName) {
    if (attackTimer >= attackDuration) {
        return stateName == "Idle";
    }
    return false;
}

std::string BlueSlimeAttackState::getName() const {
    return "Attack";
} 