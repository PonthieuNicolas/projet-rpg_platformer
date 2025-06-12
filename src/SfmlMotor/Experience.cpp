#include "pch.h"
#include "Experience.h"

Experience::Experience(int value) : value(value) {}

void Experience::SetValue(int v) {
    value = v;
}

int Experience::GetValue() const {
    return value;
}

std::string Experience::GetComponentName() const {
    return "Experience";
}

