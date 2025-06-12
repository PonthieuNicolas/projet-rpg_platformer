#include "pch.h"
#include "PlayerScript.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Life.h"
#include "TimerSystem.h"
#include "AnimationData.h"
#include "CollisionEvent.h"
#include <chrono>

PlayerScript::PlayerScript() : transform(nullptr), movingRight(true), verticalSpeed(0.0f), onGround(false), isDead(false),
isRunning(false), attackCooldown(0.0f), attackRange(2.0f), attackDamage(10), jumpRequested(false), experienceGained(0) {
}

void PlayerScript::start()
{
	// Récupérer les composants nécessaires
	transform = ecsManager->getComponent<Transform>(attachedEntity);
	animationComponent = ecsManager->getComponent<AnimationComponent>(attachedEntity);
	stats = ecsManager->getComponent<Life>(attachedEntity);

	// Créer et configurer la machine à états
	stateMachine = ecsManager->addComponent<StateMachineComponent>(attachedEntity);
	stateMachine->initialize(attachedEntity, ecsManager, "Idle");

	// Ajouter tous les états possibles
	stateMachine->addState<PlayerIdleState>("Idle");
	stateMachine->addState<PlayerWalkState>("Walk");
	stateMachine->addState<PlayerJumpState>("Jump");
	stateMachine->addState<PlayerAttackState>("Attack");

	// Démarrer la machine à états
	stateMachine->start();
	
	// S'abonner aux événements de collision
	ecsManager->getEventSystem()->subscribe("Collision", [this](Event* event) {
		if (auto collisionEvent = dynamic_cast<CollisionEvent*>(event)) {
			// Vérifier si l'une des entités est le joueur
			if (collisionEvent->entityA == attachedEntity || collisionEvent->entityB == attachedEntity) {
				// Trouver l'autre entité
				Entity* otherEntity = (collisionEvent->entityA == attachedEntity) ? 
									 collisionEvent->entityB : collisionEvent->entityA;
				
				if (otherEntity->getName() == "PlayerPlatform") {
					std::cout << "Platform collision detected with: " << otherEntity->getName() << std::endl;
					this->handlePlatformCollision(otherEntity);
				}
			}
		}
	});
}

void PlayerScript::applyGravity(float deltaTime) {
	if (!onGround) {
		verticalSpeed += gravity * deltaTime;
		if (verticalSpeed > maxFallSpeed) {
			verticalSpeed = maxFallSpeed;
		}
		transform->position.y += verticalSpeed * deltaTime;
	}
}

void PlayerScript::checkGroundCollision() {
	if (transform->position.y >= groundLevel) {
		transform->position.y = groundLevel;
		verticalSpeed = 0;
		onGround = true;
	}
}

void PlayerScript::handlePlatformCollision(Entity* platform) {
	if (!platform || !transform) return;
	
	auto platformCollider = ecsManager->getComponent<ColliderComponent>(platform);
	auto playerCollider = ecsManager->getComponent<ColliderComponent>(attachedEntity);
	
	if (!platformCollider || !playerCollider) return;
	
	// Récupérer les rectangles de collision
	const sf::FloatRect& platformBounds = platformCollider->getBoundingBox();
	const sf::FloatRect& playerBounds = playerCollider->getBoundingBox();
	
	// Calculer les positions relatives
	float playerBottom = playerBounds.position.y + playerBounds.size.y;
	float playerTop = playerBounds.position.y;
	float platformTop = platformBounds.position.y;
	
	// Vérifier le chevauchement horizontal
	bool isOverlappingHorizontally = playerBounds.position.x + playerBounds.size.x > platformBounds.position.x && 
									playerBounds.position.x < platformBounds.position.x + platformBounds.size.x;
	
	// Vérifier si le joueur est au-dessus de la plateforme
	const float collisionMargin = 20.0f;
	bool isAbovePlatform = playerBottom >= platformTop - collisionMargin && 
						  playerBottom <= platformTop + collisionMargin;
	
	// Si le joueur est au-dessus de la plateforme et descend ou est stationnaire
	if (isOverlappingHorizontally && isAbovePlatform && verticalSpeed >= 0) {
		// Placer le joueur sur la plateforme
		float newY = platformTop - playerBounds.size.y;
		transform->position.y = newY;
		playerCollider->setPosition(transform->position.x, newY);
		verticalSpeed = 0;
		
		// Ne logger que le changement d'état au sol
		if (!onGround) {
			onGround = true;
			std::cout << "Etat: Au sol" << std::endl;
		}
	}
	// Si le joueur monte et heurte le dessous de la plateforme
	else if (isOverlappingHorizontally && 
			 playerTop <= platformTop + platformBounds.size.y && 
			 playerTop >= platformTop + platformBounds.size.y - collisionMargin && 
			 verticalSpeed < 0) {
		// Arrêter le mouvement vertical
		verticalSpeed = 0;
		transform->position.y = platformTop + platformBounds.size.y;
		playerCollider->setPosition(transform->position.x, transform->position.y);
	}
}

void PlayerScript::update()
{
	if (!stateMachine || !transform) return;

	auto timerSystem = ecsManager->getSystem<TimerSystem>();
	if (!timerSystem) return;

	float deltaTime = timerSystem->DeltaTime();
	stateMachine->update(deltaTime);
	
	if (attackCooldown > 0.0f) {
		attackCooldown -= deltaTime;
	}

	auto playerCollider = ecsManager->getComponent<ColliderComponent>(attachedEntity);
	auto playerSprite = ecsManager->getComponent<SpriteComponent>(attachedEntity);
	if (!playerCollider || !playerSprite) return;

	// Mettre à jour le collider pour qu'il corresponde à la taille de la frame actuelle
	const sf::IntRect& currentFrame = playerSprite->getSprite().getTextureRect();
	sf::Vector2f currentSize;
	currentSize.x = static_cast<float>(currentFrame.size.x);
	currentSize.y = static_cast<float>(currentFrame.size.y);
	
	auto& sprite = playerSprite->getSprite();
	
	// Gestion du mouvement horizontal
	float moveSpeed = 200.0f;
	bool directionChanged = false;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		sprite.setOrigin({ currentSize.x , 0.f });
		transform->position.x -= moveSpeed * deltaTime;
		if (movingRight) {
			movingRight = false;
			directionChanged = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		sprite.setOrigin({ currentSize.x /10, 0.f });
		transform->position.x += moveSpeed * deltaTime;
		if (!movingRight) {
			movingRight = true;
			directionChanged = true;
		}
	}

	// Mettre à jour le collider
	playerCollider->setSize(currentSize.x, currentSize.y);
	playerCollider->setPosition(transform->position.x - currentSize.x / 2.f, transform->position.y);
	
	sf::FloatRect newBounds;
	newBounds.position.x = transform->position.x - currentSize.x / 2.f;
	newBounds.position.y = transform->position.y;
	newBounds.size = currentSize;
	playerCollider->setBoundingBox(newBounds);

	// Mettre à jour la position et l'échelle du sprite
	if (directionChanged) {
		sprite.setScale({ movingRight ? 1.0f : -1.0f, 1.0f });
	}
	
	// Positionner le sprite
	sf::Vector2f spritePos;
	spritePos.x = transform->position.x;
	spritePos.y = transform->position.y;
	sprite.setPosition(spritePos);

	// Vérifier si le joueur est toujours sur une plateforme
	bool wasOnGround = onGround;
	bool foundPlatform = false;
	const auto& entities = ecsManager->getAllEntities();
	
	// Obtenir la boîte de collision actuelle du joueur
	const sf::FloatRect& playerBounds = playerCollider->getBoundingBox();
	
	for (Entity* entity : entities) {
		if (entity->getName() == "PlayerPlatform") {
			auto platformCollider = ecsManager->getComponent<ColliderComponent>(entity);
			if (platformCollider) {
				const sf::FloatRect& platformBounds = platformCollider->getBoundingBox();
				
				// Vérifier le chevauchement horizontal
				bool isOverlappingHorizontally = 
					playerBounds.position.x + playerBounds.size.x > platformBounds.position.x && 
					playerBounds.position.x < platformBounds.position.x + platformBounds.size.x;
				
				// Vérifier si le joueur est au-dessus de la plateforme
				if (isOverlappingHorizontally) {
					float playerBottom = playerBounds.position.y + playerBounds.size.y;
					float platformTop = platformBounds.position.y;
					const float collisionMargin = 20.0f;
					
					if (playerBottom >= platformTop - collisionMargin && 
						playerBottom <= platformTop + collisionMargin && 
						verticalSpeed >= 0) {
						foundPlatform = true;
						break;
					}
				}
			}
		}
	}

	// Mettre à jour l'état onGround et la vitesse verticale
	if (!foundPlatform && onGround) {
		onGround = false;
		verticalSpeed = 0;
		// Passer à l'état de saut quand le joueur commence à tomber
		if (stateMachine->getCurrentStateName() != "Jump") {
			stateMachine->changeState("Jump");
			std::cout << "Etat: Chute" << std::endl;
		}
	}

	// Gestion du saut - uniquement possible si le joueur est au sol
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && onGround && 
		stateMachine->getCurrentStateName() != "Attack") {
		verticalSpeed = -jumpForce;
		onGround = false;
		stateMachine->changeState("Jump");
		std::cout << "Etat: Saut" << std::endl;
	}

	// Appliquer la gravité et mettre à jour la position si pas au sol
	if (!onGround) {
		float oldVerticalSpeed = verticalSpeed;
		verticalSpeed += gravity * deltaTime;
		if (verticalSpeed > maxFallSpeed) {
			verticalSpeed = maxFallSpeed;
		}
		
		float oldY = transform->position.y;
		transform->position.y += verticalSpeed * deltaTime;
		
		// Synchroniser la position du collider
		sf::Vector2f newPos(transform->position.x, transform->position.y);
		playerCollider->setPosition(newPos.x, newPos.y);
		playerCollider->setBoundingBox(sf::FloatRect(newPos, currentSize));
		
		// Vérifier les collisions avec toutes les plateformes
		for (Entity* entity : entities) {
			if (entity->getName() == "PlayerPlatform") {
				handlePlatformCollision(entity);
				if (onGround) {
					// Retourner à l'état Idle quand on atterrit
					if (stateMachine->getCurrentStateName() == "Jump") {
						stateMachine->changeState("Idle");
					}
					break;
				}
			}
		}

		// Ne logger que les changements significatifs de vitesse ou de position
		if (std::abs(oldVerticalSpeed - verticalSpeed) > 200.0f) {
			std::cout << "Vitesse verticale: " << verticalSpeed << std::endl;
		}
	}
}

void PlayerScript::handleEvent(const sf::Event& event)
{
	if (stateMachine) {
		stateMachine->handleEvent(event);
	}
}

void PlayerScript::attack()
{
	// Ne peut attaquer que si au sol et pas en cooldown
	if (stateMachine && attackCooldown <= 0.0f && onGround) {
		stateMachine->changeState("Attack");
		attackCooldown = 0.5f; // Cooldown de 0.5 secondes
	}
}

void PlayerScript::takeDamage(int damage)
{
	if (stats) {
		// Vérifier si le joueur est déjà mort
		if (stats->getCurrentHealth() > 0) {
			std::cout << "\n=== DEGATS RECUS ===" << std::endl;
			std::cout << "Montant des degats: " << damage << std::endl;
			std::cout << "Vie avant degats: " << stats->getCurrentHealth() << "/" << stats->getMaxHealth() << std::endl;

			// Utiliser le TimerSystem pour l'horodatage
			if (auto timerSystem = ecsManager->getSystem<TimerSystem>()) {
				std::cout << "Temps de jeu lors des degats: " << timerSystem->TotalTime() << " secondes" << std::endl;
			}

			stats->takeDamage(damage);

			std::cout << "Vie apres degats: " << stats->getCurrentHealth() << "/" << stats->getMaxHealth() << std::endl;
		}

		// Vérifier si le joueur est mort
		if (stats->getCurrentHealth() <= 0 && !isDead) {
			isDead = true; // Marquer le joueur comme mort
			std::cout << "ETAT CRITIQUE: Le joueur est mort!" << std::endl;
			die();
		}
		if (stats->getCurrentHealth() > 0) 
		{
			std::cout << "===================" << std::endl;
		}
	}

}

void PlayerScript::die()
{
	isDead = true;
	std::cout << "The player is dead!" << std::endl;
}

// Implémentation des méthodes du système de niveau
void PlayerScript::gainExperience(int exp)
{
    if (stats) {
        stats->addExperience(exp);
        experienceGained += exp;
        
        // Afficher un message de gain d'expérience
        std::cout << "Experience gagnee: " << exp << " (Total: " << experienceGained << ")" << std::endl;
    }
}

int PlayerScript::getLevel() const
{
    return stats ? stats->getLevel() : 1;
}

int PlayerScript::getExperience() const
{
    return stats ? stats->getExperience() : 0;
}

int PlayerScript::getExperienceToNextLevel() const
{
    return stats ? stats->getExperienceToNextLevel() : 100;
}

int PlayerScript::getMaxHealth() const
{
    return stats ? stats->getMaxHealth() : 100;
}

int PlayerScript::getCurrentHealth() const
{
    return stats ? stats->getCurrentHealth() : 100;
}

int PlayerScript::getAttack() const
{
    return stats ? stats->getAttack() : 10;
}

int PlayerScript::getDefense() const
{
    return stats ? stats->getDefense() : 5;
}

void PlayerScript::heal(int amount)
{
    if (stats) {
        stats->heal(amount);
        std::cout << "Soin recu: " << amount << " (Sante actuelle: " << stats->getCurrentHealth() << "/" << stats->getMaxHealth() << ")" << std::endl;
    }
}
