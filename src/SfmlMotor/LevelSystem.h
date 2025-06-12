#pragma once
#include "System.h"
#include "Entity.h"
#include "Transform.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "ECS_Manager.h"
#include <vector>
#include <string>

struct PlatformData {
    float x;
    float y;
    float width;
    float height;
    std::string type;
    std::string texturePath;
};

class LevelSystem : public System {
public:
    LevelSystem(ECS_Manager* manager);
    virtual ~LevelSystem() = default;

    void start() override;
    void update() override;

    void loadLevel(const std::vector<PlatformData>& platforms);
    void clearLevel();

private:
    std::vector<Entity*> levelEntities;
    ECS_Manager* ecsManager;
    void createPlatform(const PlatformData& data);
}; 