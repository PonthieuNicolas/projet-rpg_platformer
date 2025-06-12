#pragma once
#include <string>

class Entity {
private:
    std::string name;
    size_t id;

public:
    Entity(std::string name, size_t id);
    virtual ~Entity() = default;
    std::string getName() const;
    size_t getId() const;
};