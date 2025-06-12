#pragma once

#include "System.h"
#include "StateMachineComponent.h"
#include "TimerSystem.h"
#include <SFML/Window/Event.hpp>

class StateMachineSystem : public System {
private:
    TimerSystem* timer;

public:
    StateMachineSystem();
    virtual ~StateMachineSystem() = default;

    void setTimer(TimerSystem* timer);

    virtual void start() override;
    virtual void update() override;

    void handleEvent(const sf::Event& event);
};
