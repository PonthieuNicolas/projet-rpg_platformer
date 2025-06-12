#include "pch.h"
#include "GameManager.h"
#include "AnimationData.h"
#include <optional>
#include "InputSystem.h"
#include "StateMachineSystem.h"
#include <iostream>
#include <sstream>
#include <iomanip>

GameManager::GameManager()
	: mCollider(nullptr), mCollider2(nullptr), gameManager(new ECS_Manager()), interfaceSystem(nullptr), cameraSystem(nullptr), levelSystem(nullptr),
	showColliders(false)
{
	// Charger les textures
	if (!slimeTexture.loadFromFile(AnimationData::getSlimeSpritePath())) {
		std::cerr << "Erreur: Impossible de charger la texture du Slime" << std::endl;
	}
	if (!blackWizardTexture.loadFromFile(AnimationData::getBlackWizardSpritePath())) {
		std::cerr << "Erreur: Impossible de charger la texture du Black Wizard" << std::endl;
	}

	if (!backgroundTexrure.loadFromFile(AnimationData::getBackgroundSprite())) {
		std::cerr << "Erreur: Impossible de charger la texture du Background" << std::endl;
	}

	if (!projectileTexture.loadFromFile(AnimationData::getProjectileSprite())) {
    std::cerr << "Erreur: Impossible de charger la texture du Projectile" << std::endl;
    }

    if (!homingCardTexture.loadFromFile(AnimationData::getSkillCardSprite())) {
        std::cerr << "Erreur: Impossible de charger la texture de la carte Homing" << std::endl;
    }
}

GameManager::~GameManager() {
	delete mCollider;
	delete mCollider2;
	delete gameManager;
	delete interfaceSystem;
	delete cameraSystem;
	delete levelSystem;
    delete backgroundMusic;

	mCollider = nullptr;
	mCollider2 = nullptr;
	gameManager = nullptr;
	interfaceSystem = nullptr;
	cameraSystem = nullptr;
	levelSystem = nullptr;
}

void GameManager::OnInit() {
    window.create(sf::VideoMode({ 1200, 720 }), "My window");
    mTimer.Reset();
    mTimer.Start();

	// Initialiser la vue de la caméra avec un zoom arrière
	gameView = window.getDefaultView();
	gameView.zoom(0.9f);
	cameraSystem = new CameraSystem(gameView, gameManager);
	cameraSystem->setDeadzone(sf::Vector2f(100.f, 100.f));
	cameraSystem->setLerpFactor(0.05f);
	cameraSystem->setOffset(sf::Vector2f(0.f, 0.f));

	// Initialiser la musique de fond
    std::string musicFile = "../../res/ProjetLibreMain/RenovatioOfTheMind.mp3";
    backgroundMusic = new MusicComponent(musicFile);
    backgroundMusic->setLoop(true);
    backgroundMusic->play();

	// Charger la police pour les textes
	if (!mFont.openFromFile("../../res/SfmlMotor/Arial.ttf")) {
		std::cerr << "Erreur: Impossible de charger la police" << std::endl;
	}

	// Initialiser le système d'interface
	interfaceSystem = new InterfaceSystem(mFont);
	interfaceSystem->setGameView(&gameView);
	interfaceSystem->init();
	interfaceSystem->setPlayerStatsTexture(blackWizardTexture);

    // Configurer l'animation du sprite du joueur pour la fenêtre de stats
    std::vector<sf::IntRect> idleFrames = AnimationData::getBlackWizardIdleFrames();
    if (!idleFrames.empty()) {
        interfaceSystem->setPlayerIdleFrames(idleFrames);
    }

    std::cout << "=== Chargement des textures ===" << std::endl;

    // Appliquer les textures aux sprites
    std::cout << "Application de la texture du Slime..." << std::endl;
    SpComp.setTexture(slimeTexture);
    SpComp.setPosition(100.f, 100.f);
    std::cout << "Position Slime: " << SpComp.getSprite().getPosition().x << ", "
        << SpComp.getSprite().getPosition().y << std::endl;
    std::cout << "Taille texture Slime: " << slimeTexture.getSize().x << "x"
        << slimeTexture.getSize().y << std::endl;

    std::cout << "Application de la texture du Background..." << std::endl;
    Background.setTexture(backgroundTexrure, true);
    Background.setPosition(-500.f, -280.f);
	Background.setScale(1.6f, 1.6f);
    std::cout << "Position Background: " << Background.getSprite().getPosition().x << ", " << Background.getSprite().getPosition().y << std::endl;

    std::cout << "Application de la texture du Projectile..." << std::endl;
    Projectile.setTexture(projectileTexture, true);
	Projectile.setPosition(0.f, 200.f);
	std::cout << "Position Projectile: " << Projectile.getSprite().getPosition().x << ", " << Projectile.getSprite().getPosition().y << std::endl;

    std::cout << "Application de la texture du HomingCard..." << std::endl;
    HomingCard.setTexture(homingCardTexture, true);
    HomingCard.setPosition(50.f, 200.f);
	HomingCard.setScale(0.35f, 0.35f);
    std::cout << "Position HomingCard: " << HomingCard.getSprite().getPosition().x << ", " << HomingCard.getSprite().getPosition().y << std::endl;

    // Charger les animations
    std::cout << "\n=== Configuration des animations ===" << std::endl;
    LoadAnimationFrame();

    // Initialiser l'ECS
    std::cout << "\n=== Initialisation de l'ECS ===" << std::endl;
    SetupECS();
}

void GameManager::SetupECS()
{
    // Créer les systèmes
    auto timerSystem = gameManager->addSystem<TimerSystem>();
    auto animSystem = gameManager->addSystem<AnimationSystem>();
    auto collisionSystem = gameManager->addSystem<CollisionSystem>();
    auto inputSystem = gameManager->addSystem<InputSystem>();
    auto syncSystem = gameManager->addSystem<MovementSyncSystem>();
    auto stateMachineSystem = gameManager->addSystem<StateMachineSystem>();

    // Configurer le TimerSystem
    timerSystem->Reset();
    timerSystem->Start();

    // Configurer le StateMachineSystem
    if (stateMachineSystem) {
        stateMachineSystem->setTimer(timerSystem);
    }

	// Créer le système de niveau
	levelSystem = new LevelSystem(gameManager);

	// Créer le joueur
	player = CreatePlayer(gameManager);

    homingSkill = new Skill("Homing", sf::Vector2f(50.f, 50.f));

	// Charger le niveau 1
	levelSystem->loadLevel(1);

	// S'assurer que le système de collision est configuré
	if (collisionSystem) {
		std::cout << "Configuration du système de collision..." << std::endl;
		collisionSystem->setECSManager(gameManager);
	}

	// Configurer la caméra pour suivre le joueur
	if (cameraSystem) {
		cameraSystem->setTarget(player);
		cameraSystem->start();
	}

	// Démarrer les systèmes dans l'ordre
	std::cout << "Starting systems..." << std::endl;
	timerSystem->start();
	std::cout << "TimerSystem started" << std::endl;
	animSystem->start();
	std::cout << "AnimationSystem started" << std::endl;
	collisionSystem->start();
	std::cout << "CollisionSystem started" << std::endl;
	inputSystem->start();
	std::cout << "InputSystem started" << std::endl;
	syncSystem->start();
	std::cout << "MovementSyncSystem started" << std::endl;
	if (stateMachineSystem) {
		stateMachineSystem->start();
		std::cout << "StateMachineSystem started" << std::endl;
	}
}

void GameManager::LoadAnimationFrame() {
    // Animation du Slime
    std::vector<sf::IntRect> slimeIdleFrames = AnimationData::getSlimeIdleFrames();
    if (!slimeIdleFrames.empty()) {
        auto slimeEntity = gameManager->createEntity("Slime");
        auto slimeAnim = gameManager->addComponent<AnimationComponent>(slimeEntity, slimeIdleFrames, 0.1f);
        if (slimeAnim) {
            SpComp.setAnimation(std::shared_ptr<AnimationComponent>(slimeAnim));
        }
    }
}

void GameManager::OnRender() {
    Draw(mTimer);
}

void GameManager::Run() {
    OnInit();

    // Les textures et positions sont déjà configurées dans OnInit()
    sf::FloatRect bounds = SpComp.getSprite().getGlobalBounds();
    mCollider = new ColliderComponent(bounds.position.x, bounds.position.y, bounds.size.x, bounds.size.y);
    mCollider2 = new ColliderComponent(400.f, 200.f, bounds.size.x, bounds.size.y);

    int frameCount = 0;
    std::string lastState = "";

    sf::Clock clock;
    float deltaTime = 0.0f;

    // Démarrer le TimerSystem
    mTimer.Start();

    while (window.isOpen()) {
        // Calculer le deltaTime
        deltaTime = clock.restart().asSeconds();
        mTimer.Tick();

        // Gestion des événements
        while (const std::optional<sf::Event> eventOpt = window.pollEvent()) {
            const sf::Event& event = eventOpt.value();

            if (event.is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i pixelPos{ mouseEvent->position };
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, window.getDefaultView());

                if (HomingCard.getSprite().getGlobalBounds().contains(worldPos)) {
                    if (homingSkill && !homingSkill->isUnlocked()) {
                        homingSkill->unlock();
                        std::cout << "Skill Homing débloqué !" << std::endl;
                    }
                }
            }
        }


        // Mise à jour et dessin
        OnUpdate(mTimer);
        Draw(mTimer);
        sf::sleep(sf::milliseconds(16)); // ~60 FPS
    }
}

void GameManager::OnUpdate(const TimerSystem& gt) {
    
    static int frameCount = 0;
    frameCount++;

    if (auto timerSystem = gameManager->getSystem<TimerSystem>()) {
        timerSystem->Tick();
    }

    SpComp.update(gt.DeltaTime());

    if (gameManager) {
        gameManager->update();
    }

    if (player) {
        auto transform = gameManager->getComponent<Transform>(player);
        auto spriteComp = gameManager->getComponent<SpriteComponent>(player);
        if (transform && spriteComp) {
            spriteComp->setPosition(transform->getPosition().x, transform->getPosition().y);
        }

        // Exemple d'interaction : augmentation d'expérience avec la touche L
        static bool lKeyPressed = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
            if (!lKeyPressed) {
                lKeyPressed = true;
                auto playerScript = gameManager->getScript<PlayerScript>(player);
                if (playerScript) {
                    playerScript->gainExperience(50);
                    std::cout << "Niveau: " << playerScript->getLevel() << std::endl;
                }
            }
        }
        else {
            lKeyPressed = false;
        }

        // Soins (H) et dégâts (J)
        static bool hKeyPressed = false;
        static bool jKeyPressed = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
            if (!hKeyPressed) {
                hKeyPressed = true;
                auto lifeComponent = gameManager->getComponent<Life>(player);
                if (lifeComponent) {
                    lifeComponent->heal(20);
                    std::cout << "Soin appliqué, HP: " << lifeComponent->getCurrentHealth() << std::endl;
                }
            }
        }
        else {
            hKeyPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
            if (!jKeyPressed) {
                jKeyPressed = true;
                auto lifeComponent = gameManager->getComponent<Life>(player);
                if (lifeComponent) {
                    lifeComponent->takeDamage(15);
                    std::cout << "Dégâts infligés, HP: " << lifeComponent->getCurrentHealth() << std::endl;
                }
            }
        }
        else {
            jKeyPressed = false;
        }

        // Mise à jour de l'interface
        auto lifeComponent = gameManager->getComponent<Life>(player);
        if (lifeComponent) {
            interfaceSystem->update(lifeComponent, gt.DeltaTime());
        }

        auto playerScript = gameManager->getScript<PlayerScript>(player);
        if (playerScript && playerScript->getLevel() >= 2 && homingSkill && !homingSkill->isUnlocked()) {
            homingSkill->draw(window);
        }

    }

    // Mise à jour des collisions (pour debug)
    sf::Vector2f pos = SpComp.getSprite().getPosition();
    mCollider->setPosition(pos.x, pos.y);
    if (mCollider->isCollidingWith(*mCollider2)) {
        Entity entityA("Player", 1);
        Entity entityB("Obstacle", 2);
        CollisionEvent collisionEvent(&entityA, &entityB);
    }



    static bool eKeyPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
        if (!eKeyPressed) {
            eKeyPressed = true;

            Entity* projectileEntity = gameManager->createEntity("Projectile");

            auto projectileTransform = gameManager->addComponent<Transform>(projectileEntity);
            if (player) {
                auto playerTransform = gameManager->getComponent<Transform>(player);
                auto playerSprite = gameManager->getComponent<SpriteComponent>(player);
                if (playerTransform && playerSprite) {
                    sf::Vector2f playerPos = playerTransform->getPosition();

                    sf::FloatRect playerBounds = playerSprite->getSprite().getLocalBounds();
                    
                    bool facingLeft = (playerSprite->getSprite().getScale().x < 0.f);

                    sf::Vector2f projPos;
                    projPos.x = playerPos.x + playerBounds.position.x;
                    projPos.x = facingLeft ? playerPos.x - playerBounds.position.x : playerPos.x + playerBounds.position.y;
                    projPos.y = playerPos.y + (playerBounds.position.y / 2.f) - (static_cast<float>(projectileTexture.getSize().y) / 2.f) +50;
                    projectileTransform->setPosition(projPos);
                    std::cout << "Projectile créé à : (" << projPos.x << ", " << projPos.y << ")" << std::endl;
                }
            }

            auto projectileScript = gameManager->addScript<BasicProjectileScript>(projectileEntity);
            projectileScript->setEntity(projectileEntity);
            auto playerSprite = gameManager->getComponent<SpriteComponent>(player);
            if (playerSprite) {
                bool facingLeft = (playerSprite->getSprite().getScale().x < 0.f);
                sf::Vector2f projVelocity = facingLeft ? sf::Vector2f(-200.f, 0.f) : sf::Vector2f(200.f, 0.f);
                projectileScript->setVelocity(projVelocity);
            }
            projectileScript->start();

            auto projectileSprite = gameManager->addComponent<SpriteComponent>(projectileEntity);
            projectileSprite->setTexture(projectileTexture, true);
            projectileSprite->setScale(1.5f, 1.5f);
            projectileSprite->setPosition(projectileTransform->getPosition().x, projectileTransform->getPosition().y);
            std::cout << "SpriteComponent ajouté pour le projectile." << std::endl;
        }
    }
    else {
        eKeyPressed = false;
    }

    // Touche T : Création d'un projectile à tête chercheuse
    static bool tKeyPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
        if (!tKeyPressed) {
            tKeyPressed = true;
            if (homingSkill && homingSkill->isUnlocked()) {
                std::cout << "Création d'un HomingProjectile..." << std::endl;
                Entity* homingProjectileEntity = gameManager->createEntity("HomingProjectile");

                auto homingTransform = gameManager->addComponent<Transform>(homingProjectileEntity);
                if (player) {
                    auto playerTransform = gameManager->getComponent<Transform>(player);
                    if (playerTransform) {
                        sf::Vector2f playerPos = playerTransform->getPosition();
                        homingTransform->setPosition(playerPos.x, playerPos.y);
                    }
                }

                auto homingScript = gameManager->addScript<HomingProjectileScript>(homingProjectileEntity);
                homingScript->setEntity(homingProjectileEntity);

                bool facingLeft = false;
                if (player) {
                    auto playerSprite = gameManager->getComponent<SpriteComponent>(player);
                    if (playerSprite) {
                        facingLeft = (playerSprite->getSprite().getScale().x < 0.f);
                    }
                }
                sf::Vector2f initialVelocity = facingLeft ? sf::Vector2f(-200.f, 0.f) : sf::Vector2f(200.f, 0.f);
                homingScript->setVelocity(initialVelocity);

                homingScript->start();

                auto homingSprite = gameManager->addComponent<SpriteComponent>(homingProjectileEntity);
                homingSprite->setTexture(projectileTexture, true);
                homingSprite->setScale(1.5f, 1.5f);
                homingSprite->setPosition(homingTransform->getPosition().x, homingTransform->getPosition().y);
                std::cout << "HomingProjectile créé et affiché." << std::endl;

                // Recherche de la cible la plus proche
                Entity* closestTarget = nullptr;
                float closestDistanceSq = std::numeric_limits<float>::max();
                if (player) {
                    auto playerTransform = gameManager->getComponent<Transform>(player);
                    if (playerTransform) {
                        sf::Vector2f playerPos = playerTransform->getPosition();
                        const std::vector<Entity*>& allEntities = gameManager->getAllEntities();
                        for (Entity* entity : allEntities) {
                            if (entity->getName() == "Player" || entity == homingProjectileEntity)
                                continue;
                            auto entityTransform = gameManager->getComponent<Transform>(entity);
                            if (entityTransform) {
                                sf::Vector2f entityPos = entityTransform->getPosition();
                                float dx = entityPos.x - playerPos.x;
                                float dy = entityPos.y - playerPos.y;
                                float distanceSq = dx * dx + dy * dy;
                                if (distanceSq < closestDistanceSq) {
                                    closestDistanceSq = distanceSq;
                                    closestTarget = entity;
                                }
                            }
                        }
                    }
                }
                if (closestTarget) {
                    homingScript->setTarget(closestTarget);
                    std::cout << "Cible définie pour HomingProjectile : " << closestTarget->getName() << std::endl;
                }
                else {
                    std::cout << "Aucune cible trouvée pour HomingProjectile." << std::endl;
                }
            }
            else {
                std::cout << "Skill Homing non débloqué, impossible d'utiliser des Homing Projectiles." << std::endl;
            }
        }
    }
    else {
        tKeyPressed = false;
    }



	// Mise à jour du système de niveau
	if (levelSystem) {
		levelSystem->update();
	}

	// Mise à jour du système ECS (qui inclut maintenant l'AnimationSystem)
	if (gameManager) {
		gameManager->update();
	}

	// Synchroniser la position du sprite avec le Transform pour le joueur
	if (player) {
		auto transform = gameManager->getComponent<Transform>(player);
		auto spriteComp = gameManager->getComponent<SpriteComponent>(player);
		auto collider = gameManager->getComponent<ColliderComponent>(player);

		if (transform && spriteComp && collider) {
			spriteComp->setPosition(transform->getPosition().x, transform->getPosition().y);
			collider->setPosition(transform->getPosition().x, transform->getPosition().y);
		}

		// Test du système de niveau avec la touche L
		static bool lKeyPressed = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
			if (!lKeyPressed) {
				lKeyPressed = true;

				// Récupérer le script du joueur
				auto playerScript = gameManager->getScript<PlayerScript>(player);
				if (playerScript) {
					playerScript->gainExperience(50);

					std::cout << "Statistiques actuelles du joueur:" << std::endl;
					std::cout << "Niveau: " << playerScript->getLevel() << std::endl;
					std::cout << "Exp: " << playerScript->getExperience() << "/" << playerScript->getExperienceToNextLevel() << std::endl;
					std::cout << "HP: " << playerScript->getCurrentHealth() << "/" << playerScript->getMaxHealth() << std::endl;
					std::cout << "Att: " << playerScript->getAttack() << std::endl;
					std::cout << "Def: " << playerScript->getDefense() << std::endl;
				}
			}
		}
		else {
			lKeyPressed = false;
		}

		// Debug - Gestion de la vie du joueur
		static bool hKeyPressed = false;
		static bool jKeyPressed = false;

		// Touche H pour soigner le joueur
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
			if (!hKeyPressed && player) {
				hKeyPressed = true;
				auto lifeComponent = gameManager->getComponent<Life>(player);
				if (lifeComponent) {
					lifeComponent->heal(20);
					std::cout << "Soin appliqué! Vie actuelle: " << lifeComponent->getCurrentHealth() 
							 << "/" << lifeComponent->getMaxHealth() << std::endl;
				}
			}
		}
		else {
			hKeyPressed = false;
		}

		// Touche J pour infliger des dégâts au joueur
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
			if (!jKeyPressed && player) {
				jKeyPressed = true;
				auto lifeComponent = gameManager->getComponent<Life>(player);
				if (lifeComponent) {
					lifeComponent->takeDamage(15);
					std::cout << "Dégâts infligés! Vie actuelle: " << lifeComponent->getCurrentHealth() 
							 << "/" << lifeComponent->getMaxHealth() << std::endl;
				}
			}
		}
		else {
			jKeyPressed = false;
		}

		// Mise à jour de l'interface
		auto lifeComponent = gameManager->getComponent<Life>(player);
		if (lifeComponent) {
			interfaceSystem->update(lifeComponent, gt.DeltaTime());
		}
	}

	// Mise à jour des collisions
	pos = SpComp.getSprite().getPosition();
	mCollider->setPosition(pos.x, pos.y);

	if (mCollider->isCollidingWith(*mCollider2)) {
		Entity entityA("Player", 1);
		Entity entityB("Obstacle", 2);
		CollisionEvent collisionEvent(&entityA, &entityB);
	}

	// Mise à jour de l'interface
	if (player) {
		auto lifeComponent = gameManager->getComponent<Life>(player);
		if (lifeComponent) {
			interfaceSystem->update(lifeComponent, gt.DeltaTime());
		}
	}

	// Toggle de la fenêtre de statistiques avec la touche P
	static bool pKeyPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
		if (!pKeyPressed) {
			pKeyPressed = true;
			interfaceSystem->toggleStatsWindow();
		}
	}
	else {
		pKeyPressed = false;
	}

	// Toggle de l'affichage des colliders avec la touche B
	static bool bKeyPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B)) {
		if (!bKeyPressed) {
			bKeyPressed = true;
			showColliders = !showColliders;
			std::cout << "Affichage des colliders: " << (showColliders ? "activé" : "désactivé") << std::endl;
		}
	}
	else {
		bKeyPressed = false;
	}

	if (cameraSystem) {
		cameraSystem->update();
	}

    // --- Synchronisation du SpriteComponent pour tous les projectiles ---
    const std::vector<Entity*>& allEntities = gameManager->getAllEntities();
    for (Entity* entity : allEntities) {
        if (entity->getName() == "Projectile") {
            auto projTransform = gameManager->getComponent<Transform>(entity);
            auto projSprite = gameManager->getComponent<SpriteComponent>(entity);
            if (projTransform && projSprite) {
                projSprite->setPosition(projTransform->getPosition().x, projTransform->getPosition().y);
            }
        }
    }

}



void GameManager::Draw(const TimerSystem& gt) {
    window.clear(sf::Color::Black);

    // Appliquer la vue de la caméra pour le monde
    if (cameraSystem) {
        window.setView(gameView);
    }
    window.draw(Background.getSprite());

    // Dessiner les plateformes et les ennemis via le LevelSystem
    if (levelSystem) {
        levelSystem->draw(window, showColliders);
    }

    // Dessiner le joueur
    if (player) {
        auto playerSprite = gameManager->getComponent<SpriteComponent>(player);
        if (playerSprite) {
            window.draw(playerSprite->getSprite());
        }
    }

    // Affichage du skill si le joueur a atteint le niveau requis et si le skill n'est pas débloqué
    auto playerScript = gameManager->getScript<PlayerScript>(player);
    if (playerScript && playerScript->getLevel() >= 2 && homingSkill && !homingSkill->isUnlocked()) {
        window.setView(window.getDefaultView());
        sf::Vector2f viewCenter = window.getDefaultView().getCenter();
        sf::FloatRect spriteBounds = HomingCard.getSprite().getGlobalBounds();
        HomingCard.setPosition(viewCenter.x+75 - spriteBounds.position.x / 2,
            viewCenter.y-250 - spriteBounds.position.y / 2);
        window.draw(HomingCard.getSprite());
    }

    // Dessiner les projectiles
    const std::vector<Entity*>& allEntities = gameManager->getAllEntities();
    for (Entity* entity : allEntities) {
        std::string name = entity->getName();
        if (name == "Projectile" || name == "HomingProjectile") {
            auto projTransform = gameManager->getComponent<Transform>(entity);
            auto projSprite = gameManager->getComponent<SpriteComponent>(entity);
            if (projTransform && projSprite) {
                projSprite->setPosition(projTransform->getPosition().x, projTransform->getPosition().y);
                window.draw(projSprite->getSprite());
            }
        }
    }

    interfaceSystem->draw(window);
    window.display();
}

Entity* GameManager::CreatePlayer(ECS_Manager* ecsManager)
{
    std::cout << "Creating Player..." << std::endl;
    player = ecsManager->createEntity("Player");


	// Position initiale du joueur
	float initialPosX = 300.0f;
	float initialPosY = 250.0f;

    auto playerTransform = ecsManager->addComponent<Transform>(player);
    playerTransform->setPosition(initialPosX, initialPosY);

    auto playerSprite = ecsManager->addComponent<SpriteComponent>(player);
    playerSprite->setTexture(blackWizardTexture);
    playerSprite->setPosition(initialPosX, initialPosY);

    std::vector<sf::IntRect> idleFrames = AnimationData::getBlackWizardIdleFrames();
    auto playerAnimation = ecsManager->addComponent<AnimationComponent>(player, idleFrames, 0.1f);
    playerSprite->setAnimation(std::shared_ptr<AnimationComponent>(playerAnimation, [](AnimationComponent*) {}));

	auto playerStats = ecsManager->addComponent<Life>(player, 100);

	auto playerCollider = ecsManager->addComponent<ColliderComponent>(player);
	
	float colliderWidth = 32.0f;
	float colliderHeight = 64.0f;
	
	playerCollider->setSize(colliderWidth, colliderHeight);
	playerCollider->setPosition(initialPosX, initialPosY);
	playerCollider->setBoundingBox(sf::FloatRect({initialPosX, initialPosY},{colliderWidth, colliderHeight}));

	PlayerScript* ps = ecsManager->addScript<PlayerScript>(player);

	std::cout << "Player created successfully" << std::endl;
	return player;
}

Entity* GameManager::CreateBlueSlime(ECS_Manager* ecsManager)
{
	std::cout << "Creating Blue Slime..." << std::endl;
	blueSlime = ecsManager->createEntity("BlueSlime");

	float initialPosX = 300.0f;
	float initialPosY = 455.0f;

	auto slimeTransform = ecsManager->addComponent<Transform>(blueSlime);
	slimeTransform->setPosition(initialPosX, initialPosY);

	auto slimeSprite = ecsManager->addComponent<SpriteComponent>(blueSlime);
	slimeSprite->setTexture(slimeTexture);
	slimeSprite->setPosition(initialPosX, initialPosY);

	std::vector<sf::IntRect> idleFrames = AnimationData::getSlimeIdleFrames();
	auto slimeAnimation = ecsManager->addComponent<AnimationComponent>(blueSlime, idleFrames, 0.1f);
	slimeSprite->setAnimation(std::shared_ptr<AnimationComponent>(slimeAnimation, [](AnimationComponent*) {}));

	auto slimeStats = ecsManager->addComponent<Life>(blueSlime, 50);

	auto slimeCollider = ecsManager->addComponent<ColliderComponent>(blueSlime);

	BlueSlimeScript* slimeScript = ecsManager->addScript<BlueSlimeScript>(blueSlime);

	std::cout << "Blue Slime created successfully" << std::endl;
	return blueSlime;
}

Entity* GameManager::CreatePlayerPlatform(ECS_Manager* ecsManager)
{
	std::cout << "Creating Player Platform..." << std::endl;
	playerPlatform = ecsManager->createEntity("PlayerPlatform");

	float initialPosX=0 ;
	float initialPosY =0;
	float platformWidth =0;
	float platformHeight =0;

	auto platformTransform = ecsManager->addComponent<Transform>(playerPlatform);
	platformTransform->setPosition(initialPosX, initialPosY);

	auto platformSprite = ecsManager->addComponent<SpriteComponent>(playerPlatform);
	
	sf::RectangleShape platformShape;
	platformShape.setSize(sf::Vector2f(platformWidth, platformHeight));
	platformShape.setFillColor(sf::Color(100, 100, 100));
	platformShape.setPosition({ initialPosX, initialPosY });
	
	auto platformCollider = ecsManager->addComponent<ColliderComponent>(playerPlatform);
	platformCollider->setPosition(initialPosX, initialPosY);
	platformCollider->setSize(platformWidth, platformHeight);
	platformCollider->setBoundingBox(sf::FloatRect({initialPosX, initialPosY}, {platformWidth, platformHeight}));

	return playerPlatform;
}
