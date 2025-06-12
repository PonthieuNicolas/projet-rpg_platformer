#pragma once
#include "Component.h"

class StageComponent : public Component {
public:
    int collisionMapID;
    int decorID;
    int backgroundID;

    virtual std::string GetComponentName() const override {
        return "StageComponent";
    }
};
