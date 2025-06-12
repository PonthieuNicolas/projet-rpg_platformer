#pragma once
#include "BasicProjectileScript.h"

class HomingProjectileScript : public BasicProjectileScript {
public:
    HomingProjectileScript();

    void start() override;
    void update() override;
    void update(float deltaTime) override;

    void setTarget(Entity* target);

protected:
    Entity* targetEntity;
    float homingStrength;
};
