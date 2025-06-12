#pragma once
#include "Component.h"
#include <string>

class GUIComponent : public Component {
public:
    GUIComponent() = default;
    virtual ~GUIComponent() = default;

    virtual std::string GetComponentName() const override {
        return "GUIComponent";
    }

    virtual void render() = 0;
};
