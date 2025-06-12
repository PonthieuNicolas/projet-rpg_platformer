#include "pch.h"
#include "StateMachineComponent.h"

StateMachineComponent::StateMachineComponent() = default;

StateMachineComponent::~StateMachineComponent() = default;

std::string StateMachineComponent::GetComponentName() const {
    return "StateMachineComponent";
}

void StateMachineComponent::initialize(Entity* entity, ECS_Manager* ecsManager, const std::string& initialStateName) {
    stateMachine = std::make_unique<StateMachine>(entity, ecsManager, initialStateName);
}

void StateMachineComponent::setInitialState(const std::string& stateName) {
    if (stateMachine) {
        stateMachine->setInitialState(stateName);
    }
}

void StateMachineComponent::start() {
    if (stateMachine) {
        stateMachine->initialize();
    }
}

void StateMachineComponent::update(float deltaTime) {
    if (stateMachine) {
        stateMachine->update(deltaTime);
    }
}

void StateMachineComponent::handleEvent(const sf::Event& event) {
    if (stateMachine) {
        stateMachine->handleEvent(event);
    }
}

void StateMachineComponent::changeState(const std::string& stateName) {
    if (stateMachine) {
        stateMachine->changeState(stateName);
    }
}

std::shared_ptr<State> StateMachineComponent::getCurrentState() const {
    return stateMachine ? stateMachine->getCurrentState() : nullptr;
}

std::string StateMachineComponent::getCurrentStateName() const {
    return stateMachine ? stateMachine->getCurrentStateName() : "";
}

StateMachine* StateMachineComponent::getStateMachine() const {
    return stateMachine.get();
}
