#pragma once
#include "System.h"
#include <iostream>
#include <string>

class CountSystem : public System {
private:
    std::string targetMobName;
    int deathCount;

public:

    CountSystem(const std::string& mobName);
    virtual ~CountSystem();

    void start() override;

    void update() override;

    void registerDeath(Entity* deadEntity);

    int getDeathCount() const;
};
