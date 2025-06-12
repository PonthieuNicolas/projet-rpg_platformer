#pragma once

#include "State.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <SFML/Window/Event.hpp>

class Entity;
class ECS_Manager;

class StateMachine {
private:
    Entity* entity;
    ECS_Manager* ecsManager;
    std::unordered_map<std::string, std::shared_ptr<State>> states;
    std::shared_ptr<State> currentState;
    std::string initialStateName;

public:
    StateMachine(Entity* entity, ECS_Manager* ecsManager, const std::string& initialStateName = "");
    ~StateMachine();

    // Ajouter un état à la machine (méthode template, définie directement dans le header)
    template<typename T>
    void addState(const std::string& stateName) {
        static_assert(std::is_base_of<State, T>::value, "T must inherit from State");
        states[stateName] = std::make_shared<T>(entity, ecsManager);
    }

    void setInitialState(const std::string& stateName);

    void initialize();

    void update(float deltaTime);

    void handleEvent(const sf::Event& event);

    void changeState(const std::string& stateName);

    std::shared_ptr<State> getCurrentState() const;

    std::string getCurrentStateName() const;
};
