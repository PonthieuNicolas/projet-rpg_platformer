template<typename T, typename... Args>
T* ECS_Manager::addComponent(Entity* entity, Args&&... args) {
    if (!entity) return nullptr;

    T* component = new T(std::forward<Args>(args)...);
    component->SetEntityId(static_cast<int>(entity->getId()));

    entityComponents[entity->getId()][std::type_index(typeid(T))] = component;
    return component;
}

template<typename T>
T* ECS_Manager::addSystem() {
    static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from ISystem");
    T* system = new T();
    system->setECSManager(this);  // On configure l'ECS_Manager
    m_systems.push_back(system);
    system->start();  // On appelle start() lors de l'ajout
    return system;
}

template<typename T>
T* ECS_Manager::addScript(Entity* entity) {
    static_assert(std::is_base_of<IScript, T>::value, "T must inherit from IScript");

    if (!entity) return nullptr;

    T* script = new T();
    script->setEntity(entity);
    script->setECSManager(this);  // On passe l'ECS_Manager au script
    entityScripts[entity->getId()].push_back(script);
    script->start();
    return script;
}

template<typename T>
T* ECS_Manager::getComponent(Entity* entity) {
    if (!entity) return nullptr;

    auto entityFind = entityComponents.find(static_cast<int>(entity->getId()));
    if (entityFind != entityComponents.end()) {
        auto componentFind = entityFind->second.find(std::type_index(typeid(T)));
        if (componentFind != entityFind->second.end()) {
            return static_cast<T*>(componentFind->second);
        }
    }
    return nullptr;
}

template<typename T>
T* ECS_Manager::getSystem() {
    static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from ISystem");

    for (auto* system : m_systems) {
        if (T* castedSystem = dynamic_cast<T*>(system)) {
            return castedSystem;
        }
    }
    return nullptr;
}

template<typename T>
T* ECS_Manager::getScript(Entity* entity) {
    if (!entity) return nullptr;

    auto it = entityScripts.find(entity->getId());
    if (it != entityScripts.end()) {
        for (auto* script : it->second) {
            if (T* castedScript = dynamic_cast<T*>(script)) {
                return castedScript;
            }
        }
    }
    return nullptr;
}

template<typename T>
bool ECS_Manager::removeComponent(Entity* entity) {
    if (!entity) return false;

    auto entityFind = entityComponents.find(static_cast<int>(entity->getId()));
    if (entityFind != entityComponents.end()) {
        auto componentFind = entityFind->second.find(std::type_index(typeid(T)));
        if (componentFind != entityFind->second.end()) {
            delete componentFind->second;
            entityFind->second.erase(componentFind);
            return true;
        }
    }
    return false;
}

template<typename T>
bool ECS_Manager::removeSystem() {
    static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from ISystem");

    for (auto it = m_systems.begin(); it != m_systems.end(); ++it) {
        if (T* castedSystem = dynamic_cast<T*>(*it)) {
            delete* it;  // Libére la mémoire
            m_systems.erase(it);  // Retire du vector
            return true;
        }
    }
    return false;
}

template<typename T>
bool ECS_Manager::removeScript(Entity* entity) {
    if (!entity) return false;

    auto it = entityScripts.find(static_cast<int>(entity->getId()));
    if (it != entityScripts.end()) {
        auto& scripts = it->second;
        for (auto scriptIt = scripts.begin(); scriptIt != scripts.end(); ++scriptIt) {
            if (dynamic_cast<T*>(*scriptIt)) {
                delete* scriptIt;
                scripts.erase(scriptIt);
                return true;
            }
        }
    }
    return false;
}