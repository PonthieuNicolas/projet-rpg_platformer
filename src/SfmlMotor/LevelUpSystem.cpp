#include "pch.h"
#include "LevelUpSystem.h"

LevelUpSystem::LevelUpSystem() {}

LevelUpSystem::~LevelUpSystem() {}

void LevelUpSystem::start() {
    std::cout << "LevelUpSystem demarre." << std::endl;
    for (auto entity : entities) {
        levels[entity->getId()] = 1;
    }
}

void LevelUpSystem::update() {
    for (auto entity : entities) {
        size_t id = entity->getId();

        Experience* exp = dynamic_cast<Experience*>(entity);
        if (exp) {
            if (levels.find(id) == levels.end()) {
                levels[id] = 1;
            }
            int currentLevel = levels[id];
            int threshold = calculateThreshold(currentLevel);
            int currentXP = exp->GetValue();

            while (currentXP >= threshold) {
                currentXP -= threshold;
                currentLevel++;
                std::cout << "Entity " << id << " a monte au niveau " << currentLevel << " !" << std::endl;
                threshold = calculateThreshold(currentLevel);
            }
            levels[id] = currentLevel;
            exp->SetValue(currentXP);
        }
    }
}

