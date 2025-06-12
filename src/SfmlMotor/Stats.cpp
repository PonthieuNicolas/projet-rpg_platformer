#include "pch.h"
#include "Stats.h"
#include <iostream>

Stats::Stats()
    : level(1),
    experience(0),
    experienceToNextLevel(100),
    maxHealth(100),
    currentHealth(100),
    attack(10),
    defense(5)
{
}

int Stats::getLevel() const {
    return level;
}

int Stats::getExperience() const {
    return experience;
}

int Stats::getExperienceToNextLevel() const {
    return experienceToNextLevel;
}

int Stats::getMaxHealth() const {
    return maxHealth;
}

int Stats::getCurrentHealth() const {
    return currentHealth;
}

int Stats::getAttack() const {
    return attack;
}

int Stats::getDefense() const {
    return defense;
}

void Stats::addExperience(int exp) {
    experience += exp;
    checkLevelUp();
}

void Stats::checkLevelUp() {
    while (experience >= experienceToNextLevel) {
        levelUp();
    }
}

void Stats::levelUp() {
    level++;
    experience -= experienceToNextLevel;
    experienceToNextLevel = calculateNextLevelExperience();

    // Am�lioration des statistiques
    maxHealth += 10;
    currentHealth = maxHealth;
    attack += 2;
    defense += 1;

    // Notification de niveau sup�rieur
    std::cout << "Niveau sup�rieur! Niveau " << level << " atteint!" << std::endl;
    std::cout << "Sant�: " << currentHealth << "/" << maxHealth << std::endl;
    std::cout << "Attaque: " << attack << std::endl;
    std::cout << "D�fense: " << defense << std::endl;
}

int Stats::calculateNextLevelExperience() const {
    return 100 + (level * 50);
}

std::string Stats::GetComponentName() const {
    return "Stats";
}
