#pragma once
#include "Entity.h"
#include "ECS_Manager.h"
#include <SFML/Window/Event.hpp>

class State {
protected:
    Entity* entity;
    ECS_Manager* ecsManager;

public:
    State(Entity* entity, ECS_Manager* ecsManager) 
        : entity(entity), ecsManager(ecsManager) {}
    
    virtual ~State() = default;
    
    virtual void enter() = 0;
    virtual void exit() = 0;
    
    virtual void update(float deltaTime) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual bool shouldTransitionTo(const std::string& stateName) = 0;
    
    virtual std::string getName() const = 0;
}; 