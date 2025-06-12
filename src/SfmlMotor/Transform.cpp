#include "pch.h"
#include "Transform.h"

Transform::Transform()
    : Component(), position(0.f, 0.f), scale(1.f, 1.f), rotation(0.f) {
}

void Transform::Identity() {
    position = { 0.f, 0.f };
    scale = { 1.f, 1.f };
    rotation = 0.f;
}

void Transform::Rotate(float angle) {
    rotation += angle;
}
