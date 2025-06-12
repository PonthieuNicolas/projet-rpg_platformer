#include "pch.h"
#include "BlueSlimeScript.h"
#include "BlueSlimeStates.h"
#include "PlayerScript.h"
#include <SFML/Window/Keyboard.hpp>

BlueSlimeScript::BlueSlimeScript()
    : transform(nullptr), stateMachine(nullptr), isDead(false), 
    attackCooldown(0.0f), attackRange(50.0f), attackDamage(10),
    attackCooldownDuration(2.0f), movingLeft(false), facingLeft(false),
    patrolTimer(0.0f), initialX(0.0f), detectionRange(200.0f) {
}

void BlueSlimeScript::start() {
    // Récupérer les composants nécessaires
    transform = ecsManager->getComponent<Transform>(attachedEntity);
    animationComponent = ecsManager->getComponent<AnimationComponent>(attachedEntity);
    stats = ecsManager->getComponent<Life>(attachedEntity);

    // Enregistrer la position initiale pour la patrouille
    if (transform) {
        initialX = transform->position.x;
    }

    // Créer et configurer la machine à états
    stateMachine = ecsManager->addComponent<StateMachineComponent>(attachedEntity);
    stateMachine->initialize(attachedEntity, ecsManager, "Idle");

    // Ajouter tous les états possibles
    stateMachine->addState<BlueSlimeIdleState>("Idle");
    stateMachine->addState<BlueSlimeMoveState>("Move");
    stateMachine->addState<BlueSlimeAttackState>("Attack");

    // Démarrer la machine à états
    stateMachine->start();
}

void BlueSlimeScript::update() {
    if (isDead) return;

    if (!stateMachine || !transform) return;

    auto timerSystem = ecsManager->getSystem<TimerSystem>();
    if (!timerSystem) return;

    float deltaTime = timerSystem->DeltaTime();
    stateMachine->update(deltaTime);

    auto slimeCollider = ecsManager->getComponent<ColliderComponent>(attachedEntity);
    auto slimeSprite = ecsManager->getComponent<SpriteComponent>(attachedEntity);
    if (!slimeCollider || !slimeSprite) return;

    // Mettre à jour le timer de patrouille
    patrolTimer += deltaTime;
    
    // Vérifier les limites de patrouille
    float distanceFromStart = transform->position.x - initialX;
    bool reachedLeftLimit = distanceFromStart <= -patrolRange;
    bool reachedRightLimit = distanceFromStart >= patrolRange;

    // Changer de direction si nécessaire
    if (patrolTimer >= patrolDuration || reachedLeftLimit || reachedRightLimit) {
        patrolTimer = 0.0f;
        if (reachedLeftLimit) {
            movingLeft = false;
        } else if (reachedRightLimit) {
            movingLeft = true;
        } else {
            movingLeft = !movingLeft; // Inverser la direction périodiquement
        }
        stateMachine->changeState("Move");
    }

    // Mettre à jour le collider pour qu'il corresponde à la taille de la frame actuelle
    const sf::IntRect& currentFrame = slimeSprite->getSprite().getTextureRect();
    sf::Vector2f currentSize;
    currentSize.x = static_cast<float>(currentFrame.size.x);
    currentSize.y = static_cast<float>(currentFrame.size.y);
    
    auto& sprite = slimeSprite->getSprite();
    
    // Gestion du mouvement horizontal
    float moveSpeed = 100.0f; // Vitesse plus lente que le joueur
    bool directionChanged = false;
    
    if (movingLeft) {
        sprite.setOrigin({ currentSize.x, 0.f });
        transform->position.x -= moveSpeed * deltaTime;
        if (!facingLeft) {
            facingLeft = true;
            directionChanged = true;
        }
    }
    else {
        sprite.setOrigin({ currentSize.x / 2.f, 0.f });
        transform->position.x += moveSpeed * deltaTime;
        if (facingLeft) {
            facingLeft = false;
            directionChanged = true;
        }
    }

    // Mettre à jour le collider
    slimeCollider->setSize(currentSize.x, currentSize.y);
    slimeCollider->setPosition(transform->position.x - currentSize.x / 2.f, transform->position.y);
    
    sf::FloatRect newBounds;
    newBounds.position.x = transform->position.x - currentSize.x / 2.f;
    newBounds.position.y = transform->position.y;
    newBounds.size = currentSize;
    slimeCollider->setBoundingBox(newBounds);

    // Mettre à jour la position et l'échelle du sprite
    if (directionChanged) {
        sprite.setScale({ facingLeft ? -1.0f : 1.0f, 1.0f });
    }
    
    // Positionner le sprite
    sf::Vector2f spritePos;
    spritePos.x = transform->position.x;
    spritePos.y = transform->position.y;
    sprite.setPosition(spritePos);

    // Gérer le cooldown d'attaque
    if (attackCooldown > 0.0f) {
        attackCooldown -= deltaTime;
    }

    // Vérifier si le joueur est à portée
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
        if (playerTransform && transform) {
            float distance = std::abs(transform->position.x - playerTransform->position.x);
            if (distance <= detectionRange && attackCooldown <= 0.0f) {
                stateMachine->changeState("Attack");
                attackCooldown = attackCooldownDuration;
            }
        }
    }
}

void BlueSlimeScript::handleEvent(const sf::Event& event) {
    if (stateMachine) {
        stateMachine->handleEvent(event);
    }
}

void BlueSlimeScript::takeDamage(int damage) {
    if (stats && !isDead) {
        stats->takeDamage(damage);
        if (stats->GetValue() <= 0) {
            die();
        }
    }
}

void BlueSlimeScript::die() {
    isDead = true;
    if (animationComponent) {
        animationComponent->setCurrentAnimationIndex(0);
    }
    auto* destroyComp = ecsManager->getComponent<DestroyComponent>(attachedEntity);
    if (!destroyComp) {
        destroyComp = ecsManager->addComponent<DestroyComponent>(attachedEntity);
    }

    destroyComp->markForDestruction();
}

int BlueSlimeScript::getCurrentHealth() const {
    return stats ? stats->GetValue() : 0;
}

int BlueSlimeScript::getMaxHealth() const {
    return stats ? stats->getMaxHealth() : 0;
}

bool BlueSlimeScript::isAlive() const {
    return !isDead;
} 