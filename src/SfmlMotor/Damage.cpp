#include "pch.h"
#include "Damage.h"

Damage::Damage(int value) : value(value) {}

void Damage::SetValue(int v) {
    value = v;
}

int Damage::GetValue() const {
    return value;
}

std::string Damage::GetComponentName() const {
    return "Damage";
}
