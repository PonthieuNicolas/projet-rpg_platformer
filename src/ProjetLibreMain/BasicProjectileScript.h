#pragma once
#include "Script.h"
#include "Projectile.h"
#include "Life.h"
#include <iostream>

class BasicProjectileScript : public Script, public Projectile {
public:
    bool toBeDestroyed = false;
    BasicProjectileScript();
    virtual ~BasicProjectileScript() = default;

    void start() override;
    void update() override;

    void onCollision(Entity* other) override;
    void update(float deltaTime) override;

protected:
    float mElapsedTime = 0.f;
    const float mLifeTime = 12.f;
};
