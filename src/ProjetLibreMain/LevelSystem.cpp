#include "pch.h"
#include "LevelSystem.h"
#include "Transform.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "BlueSlimeScript.h"
#include "AnimationData.h"

LevelSystem::LevelSystem(ECS_Manager* manager) : ecsManager(manager) {
    // Charger la texture du Slime
    if (!slimeTexture.loadFromFile(AnimationData::getSlimeSpritePath())) {
        std::cerr << "Erreur: Impossible de charger la texture du Slime dans LevelSystem" << std::endl;
    }
}

LevelSystem::~LevelSystem() {
    clearLevel();
}

void LevelSystem::loadLevel(int levelNumber) {
    clearLevel();

    switch (levelNumber) {
        case 1:

            addPlatform({ 0.f, 570.f }, { 600.f, 150.f }, "../../res/ProjetLibreMain/BigHightFloating.png");
            addPlatform({ 600.f, 570.f }, { 600.f, 150.f }, "../../res/ProjetLibreMain/BigHightFloating.png");
            addPlatform({1200.f, 570.f }, { 600.f, 150.f }, "../../res/ProjetLibreMain/BigHightFloating.png");
            addPlatform({ 1800.f, 570.f }, { 600.f, 150.f }, "../../res/ProjetLibreMain/BigHightFloating.png");


            
            addPlatform({1400.f, 500.f}, {300.f, 60.f}, "../../res/ProjetLibreMain/MediumFloatingSp.png"); 
            addPlatform({1700.f, 400.f}, {300.f, 60.f}, "../../res/ProjetLibreMain/MediumFloatingSp.png"); 
            addPlatform({2000.f, 300.f}, {300.f, 60.f}, "../../res/ProjetLibreMain/MediumFloatingSp.png"); 
            
            addPlatform({2300.f, 300.f}, {600.f, 60.f}, "../../res/ProjetLibreMain/MediumFloatingSp.png"); 
            
            addPlatform({3000.f, 400.f}, {200.f, 60.f}, "../../res/ProjetLibreMain/MediumFloatingSp.png"); 
            addPlatform({3300.f, 500.f}, {200.f, 60.f}, "../../res/ProjetLibreMain/MediumFloatingSp.png"); 
            addPlatform({3700.f, 600.f}, {800.f, 60.f}, "../../res/ProjetLibreMain/MediumFloatingSp.png"); 
            
            // Ennemis
            addEnemy({300.f, 530.f}, "BlueSlime");
            addEnemy({900.f, 530.f}, "BlueSlime");
            addEnemy({1400.f, 480.f}, "BlueSlime");
            addEnemy({1700.f, 380.f}, "BlueSlime");
          
            break;

        // Autres niveaux à ajouter ici
        default:
            break;
    }

    // Créer les entités à partir des données
    std::cout << "\n=== Creation des plateformes ===" << std::endl;
    for (const auto& data : platformsData) {
        createPlatform(data);
    }

    std::cout << "\n=== Creation des ennemis ===" << std::endl;
    for (const auto& data : enemiesData) {
        createEnemy(data);
    }
}

void LevelSystem::clearLevel() {
    // Vider les listes d'entités
    platforms.clear();
    enemies.clear();

    // Vider les données
    platformsData.clear();
    enemiesData.clear();
}

void LevelSystem::update() {
    // Mise à jour des animations des ennemis
    auto timerSystem = ecsManager->getSystem<TimerSystem>();
    if (!timerSystem) return;

    float deltaTime = timerSystem->DeltaTime();

    // Mise à jour des positions des plateformes
    for (auto platform : platforms) {
        auto transform = ecsManager->getComponent<Transform>(platform);
        auto sprite = ecsManager->getComponent<SpriteComponent>(platform);
        auto collider = ecsManager->getComponent<ColliderComponent>(platform);
        
        if (transform && sprite && collider) {
            const sf::Vector2f& position = transform->getPosition();
            sprite->setPosition(position.x, position.y);
            collider->setPosition(position.x, position.y);
            collider->setBoundingBox(sf::FloatRect(position, collider->getSize()));
        }
    }

    // Mise à jour des ennemis
    for (auto enemy : enemies) {
        auto sprite = ecsManager->getComponent<SpriteComponent>(enemy);
        auto transform = ecsManager->getComponent<Transform>(enemy);
        auto collider = ecsManager->getComponent<ColliderComponent>(enemy);
        
        if (sprite) {
            sprite->update(deltaTime);
            
            if (transform && collider) {
                const sf::Vector2f& position = transform->getPosition();
                sprite->setPosition(position.x, position.y);
                collider->setPosition(position.x, position.y);
            }
        }
    }
}

void LevelSystem::draw(sf::RenderWindow& window, bool showColliders) {
    // Dessiner les plateformes
    for (auto platform : platforms) {
        auto transform = ecsManager->getComponent<Transform>(platform);
        auto collider = ecsManager->getComponent<ColliderComponent>(platform);
        auto sprite = ecsManager->getComponent<SpriteComponent>(platform);
        
        if (transform && sprite) {
            // Dessiner le sprite de la plateforme
            window.draw(sprite->getSprite());
            
            // Dessiner le collider si activé
            if (showColliders && collider) {
                sf::RectangleShape colliderShape;
                const sf::FloatRect& bounds = collider->getBoundingBox();
                colliderShape.setSize(sf::Vector2f(bounds.size.x, bounds.size.y));
                colliderShape.setPosition(bounds.position);
                colliderShape.setFillColor(sf::Color(0, 0, 255, 128));
                colliderShape.setOutlineColor(sf::Color::Blue);
                colliderShape.setOutlineThickness(1.0f);
                window.draw(colliderShape);
            }
        }
    }

    // Dessiner les ennemis
    for (auto enemy : enemies) {
        auto sprite = ecsManager->getComponent<SpriteComponent>(enemy);
        auto collider = ecsManager->getComponent<ColliderComponent>(enemy);
        
        if (sprite) {
            window.draw(sprite->getSprite());
            
            // Dessiner le collider des ennemis si activé
            if (showColliders && collider) {
                sf::RectangleShape colliderShape;
                const sf::FloatRect& bounds = collider->getBoundingBox();
                colliderShape.setSize(sf::Vector2f(bounds.size.x, bounds.size.y));
                colliderShape.setPosition(bounds.position);
                colliderShape.setFillColor(sf::Color(255, 0, 0, 128));
                colliderShape.setOutlineColor(sf::Color::Red);
                colliderShape.setOutlineThickness(1.0f);
                window.draw(colliderShape);
            }
        }
    }
}

void LevelSystem::addPlatform(const sf::Vector2f& position, const sf::Vector2f& size, 
                            const std::string& texturePath, const sf::Color& color) {
    PlatformData data;
    data.position = position;
    data.size = size;
    data.color = color;
    data.texturePath = texturePath;
    platformsData.push_back(data);
}

void LevelSystem::addEnemy(const sf::Vector2f& position, const std::string& type) {
    EnemyData data;
    data.position = position;
    data.type = type;
    enemiesData.push_back(data);
}

void LevelSystem::createPlatform(const PlatformData& data) {
    Entity* platform = ecsManager->createEntity("PlayerPlatform");

    // Ajouter le composant de transformation
    auto platformTransform = ecsManager->addComponent<Transform>(platform);
    platformTransform->setPosition(data.position.x, data.position.y);

    // Ajouter le composant de sprite
    auto platformSprite = ecsManager->addComponent<SpriteComponent>(platform);

    // Gérer la texture
    if (!data.texturePath.empty()) {
        // Vérifier si la texture est déjà chargée
        if (platformTextures.find(data.texturePath) == platformTextures.end()) {
            // Créer et charger la nouvelle texture
            platformTextures[data.texturePath] = sf::Texture();
            if (platformTextures[data.texturePath].loadFromFile(data.texturePath)) {
                std::cout << "Texture de plateforme chargee: " << data.texturePath << std::endl;
                
                // S'assurer que la texture utilise la répétition
                platformTextures[data.texturePath].setRepeated(true);
            } else {
                std::cerr << "Erreur lors du chargement de la texture: " << data.texturePath << std::endl;
                return;
            }
        }

        // Appliquer la texture au sprite en utilisant la référence à la texture stockée
        platformSprite->setTexture(platformTextures[data.texturePath]);
        
        // Ajuster l'échelle du sprite pour correspondre à la taille souhaitée
        sf::Vector2u textureSize = platformTextures[data.texturePath].getSize();
        std::cout << "Taille de la texture: " << textureSize.x << "x" << textureSize.y << std::endl;
        std::cout << "Taille souhaitee: " << data.size.x << "x" << data.size.y << std::endl;
        
        float scaleX = data.size.x / static_cast<float>(textureSize.x);
        float scaleY = data.size.y / static_cast<float>(textureSize.y);
        platformSprite->setScale(scaleX, scaleY);
        
        // Définir la zone de texture à utiliser
        platformSprite->getSprite().setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(textureSize.x), static_cast<int>(textureSize.y)}));
        
        std::cout << "Echelle appliquee: " << scaleX << "x" << scaleY << std::endl;
    }

    // Ajouter le collider
    auto platformCollider = ecsManager->addComponent<ColliderComponent>(platform);
    platformCollider->setPosition(data.position.x, data.position.y);
    platformCollider->setSize(data.size.x, data.size.y);
    platformCollider->setBoundingBox(sf::FloatRect(data.position, data.size));

    platforms.push_back(platform);
}

void LevelSystem::createEnemy(const EnemyData& data) {
    Entity* enemy = ecsManager->createEntity(data.type);
    
    // Ajouter le composant de transformation
    auto transform = ecsManager->addComponent<Transform>(enemy);
    transform->setPosition(data.position.x, data.position.y);

    // Ajouter les composants spécifiques selon le type
    if (data.type == "BlueSlime") {
        // Ajouter le sprite component
        auto spriteComp = ecsManager->addComponent<SpriteComponent>(enemy);
        spriteComp->setTexture(slimeTexture);
        spriteComp->setPosition(data.position.x, data.position.y);

        // Ajouter l'animation
        std::vector<sf::IntRect> idleFrames = AnimationData::getSlimeIdleFrames();
        auto slimeAnimation = ecsManager->addComponent<AnimationComponent>(enemy, idleFrames, 0.1f);
        spriteComp->setAnimation(std::shared_ptr<AnimationComponent>(slimeAnimation, [](AnimationComponent*) {}));

        // Ajouter le script du Slime
        auto slimeScript = ecsManager->addScript<BlueSlimeScript>(enemy);
        
        // Ajouter le collider
        auto collider = ecsManager->addComponent<ColliderComponent>(enemy);
        collider->setPosition(data.position.x, data.position.y);
        collider->setSize(32.f, 32.f);
        
        std::cout << "BlueSlime cree a la position: " << data.position.x << ", " << data.position.y << std::endl;
    }

    enemies.push_back(enemy);
} 