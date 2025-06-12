#pragma once
#include "State.h"
#include "Transform.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "Life.h"
#include "TimerSystem.h"

// État d'attente du slime
class BlueSlimeIdleState : public State {
private:
    float idleTimer;
    const float idleDuration = 2.0f;

public:
    BlueSlimeIdleState(Entity* entity, ECS_Manager* ecsManager);
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void handleEvent(const sf::Event& event) override;
    bool shouldTransitionTo(const std::string& stateName) override;
    std::string getName() const override;
};

// État de déplacement du slime
class BlueSlimeMoveState : public State {
private:
    float moveTimer;
    const float moveDuration = 3.0f;
    float moveSpeed;
    bool movingRight;

public:
    BlueSlimeMoveState(Entity* entity, ECS_Manager* ecsManager);
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void handleEvent(const sf::Event& event) override;
    bool shouldTransitionTo(const std::string& stateName) override;
    std::string getName() const override;
};

// État d'attaque du slime
class BlueSlimeAttackState : public State {
private:
    float attackTimer;
    const float attackDuration = 1.0f;
    const float attackRange = 100.0f;
    const int attackDamage = 10;

public:
    BlueSlimeAttackState(Entity* entity, ECS_Manager* ecsManager);
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void handleEvent(const sf::Event& event) override;
    bool shouldTransitionTo(const std::string& stateName) override;
    std::string getName() const override;
}; 