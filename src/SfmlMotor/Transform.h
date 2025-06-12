#pragma once
#include "Component.h"
#include <SFML/System/Vector2.hpp>
#include "Component.h"

class Transform : public Component {
public:
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;

    Transform();
    ~Transform() = default;

    void Identity();
    void Rotate(float angle);

    inline sf::Vector2f getPosition() const { return position; }
    inline void setPosition(const sf::Vector2f& pos) { position = pos; }
    inline void setPosition(float x, float y) { position = { x, y }; }
    
    virtual std::string GetComponentName() const override {
        return "Transform";
    }
};
