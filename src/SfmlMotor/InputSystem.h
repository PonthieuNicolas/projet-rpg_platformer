#pragma once
#include "System.h"
#include <windows.h>

class InputSystem : public System {
public:
    InputSystem() = default;
    virtual ~InputSystem() = default;

    void start() override {
    }

    void update() override {

    }

    bool isKeyPressed(int key);

    POINT getMousePosition();

    bool isMouseButtonPressed(int button);
};