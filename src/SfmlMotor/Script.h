#pragma once
#include "ScriptInterface.h"
#include "Entity.h"
#include "ECS_Manager.h"

class Script : public IScript {
protected:
    Entity* attachedEntity;
    ECS_Manager* ecsManager;

public:
    Script();
    virtual ~Script() = default;

    void setEntity(Entity* entity) override;
    void setECSManager(ECS_Manager* manager) override;
    Entity* getEntity() const override;

    virtual void start() override = 0;
    virtual void update() override = 0;
};