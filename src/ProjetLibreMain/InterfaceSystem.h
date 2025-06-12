#pragma once
#include <SFML/Graphics.hpp>
#include "Life.h"
#include "PlayerScript.h"

class InterfaceSystem {
private:
    // Fenêtre de statistiques
    bool showStatsWindow;
    sf::RectangleShape statsBackground;
    sf::RectangleShape expBarBackground;
    sf::RectangleShape expBarFill;
    sf::Text* statsText;
    sf::Text* levelText;
    sf::Text* expText;
    sf::Text* healthText;
    sf::Text* attackText;
    sf::Text* defenseText;
    sf::Sprite* playerStatsSprite;
    sf::Texture playerStatsTexture;
    const sf::Font& font;

    // Indicateur de vie circulaire
    sf::CircleShape healthCircle;
    sf::CircleShape healthCircleBackground;
    float healthCircleRadius;
    sf::Vector2f healthCirclePosition;

    // Animation du sprite du joueur
    std::vector<sf::IntRect> idleFrames;
    int currentFrame;
    float frameTimer;
    float frameDuration;

    // Vue de la caméra
    const sf::View* gameView;
    sf::View hudView;

    // Méthodes d'initialisation privées
    void initStatsWindow();
    void initHealthCircle();
    void updatePlayerAnimation(float deltaTime);
    void updateInterfacePositions();

public:
    InterfaceSystem(const sf::Font& font);
    ~InterfaceSystem();

    void init();
    void update(Life* playerLife, float deltaTime);
    void draw(sf::RenderWindow& window);
    void toggleStatsWindow();
    bool isStatsWindowVisible() const { return showStatsWindow; }
    void setPlayerStatsSprite(sf::Sprite* sprite) { playerStatsSprite = sprite; }
    void setPlayerStatsTexture(const sf::Texture& texture);
    void setPlayerIdleFrames(const std::vector<sf::IntRect>& frames) { idleFrames = frames; }
    void setGameView(const sf::View* view) { gameView = view; }
}; 