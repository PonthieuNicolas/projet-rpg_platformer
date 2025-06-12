#pragma once

#include "Component.h"
#include <string>
#include <iostream>

class Stats : public Component {
protected:
    int level;
    int experience;
    int experienceToNextLevel;
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;

public:
    Stats();
    virtual ~Stats() = default;

    virtual void takeDamage(int damage) = 0;

    int getLevel() const;
    int getExperience() const;
    int getExperienceToNextLevel() const;
    int getMaxHealth() const;
    int getCurrentHealth() const;
    int getAttack() const;
    int getDefense() const;

    void addExperience(int exp);
    void checkLevelUp();
    void levelUp();
    int calculateNextLevelExperience() const;

    virtual std::string GetComponentName() const override;
};
