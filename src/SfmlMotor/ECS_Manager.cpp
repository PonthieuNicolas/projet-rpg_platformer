#include "pch.h"
#include "ECS_Manager.h"

ECS_Manager::ECS_Manager() : nextEntityId(0) {
    eventSystem = new EventSystem();
}

ECS_Manager::~ECS_Manager() {
    for (auto& pair : entityScripts) {
        for (auto* script : pair.second) {
            if (script) {
                delete script;
                script = nullptr;
            }
        }
        pair.second.clear();
    }
    entityScripts.clear();

    for (auto* system : m_systems) {
        if (system) {
            delete system;
            system = nullptr;
        }
    }
    m_systems.clear();

    for (auto& entityComponent : entityComponents) {
        for (auto& component : entityComponent.second) {
            if (component.second) {
                delete component.second;
                component.second = nullptr;
            }
        }
        entityComponent.second.clear();
    }
    entityComponents.clear();

    for (auto entity : entities) {
        if (entity) {
            delete entity;
            entity = nullptr;
        }
    }
    entities.clear();

    if (eventSystem) {
        delete eventSystem;
        eventSystem = nullptr;
    }
}


EventSystem* ECS_Manager::getEventSystem()
{
    return eventSystem;
}

Entity* ECS_Manager::createEntity(const std::string& name) {
    Entity* entity = new Entity(name, nextEntityId++);
    entities.push_back(entity);
    return entity;
}

const std::vector<Entity*>& ECS_Manager::getAllEntities() const
{
    return entities;
}

bool ECS_Manager::destroyEntity(Entity* entity) {
    if (!entity) return false;
    int id = entity->getId();

    if (entityScripts.find(id) != entityScripts.end()) {
        for (auto* script : entityScripts[id]) {
            if (script) {
                delete script;
                script = nullptr;
            }
        }
        entityScripts.erase(id);
    }

    if (entityComponents.find(id) != entityComponents.end()) {
        for (auto& [type, comp] : entityComponents[id]) {
            if (comp) {
                delete comp;
                comp = nullptr;
            }
        }
        entityComponents.erase(id);
    }

    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        delete* it;
        entities.erase(it);
    }
    return true;
}


void ECS_Manager::update() {
    for (auto& pair : entityScripts) {
        for (auto* script : pair.second) {
            if (script) {
                script->update();
            }
        }
    }
    for (auto* system : m_systems) {
        if (system) {
            system->update();
        }
    }

    std::vector<Entity*> entitiesToRemove;
    for (Entity* entity : entities) {
        auto* destroyComp = getComponent<DestroyComponent>(entity);
        if (destroyComp && destroyComp->isMarked()) {
            entitiesToRemove.push_back(entity);
        }
    }
    for (Entity* entity : entitiesToRemove) {
        destroyEntity(entity);
    }
}
