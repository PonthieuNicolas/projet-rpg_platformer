#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class ColliderComponent : public Component {
private:
    sf::FloatRect boundingBox;

public:
    sf::Vector2f position;
    sf::Vector2f size;

    ColliderComponent();
    ColliderComponent(float x, float y, float width, float height);
    virtual ~ColliderComponent() = default;

    virtual std::string GetComponentName() const override;

    void setPosition(float x, float y);
    void updateFromSprite(const sf::Sprite& sprite);

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    void setSize(float width, float height);

    void setBoundingBox(const sf::FloatRect& rect);
    const sf::FloatRect& getBoundingBox() const;

    bool isCollidingWith(const ColliderComponent& other) const;

private:
    bool aabbIntersects(const sf::FloatRect& a, const sf::FloatRect& b) const;
};
