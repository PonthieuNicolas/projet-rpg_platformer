#include "pch.h"
#include "Life.h"
#include <algorithm>

Life::Life(int value) : value(value) {
    maxHealth = value;
    currentHealth = value;
}

void Life::SetValue(int v) {
    value = v;
    maxHealth = v;
    currentHealth = v;
}

int Life::GetValue() const {
    return currentHealth;
}

void Life::takeDamage(int damage) {
    int actualDamage = std::max(1, damage - defense);
    currentHealth = std::max(0, currentHealth - actualDamage);
    value = currentHealth;
}

void Life::heal(int amount) {
    currentHealth = std::min(maxHealth, currentHealth + amount);
    value = currentHealth;
}

std::string Life::GetComponentName() const {
    return "Life";
}

