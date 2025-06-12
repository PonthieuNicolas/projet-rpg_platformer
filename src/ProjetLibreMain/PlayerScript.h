#pragma once
#include "Script.h"
#include "StateMachineComponent.h"
#include "PlayerStates.h"
#include "Transform.h"
#include "Life.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "CollisionEvent.h"
#include <SFML/Window/Event.hpp>
#include <string>

class PlayerScript : public Script {
private:
    StateMachineComponent* stateMachine;
    Transform* transform;
    AnimationComponent* animationComponent;
    Life* stats;
    bool movingRight;
    float verticalSpeed;
    bool onGround;
    bool jumpRequested;
    bool isDead;
    bool isRunning;
    float attackCooldown;
    float attackRange;
    int attackDamage;
    int experienceGained;

    // Variables pour la physique
    const float gravity = 980.0f; // pixels par seconde au carré
    const float maxFallSpeed = 1000.0f; // vitesse de chute maximale
    const float groundLevel = 400.0f; // position Y du sol
    const float jumpForce = 500.0f;

    void applyGravity(float deltaTime);
    void checkGroundCollision();
    void handlePlatformCollision(Entity* platform);

public:
    PlayerScript();
    void start() override;
    void update() override;
    void handleEvent(const sf::Event& event);
    void attack();
    void takeDamage(int damage);
    void die();
    
    // Méthodes pour le système de niveau
    void gainExperience(int exp);
    int getLevel() const;
    int getExperience() const;
    int getExperienceToNextLevel() const;
    int getMaxHealth() const;
    int getCurrentHealth() const;
    int getAttack() const;
    int getDefense() const;
    void heal(int amount);
    
    // Méthode pour gérer les événements de collision
    void onCollision(const CollisionEvent& event);
};
