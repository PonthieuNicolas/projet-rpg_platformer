#include "pch.h"
#include "StateMachine.h"
#include "State.h"
#include "ECS_Manager.h"

StateMachine::StateMachine(Entity* entity, ECS_Manager* ecsManager, const std::string& initialStateName)
    : entity(entity), ecsManager(ecsManager), initialStateName(initialStateName)
{
}

StateMachine::~StateMachine() = default;

void StateMachine::setInitialState(const std::string& stateName) {
    if (states.find(stateName) != states.end()) {
        initialStateName = stateName;
    }
}

void StateMachine::initialize() {
    if (!initialStateName.empty() && states.find(initialStateName) != states.end()) {
        currentState = states[initialStateName];
        currentState->enter();
    }
}

void StateMachine::update(float deltaTime) {
    if (currentState) {
        currentState->update(deltaTime);
        for (const auto& pair : states) {
            if (pair.first != currentState->getName() &&
                currentState->shouldTransitionTo(pair.first)) {
                changeState(pair.first);
                break;
            }
        }
    }
}

void StateMachine::handleEvent(const sf::Event& event) {
    if (currentState) {
        currentState->handleEvent(event);
    }
}

void StateMachine::changeState(const std::string& stateName) {
    if (states.find(stateName) != states.end()) {
        if (currentState) {
            currentState->exit();
        }
        currentState = states[stateName];
        currentState->enter();
    }
}

std::shared_ptr<State> StateMachine::getCurrentState() const {
    return currentState;
}

std::string StateMachine::getCurrentStateName() const {
    return currentState ? currentState->getName() : "";
}
