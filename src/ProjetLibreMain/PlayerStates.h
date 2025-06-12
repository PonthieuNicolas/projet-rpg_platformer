#pragma once
#include "State.h"
#include "Transform.h"
#include "AnimationComponent.h"
#include "AnimationData.h"
#include "SpriteComponent.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <string>

// État d'inactivité (Idle)
class PlayerIdleState : public State {
private:
    AnimationComponent* animationComponent;
    SpriteComponent* spriteComponent;
    float idleTimer;

public:
    PlayerIdleState(Entity* entity, ECS_Manager* ecsManager) 
        : State(entity, ecsManager), animationComponent(nullptr), spriteComponent(nullptr), idleTimer(0.0f) {}
    
    void enter() override {
        std::cout << ">>> Entrant dans l'etat IDLE" << std::endl;
        animationComponent = ecsManager->getComponent<AnimationComponent>(entity);
        spriteComponent = ecsManager->getComponent<SpriteComponent>(entity);
        
        if (animationComponent) {
            std::vector<sf::IntRect> idleFrames = AnimationData::getBlackWizardIdleFrames();
            animationComponent->setFrames(idleFrames);
            animationComponent->reset();
        }
        
        idleTimer = 0.0f;
    }
    
    void exit() override {
        std::cout << "<<< Sortant de l'etat IDLE" << std::endl;
    }
    
    void update(float deltaTime) override {
        idleTimer += deltaTime;

        spriteComponent->update(deltaTime);
        
        // Afficher les touches pressées uniquement à intervalles réguliers
        if (static_cast<int>(idleTimer * 10) % 30 == 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
                std::cout << "Touche Q/D detectee dans IDLE" << std::endl;
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                std::cout << "Touche Espace (saut) detectee dans IDLE" << std::endl;
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
                std::cout << "Touche E (attaque) detectee dans IDLE" << std::endl;
            }
        }
    }
    
    void handleEvent(const sf::Event& event) override {
        // Ne rien faire avec les événements pour le moment
    }
    
    bool shouldTransitionTo(const std::string& stateName) override {
        if (stateName == "Walk") {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || 
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        }
        else if (stateName == "Jump") {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        }
        else if (stateName == "Attack") {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
        }
        return false;
    }
    
    std::string getName() const override {
        return "Idle";
    }
};

// État de marche (Walk)
class PlayerWalkState : public State {
private:
    AnimationComponent* animationComponent;
    SpriteComponent* spriteComponent;
    Transform* transform;
    float moveSpeed;
    bool movingRight;
    float stateTimer;

public:
    PlayerWalkState(Entity* entity, ECS_Manager* ecsManager) 
        : State(entity, ecsManager), animationComponent(nullptr), spriteComponent(nullptr),
          transform(nullptr), moveSpeed(300.0f), movingRight(true), stateTimer(0.0f) {}
    
    void enter() override {
        std::cout << ">>> Entrant dans l'etat WALK" << std::endl;
        animationComponent = ecsManager->getComponent<AnimationComponent>(entity);
        spriteComponent = ecsManager->getComponent<SpriteComponent>(entity);
        transform = ecsManager->getComponent<Transform>(entity);
        stateTimer = 0.0f;
        
        if (animationComponent) {
            std::vector<sf::IntRect> walkFrames = AnimationData::getBlackWizardWalkFrames();
            animationComponent->setFrames(walkFrames);
            animationComponent->reset();
        }
        
        // Déterminer la direction initiale
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            movingRight = true;
            if (spriteComponent) {
                spriteComponent->setScale(1.0f, 1.0f); // Face à droite
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            movingRight = false;
            if (spriteComponent) {
                spriteComponent->setScale(-1.0f, 1.0f); // Face à gauche
            }
        }
    }
    
    void exit() override {
        std::cout << "<<< Sortant de l'etat WALK" << std::endl;
    }
    
    void update(float deltaTime) override {
        if (!transform) return;

        spriteComponent->update(deltaTime);

        stateTimer += deltaTime;
        bool moving = false;
        
        // Debug à intervalle régulier
        //if (static_cast<int>(stateTimer * 10) % 30 == 0) {
        //    std::cout << "Position actuelle: (" << transform->getPosition().x << ", " << transform->getPosition().y << ")" << std::endl;
        //}
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            transform->setPosition(transform->getPosition().x + moveSpeed * deltaTime, transform->getPosition().y);
            movingRight = true;
            moving = true;
            if (spriteComponent) {
                spriteComponent->setScale(1.0f, 1.0f); // Face à droite
            }
            if (static_cast<int>(stateTimer * 10) % 30 == 0) {
                std::cout << "Deplacement vers la droite" << std::endl;
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            transform->setPosition(transform->getPosition().x - moveSpeed * deltaTime, transform->getPosition().y);
            movingRight = false;
            moving = true;
            if (spriteComponent) {
                spriteComponent->setScale(-1.0f, 1.0f); // Face à gauche
            }
            if (static_cast<int>(stateTimer * 10) % 30 == 0) {
                std::cout << "Deplacement vers la gauche" << std::endl;
            }
        }
    }
    
    void handleEvent(const sf::Event& event) override {
        // Ne rien faire avec les événements pour le moment
    }
    
    bool shouldTransitionTo(const std::string& stateName) override {
        if (stateName == "Idle") {
            return !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && 
                   !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        }
        else if (stateName == "Jump") {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        }
        else if (stateName == "Attack") {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
        }
        return false;
    }
    
    std::string getName() const override {
        return "Walk";
    }
};

// État de saut (Jump)
class PlayerJumpState : public State {
private:
    AnimationComponent* animationComponent;
    SpriteComponent* spriteComponent;
    Transform* transform;
    float jumpForce;
    float gravity;
    float verticalVelocity;
    bool isJumping;
    bool movingRight;
    float stateTimer;
    float initialY;

public:
    PlayerJumpState(Entity* entity, ECS_Manager* ecsManager) 
        : State(entity, ecsManager), animationComponent(nullptr), spriteComponent(nullptr), transform(nullptr), 
          jumpForce(600.0f), gravity(1200.0f), verticalVelocity(0.0f), isJumping(false), movingRight(true), stateTimer(0.0f), initialY(300.0f) {}
    
    void enter() override {
        std::cout << ">>> Entrant dans l'etat JUMP" << std::endl;
        animationComponent = ecsManager->getComponent<AnimationComponent>(entity);
        spriteComponent = ecsManager->getComponent<SpriteComponent>(entity);
        transform = ecsManager->getComponent<Transform>(entity);
        stateTimer = 0.0f;
        
        if (transform) {
            initialY = transform->getPosition().y;
        }
        
        if (animationComponent) {
            std::vector<sf::IntRect> jumpFrames = AnimationData::getBlackWizardJumpFrames();
            animationComponent->setFrames(jumpFrames);
            animationComponent->reset();
        }
        
        verticalVelocity = jumpForce;
        isJumping = true;
        
        // Conserver la direction horizontale
        movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
        
        // Appliquer la direction du sprite
        if (spriteComponent) {
            spriteComponent->setScale(movingRight ? 1.0f : -1.0f, 1.0f);
        }
    }
    
    void exit() override {
        std::cout << "<<< Sortant de l'etat JUMP" << std::endl;
    }
    
    void update(float deltaTime) override {
        if (!transform) return;

        spriteComponent->update(deltaTime);        

        stateTimer += deltaTime;
        
        // Appliquer la gravité
        verticalVelocity -= gravity * deltaTime;
        
        // Mettre à jour la position verticale
        transform->setPosition(transform->getPosition().x, transform->getPosition().y - verticalVelocity * deltaTime);
        
        // Debug à intervalle régulier
        //if (static_cast<int>(stateTimer * 10) % 30 == 0) {
        //    std::cout << "Position en saut: (" << transform->getPosition().x << ", " << transform->getPosition().y 
        //              << "), Velocite: " << verticalVelocity << std::endl;
        //}
        
        // Vérifier si le joueur est au sol
        if (transform->getPosition().y >= initialY) {
            transform->setPosition(transform->getPosition().x, initialY);
            isJumping = false;
            //std::cout << "Atterrissage au sol à la position Y: " << initialY << std::endl;
        }

        // Permettre le mouvement horizontal pendant le saut
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            transform->setPosition(transform->getPosition().x + 300.0f * deltaTime, transform->getPosition().y);
            movingRight = true;
            if (spriteComponent) {
                spriteComponent->setScale(1.0f, 1.0f); // Face à droite
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            transform->setPosition(transform->getPosition().x - 300.0f * deltaTime, transform->getPosition().y);
            movingRight = false;
            if (spriteComponent) {
                spriteComponent->setScale(-1.0f, 1.0f); // Face à gauche
            }
        }
    }
    
    void handleEvent(const sf::Event& event) override {
        // Ne rien faire avec les événements pour le moment
    }
    
    bool shouldTransitionTo(const std::string& stateName) override {
        if (!isJumping) {
            if (stateName == "Idle") {
                return !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && 
                       !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
            }
            else if (stateName == "Walk") {
                return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || 
                       sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
            }
        }
        
        //if (stateName == "Attack") {
        //    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
        //}
        
        return false;
    }
    
    std::string getName() const override {
        return "Jump";
    }
};

// État d'attaque (Attack)
class PlayerAttackState : public State {
private:
    AnimationComponent* animationComponent;
    SpriteComponent* spriteComponent;
    float attackTimer;
    float attackDuration;
    bool isAttacking;
    bool movingRight;

public:
    PlayerAttackState(Entity* entity, ECS_Manager* ecsManager) 
        : State(entity, ecsManager), animationComponent(nullptr), spriteComponent(nullptr),
          attackTimer(0.0f), attackDuration(0.5f), isAttacking(false), movingRight(true) {}
    
    void enter() override {
        std::cout << ">>> Entrant dans l'etat ATTACK" << std::endl;
        animationComponent = ecsManager->getComponent<AnimationComponent>(entity);
        spriteComponent = ecsManager->getComponent<SpriteComponent>(entity);
        
        // Conserver la direction du sprite
        if (spriteComponent) {
            // Vérifier la direction actuelle du sprite
            sf::Vector2f scale = spriteComponent->getSprite().getScale();
            movingRight = (scale.x > 0);
        }
        
        if (animationComponent) {
            std::vector<sf::IntRect> attackFrames = AnimationData::getBlackWizardAttack1Frames();
            animationComponent->setFrames(attackFrames);
            animationComponent->reset();
        }
        
        attackTimer = 0.0f;
        isAttacking = true;
    }
    
    void exit() override {
        std::cout << "<<< Sortant de l'etat ATTACK" << std::endl;
    }
    
    void update(float deltaTime) override {
        attackTimer += deltaTime;

        spriteComponent->update(deltaTime);
        
        if (attackTimer >= attackDuration) {
            isAttacking = false;
            //std::cout << "Fin de l'attaque apres " << attackTimer << " secondes" << std::endl;
        }
    }
    
    void handleEvent(const sf::Event& event) override {}
    
    bool shouldTransitionTo(const std::string& stateName) override {
        if (stateName == "Idle" && !isAttacking) {
            return !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && 
                   !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && 
                   !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        }
        else if (stateName == "Walk" && !isAttacking) {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || 
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        }
        else if (stateName == "Jump" && !isAttacking) {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        }
        
        return false;
    }
    
    std::string getName() const override {
        return "Attack";
    }
};