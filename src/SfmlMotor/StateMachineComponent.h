#pragma once

#include "Component.h"
#include "StateMachine.h"
#include <memory>
#include <SFML/Window/Event.hpp>

class StateMachineComponent : public Component {
private:
    std::unique_ptr<StateMachine> stateMachine;

public:
    StateMachineComponent();
    virtual ~StateMachineComponent();

    virtual std::string GetComponentName() const override;

    void initialize(Entity* entity, ECS_Manager* ecsManager, const std::string& initialStateName = "");

    template<typename T>
    void addState(const std::string& stateName) {
        if (stateMachine) {
            stateMachine->addState<T>(stateName);
        }
    }

    void setInitialState(const std::string& stateName);

    void start();
    void update(float deltaTime);
    void handleEvent(const sf::Event& event);
    void changeState(const std::string& stateName);

    std::shared_ptr<State> getCurrentState() const;
    std::string getCurrentStateName() const;

    StateMachine* getStateMachine() const;
};
