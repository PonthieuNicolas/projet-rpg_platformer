#include "pch.h"
#include "Projectile.h"

Projectile::Projectile()
    : position(0.f, 0.f)
    , velocity(0.f, 0.f)
    , size(10.f, 10.f)
    , damage(0.f)
    , active(true)
{
}

Projectile::Projectile(const sf::Vector2f& position,
    const sf::Vector2f& velocity,
    float damage,
    const sf::Vector2f& size)
    : position(position)
    , velocity(velocity)
    , size(size)
    , damage(damage)
    , active(true)
{
}

void Projectile::move(float deltaTime) {
    position += velocity * deltaTime;
}

sf::FloatRect Projectile::getBounds() const {
    return sf::FloatRect(position, size);
}

void Projectile::setActive(bool isActive) {
    active = isActive;
}

bool Projectile::isActive() const {
    return active;
}

void Projectile::setVelocity(const sf::Vector2f& newVelocity) {
    velocity = newVelocity;
}

sf::Vector2f Projectile::getVelocity() const {
    return velocity;
}

float Projectile::getDamage() const {
    return damage;
}

void Projectile::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
}

sf::Vector2f Projectile::getPosition() const {
    return position;
}

void Projectile::setSize(const sf::Vector2f& newSize) {
    size = newSize;
}

sf::Vector2f Projectile::getSize() const {
    return size;
}
