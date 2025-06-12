#pragma once
#include "ECS_Manager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>

struct PlatformData {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
    std::string texturePath;
};

struct EnemyData {
    sf::Vector2f position;
    std::string type;
};

class LevelSystem {
public:
    LevelSystem(ECS_Manager* manager);
    ~LevelSystem();

    void loadLevel(int levelNumber);
    void clearLevel();
    void update();
    void draw(sf::RenderWindow& window, bool showColliders = false);

    void addPlatform(const sf::Vector2f& position, 
                    const sf::Vector2f& size, 
                    const std::string& texturePath = "",
                    const sf::Color& color = sf::Color(100, 100, 100));
    void addEnemy(const sf::Vector2f& position, const std::string& type);

    const std::vector<Entity*>& getPlatforms() const { return platforms; }
    const std::vector<Entity*>& getEnemies() const { return enemies; }

private:
    ECS_Manager* ecsManager;
    std::vector<Entity*> platforms;
    std::vector<Entity*> enemies;
    std::vector<PlatformData> platformsData;
    std::vector<EnemyData> enemiesData;
    sf::Texture slimeTexture;
    std::unordered_map<std::string, sf::Texture> platformTextures;

    void createPlatform(const PlatformData& data);
    void createEnemy(const EnemyData& data);
}; 