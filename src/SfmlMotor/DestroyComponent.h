#pragma once
#include "Component.h"
#include <string>

class DestroyComponent : public Component {
private:
    bool markedForDestruction;
public:
    DestroyComponent() : markedForDestruction(false) {}

    void markForDestruction() { markedForDestruction = true; }
    bool isMarked() const { return markedForDestruction; }

    std::string GetComponentName() const override {
        return "DestroyComponent";
    }
};
