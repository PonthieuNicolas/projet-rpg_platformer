#include "pch.h"
#include "Rigidbody.h"

RigidBody::RigidBody()
    : position({ 0.0f, 0.0f }), velocity({ 0.0f, 0.0f }), mass(1.0f) {
}

void RigidBody::setPosition(const Vector2& pos) {
    position = pos;
}

Vector2 RigidBody::getPosition() const {
    return position;
}

void RigidBody::setVelocity(const Vector2& vel) {
    velocity = vel;
}

Vector2 RigidBody::getVelocity() const {
    return velocity;
}

void RigidBody::setMass(float m) {
    mass = m;
}

float RigidBody::getMass() const {
    return mass;
}

void RigidBody::SetX(float _x) {
    position.x = _x;
}

void RigidBody::SetY(float _y) {
    position.y = _y;
}

float RigidBody::GetX() const {
    return position.x;
}

float RigidBody::GetY() const {
    return position.y;
}

Vector2 RigidBody::operator-(const Vector2& _right) const {
    return Vector2(position.x - _right.x, position.y - _right.y);
}

Vector2 RigidBody::operator+(const Vector2& _right) const {
    return Vector2(position.x + _right.x, position.y + _right.y);
}

std::string RigidBody::GetComponentName() const {
    return "RigidBody";
}

