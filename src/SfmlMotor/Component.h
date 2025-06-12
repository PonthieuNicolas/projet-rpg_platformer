#pragma once
#include <string>

class Component {
protected:
    int entityId;
public:
    Component();
    virtual ~Component() = default;
    void SetEntityId(int id);
    int GetEntityId() const;
    virtual std::string GetComponentName() const = 0;
};