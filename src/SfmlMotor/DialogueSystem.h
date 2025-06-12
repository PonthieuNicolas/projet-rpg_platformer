#pragma once
#include "SystemInterface.h"
#include "ECS_Manager.h"
#include "Dialogue.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class DialogueSystem : public ISystem {
private:
    ECS_Manager* ecsManager;
    sf::Font font;

public:
    DialogueSystem(ECS_Manager* manager)
        : ecsManager(manager), font("arial.ttf")
    {
    }

    virtual ~DialogueSystem() = default;

    virtual void setECSManager(ECS_Manager* manager) override {
        ecsManager = manager;
    }

    virtual void start() override {
    }

    virtual void update() override {
    }

    virtual void addEntity(Entity* entity) override {
    }

    void render(sf::RenderWindow& window) {
        const std::vector<Entity*>& entities = ecsManager->getAllEntities();
        for (Entity* entity : entities) {
            Dialogue* dialogue = ecsManager->getComponent<Dialogue>(entity);
            if (dialogue) {
                sf::Text text(font, sf::String(dialogue->getMessage()), 24U);
                text.setFillColor(sf::Color::White);
                text.setPosition(sf::Vector2f(10.f, 10.f));
                window.draw(text);
            }
        }
    }
};
