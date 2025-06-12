#pragma once
#include "System.h"
#include "Experience.h"
#include <unordered_map>
#include <iostream>

class LevelUpSystem : public System {
private:
    std::unordered_map<size_t, int> levels;

    int calculateThreshold(int level) const {
        return level * 100;
    }

public:
    LevelUpSystem();
    virtual ~LevelUpSystem();

    void start() override;

    void update() override;
};
