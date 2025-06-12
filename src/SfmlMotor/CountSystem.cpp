#include "pch.h"
#include "CountSystem.h"

CountSystem::CountSystem(const std::string& mobName)
    : targetMobName(mobName), deathCount(0) {
}

CountSystem::~CountSystem() {}

void CountSystem::start() {
    deathCount = 0;
    std::cout << "CountSystem d�marr� pour le mob '" << targetMobName
        << "'. Nombre initial de morts: " << deathCount << std::endl;
}

void CountSystem::update() {
    std::cout << "Nombre de morts pour '" << targetMobName << "': " << deathCount << std::endl;
}

void CountSystem::registerDeath(Entity* deadEntity) {
    if (deadEntity) {
        if (deadEntity->getName() == targetMobName) {
            ++deathCount;
            std::cout << "Mort enregistr�e pour '" << targetMobName
                << "'. Total actuel: " << deathCount << std::endl;
        }
    }
}

int CountSystem::getDeathCount() const {
    return deathCount;
}


