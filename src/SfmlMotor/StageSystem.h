#pragma once
#include "SystemInterface.h"
#include "ECS_Manager.h"
#include "StageComponent.h"
#include <vector>
#include <string>
#include <iostream>

struct Stage {
    int stageNumber;
    std::string name;
    std::string description;
    int collisionMapID;
    int decorID;
    int backgroundID;
};

class StageSystem : public ISystem {
private:
    ECS_Manager* ecsManager;
    std::vector<Stage> stages;
    int currentStageIndex;
    StageComponent* stageComponent = nullptr;

public:
    StageSystem(ECS_Manager* manager)
        : ecsManager(manager), currentStageIndex(-1)
    {
        stages.push_back({ 1, "Stage 1", "Premier niveau", 101, 201, 301 });
        stages.push_back({ 2, "Stage 2", "Deuxième niveau", 102, 202, 302 });
        stages.push_back({ 3, "Stage 3", "Troisième niveau", 103, 203, 303 });
    }

    virtual ~StageSystem() {
        if (stageComponent)
            delete stageComponent;
    }

    void loadStage(int stageIndex) {
        if (stageIndex < 0 || stageIndex >= static_cast<int>(stages.size())) {
            std::cerr << "Erreur: Niveau invalide !" << std::endl;
            return;
        }
        currentStageIndex = stageIndex;
        const Stage& stage = stages[stageIndex];
        std::cout << "Chargement du niveau " << stage.stageNumber << " : " << stage.name << std::endl;
        std::cout << stage.description << std::endl;

        if (!stageComponent) {
            stageComponent = new StageComponent();
        }

        stageComponent->collisionMapID = stage.collisionMapID;
        stageComponent->decorID = stage.decorID;
        stageComponent->backgroundID = stage.backgroundID;
    }

    StageComponent* getStageComponent() const {
        return stageComponent;
    }

    virtual void update() override {}
    virtual void setECSManager(ECS_Manager* manager) override { ecsManager = manager; }
    virtual void start() override {}
    virtual void addEntity(Entity* entity) override {}
};
