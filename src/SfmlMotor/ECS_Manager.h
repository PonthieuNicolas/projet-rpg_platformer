// ECS_Manager.h
#pragma once
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "Entity.h"
#include "Component.h"
#include "SystemInterface.h"
#include "ScriptInterface.h"
#include "EventSystem.h"
#include "DestroyComponent.h"

class ECS_Manager {
private:
    std::vector<Entity*> entities;
    std::vector<ISystem*> m_systems;
    std::unordered_map<int, std::unordered_map<std::type_index, Component*>> entityComponents;
    std::unordered_map<int, std::vector<IScript*>> entityScripts;
    size_t nextEntityId;
    EventSystem* eventSystem;

public:
    ECS_Manager();
    ~ECS_Manager();

    EventSystem* getEventSystem();
    Entity* createEntity(const std::string& name);
    const std::vector<Entity*>& getAllEntities() const;
    bool destroyEntity(Entity* entity);

    template<typename T, typename... Args>
    T* addComponent(Entity* entity, Args&&... args);

    template<typename T>
    T* addSystem();

    template<typename T>
    T* addScript(Entity* entity);

    template<typename T>
    T* getComponent(Entity* entity);

    template<typename T>
    T* getSystem();

    template<typename T>
    T* getScript(Entity* entity);

    template<typename T>
    bool removeComponent(Entity* entity);

    template<typename T>
    bool removeSystem();

    template<typename T>
    bool removeScript(Entity* entity);

    void update();
};

#include "ECS_Manager.inl"