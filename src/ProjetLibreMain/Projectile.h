#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Projectile {
protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f size;
    float damage;
    bool active;

public:
    Projectile();

    Projectile(const sf::Vector2f& position,
        const sf::Vector2f& velocity,
        float damage,
        const sf::Vector2f& size = sf::Vector2f(10.f, 10.f));

    virtual ~Projectile() = default;

    virtual void update(float deltaTime) = 0;

    virtual void onCollision(Entity* other) = 0;

    virtual void move(float deltaTime);

    virtual sf::FloatRect getBounds() const;

    virtual void setActive(bool isActive);
    virtual bool isActive() const;

    virtual void setVelocity(const sf::Vector2f& newVelocity);
    virtual sf::Vector2f getVelocity() const;

    virtual float getDamage() const;

    virtual void setPosition(const sf::Vector2f& newPosition);
    virtual sf::Vector2f getPosition() const;

    virtual void setSize(const sf::Vector2f& newSize);
    virtual sf::Vector2f getSize() const;
};
