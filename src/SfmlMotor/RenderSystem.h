#pragma once
#include <SFML/Graphics.hpp>
#include "SystemInterface.h"
#include "ECS_Manager.h"

class RenderSystem : public ISystem {
private:
    ECS_Manager* ecsManager;
    sf::RenderWindow* window;

public:
    RenderSystem(ECS_Manager* manager, sf::RenderWindow* win) 
        : ecsManager(manager), window(win) {}

    virtual ~RenderSystem() = default;

    virtual void setECSManager(ECS_Manager* manager) override {
        ecsManager = manager;
    }

    virtual void start() override {
    }

    virtual void update() override {
    }

    virtual void addEntity(Entity* entity) override {
    }
};

