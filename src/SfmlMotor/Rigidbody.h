#pragma once
#include "Component.h"
#include <string>

struct Vector2 {
    float x;
    float y;
};

class RigidBody : public Component {
private:
    Vector2 position;
    Vector2 velocity;
    float mass;

public:
    RigidBody();
    virtual ~RigidBody() = default;

    void setPosition(const Vector2& pos);
    Vector2 getPosition() const;

    void setVelocity(const Vector2& vel);
    Vector2 getVelocity() const;

    void setMass(float mass);
    float getMass() const;

    float GetX() const;
    float GetY() const;
    void SetX(float x);
    void SetY(float y);

    Vector2 operator-(const Vector2& _right) const;
    Vector2 operator+(const Vector2& _right) const;

    std::string GetComponentName() const override;
};
