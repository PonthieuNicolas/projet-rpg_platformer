#include "pch.h"
#include "InterfaceSystem.h"
#include <sstream>
#include <iomanip>

InterfaceSystem::InterfaceSystem(const sf::Font& font)
    : font(font), showStatsWindow(false), currentFrame(0), frameTimer(0.f), frameDuration(0.30f),
    healthCircleRadius(30.f), gameView(nullptr)
{
    statsText = new sf::Text(font);
    
    levelText = new sf::Text(font);
    
    expText = new sf::Text(font);
    
    healthText = new sf::Text(font);
    
    attackText = new sf::Text(font);
    
    defenseText = new sf::Text(font);
    
    playerStatsSprite = nullptr;
}

InterfaceSystem::~InterfaceSystem() {
    delete statsText;
    delete levelText;
    delete expText;
    delete healthText;
    delete attackText;
    delete defenseText;
    delete playerStatsSprite;
}

void InterfaceSystem::init() {
    initStatsWindow();
    initHealthCircle();
}

void InterfaceSystem::initStatsWindow() {
    // Configuration de la fenêtre de stats
    statsBackground.setSize(sf::Vector2f(300.f, 400.f));
    statsBackground.setFillColor(sf::Color(0, 0, 0, 200));

    // Configuration de la barre d'expérience
    expBarBackground.setSize(sf::Vector2f(280.f, 20.f));
    expBarBackground.setFillColor(sf::Color(50, 50, 50, 200));
    expBarFill.setSize(sf::Vector2f(0.f, 20.f));
    expBarFill.setFillColor(sf::Color(0, 255, 0, 200));

    // Configuration des textes
    statsText->setCharacterSize(24);
    levelText->setCharacterSize(24);
    expText->setCharacterSize(20);
    healthText->setCharacterSize(20);
    attackText->setCharacterSize(20);
    defenseText->setCharacterSize(20);
}

void InterfaceSystem::initHealthCircle() {
    healthCircle.setRadius(healthCircleRadius);
    healthCircle.setFillColor(sf::Color::Red);
    healthCircle.setOrigin({ healthCircleRadius, healthCircleRadius });
    
    healthCircleBackground.setRadius(healthCircleRadius);
    healthCircleBackground.setFillColor(sf::Color(100, 100, 100, 200));
    healthCircleBackground.setOrigin({ healthCircleRadius, healthCircleRadius });
}

void InterfaceSystem::updateInterfacePositions() {
    if (!gameView) return;

    // Utiliser la vue HUD pour le positionnement fixe
    sf::Vector2f hudSize = hudView.getSize();
    
    // Positionner l'indicateur de vie en haut à gauche
    healthCirclePosition = {50.f, 50.f};
    healthCircle.setPosition(healthCirclePosition);
    healthCircleBackground.setPosition(healthCirclePosition);
    
    // Positionner la fenêtre de stats au centre si elle est visible
    if (showStatsWindow) {
        // Calculer la position centrale
        float statsWidth = statsBackground.getSize().x;
        float statsHeight = statsBackground.getSize().y;
        sf::Vector2f statsPos{
            (hudSize.x - statsWidth) / 2.f,
            (hudSize.y - statsHeight) / 2.f
        };
        
        statsBackground.setPosition(statsPos);
        
        sf::Vector2f expBarPos = statsPos;
        expBarPos.x += 10.f;
        expBarPos.y += 360.f;
        expBarBackground.setPosition(expBarPos);
        expBarFill.setPosition(expBarPos);
        
        // Positionner les textes avec un espacement fixe
        float baseY = statsPos.y + 20.f;
        float spacing = 30.f;
        
        sf::Vector2f textPos = {statsPos.x + 10.f, statsPos.y};
        statsText->setPosition(textPos);
        
        textPos.y = baseY;
        levelText->setPosition(textPos);
        
        textPos.y = baseY + spacing;
        expText->setPosition(textPos);
        
        textPos.y = baseY + spacing * 2;
        healthText->setPosition(textPos);
        
        textPos.y = baseY + spacing * 3;
        attackText->setPosition(textPos);
        
        textPos.y = baseY + spacing * 4;
        defenseText->setPosition(textPos);
        
        if (playerStatsSprite) {
            sf::Vector2f spritePos = {statsPos.x + 150.f, statsPos.y + 200.f};
            playerStatsSprite->setPosition(spritePos);
        }
    }
}

void InterfaceSystem::update(Life* lifeComponent, float deltaTime) {
    if (!lifeComponent) return;

    // Mettre à jour les positions de l'interface
    updateInterfacePositions();

    // Mettre à jour l'animation du sprite du joueur
    updatePlayerAnimation(deltaTime);

    // Mettre à jour l'indicateur de vie
    float healthPercent = static_cast<float>(lifeComponent->getCurrentHealth()) / lifeComponent->getMaxHealth();
    healthCircle.setScale({1.f, healthPercent});

    if (showStatsWindow) {
        // Mettre à jour les textes
        std::stringstream ss;
        
        ss << "Statistiques du joueur";
        statsText->setString(ss.str());
        ss.str("");
        
        ss << "Niveau: " << lifeComponent->getLevel();
        levelText->setString(ss.str());
        ss.str("");
        
        ss << "Exp: " << lifeComponent->getExperience() << "/" << lifeComponent->getExperienceToNextLevel();
        expText->setString(ss.str());
        ss.str("");
        
        ss << "HP: " << lifeComponent->getCurrentHealth() << "/" << lifeComponent->getMaxHealth();
        healthText->setString(ss.str());
        ss.str("");
        
        ss << "Att: " << lifeComponent->getAttack();
        attackText->setString(ss.str());
        ss.str("");
        
        ss << "Def: " << lifeComponent->getDefense();
        defenseText->setString(ss.str());

        // Mettre à jour la barre d'expérience
        float expPercent = static_cast<float>(lifeComponent->getExperience()) / lifeComponent->getExperienceToNextLevel();
        expBarFill.setSize(sf::Vector2f(expBarBackground.getSize().x * expPercent, expBarBackground.getSize().y));
    }
}

void InterfaceSystem::draw(sf::RenderWindow& window) {
    if (!gameView) return;

    // Sauvegarder la vue actuelle
    sf::View currentView = window.getView();

    // Créer une vue fixe pour l'interface
    hudView = window.getDefaultView();
    window.setView(hudView);

    // Dessiner l'indicateur de vie
    window.draw(healthCircleBackground);
    window.draw(healthCircle);

    if (showStatsWindow) {
        window.draw(statsBackground);
        window.draw(expBarBackground);
        window.draw(expBarFill);
        window.draw(*statsText);
        window.draw(*levelText);
        window.draw(*expText);
        window.draw(*healthText);
        window.draw(*attackText);
        window.draw(*defenseText);
        
        if (playerStatsSprite) {
            window.draw(*playerStatsSprite);
        }
    }

    // Restaurer la vue du jeu
    window.setView(currentView);
}

void InterfaceSystem::setPlayerStatsTexture(const sf::Texture& texture) {
    playerStatsTexture = texture;
    if (playerStatsSprite == nullptr) {
        playerStatsSprite = new sf::Sprite(playerStatsTexture);
        playerStatsSprite->setPosition({550, 150});
        playerStatsSprite->setScale({2.0f, 2.0f});
    } else {
        playerStatsSprite->setTexture(playerStatsTexture);
    }
}

void InterfaceSystem::updatePlayerAnimation(float deltaTime) {
    if (!idleFrames.empty() && playerStatsSprite) {
        frameTimer += deltaTime;
        if (frameTimer >= frameDuration) {
            frameTimer = 0.0f;
            currentFrame = (currentFrame + 1) % idleFrames.size();
            playerStatsSprite->setTextureRect(idleFrames[currentFrame]);
        }
    }
}

void InterfaceSystem::toggleStatsWindow() {
    showStatsWindow = !showStatsWindow;
}