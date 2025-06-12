#pragma once

class Entity;
class ECS_Manager;

class IScript {
public:
    virtual ~IScript() = default;
    virtual void setEntity(Entity* entity) = 0;
    virtual void setECSManager(ECS_Manager* manager) = 0;
    virtual Entity* getEntity() const = 0;
    virtual void start() = 0;
    virtual void update() = 0;
};