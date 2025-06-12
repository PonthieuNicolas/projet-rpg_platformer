#pragma once
#include "GUI.h"
#include <string>
#include <iostream>

class Dialogue : public GUIComponent {
private:
    std::string message;
public:
    Dialogue(const std::string& msg) : message(msg) {}
    virtual ~Dialogue() = default;

    void setMessage(const std::string& msg) { message = msg; }
    std::string getMessage() const { return message; }

    virtual std::string GetComponentName() const override {
        return "Dialogue";
    }

    virtual void render() override {
        std::cout << "Dialogue: " << message << std::endl;
    }
};
