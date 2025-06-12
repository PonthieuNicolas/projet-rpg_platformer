#include "pch.h"
#include "ColliderComponent.h"

ColliderComponent::ColliderComponent()
    : boundingBox({ {0.f, 0.f}, {0.f, 0.f} }) {
    position = sf::Vector2f(0, 0);
    size = sf::Vector2f(0, 0);
}

ColliderComponent::ColliderComponent(float x, float y, float width, float height)
    : boundingBox({ {x, y}, {width, height} }) {
    position = sf::Vector2f(x, y);
    size = sf::Vector2f(width, height);
}

std::string ColliderComponent::GetComponentName() const {
    return "ColliderComponent";
}

void ColliderComponent::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    boundingBox.position = sf::Vector2f(x, y);
}

void ColliderComponent::updateFromSprite(const sf::Sprite& sprite) {
    boundingBox = sprite.getGlobalBounds();
    position = boundingBox.position;
    size = boundingBox.size;
}

sf::Vector2f ColliderComponent::getPosition() const {
    return position;
}

sf::Vector2f ColliderComponent::getSize() const {
    return size;
}

void ColliderComponent::setSize(float width, float height) {
    size = sf::Vector2f(width, height);
    boundingBox.size = sf::Vector2f(width, height);
}

void ColliderComponent::setBoundingBox(const sf::FloatRect& rect) {
    boundingBox = rect;
    position = rect.position;
    size = rect.size;
}

const sf::FloatRect& ColliderComponent::getBoundingBox() const {
    return boundingBox;
}

bool ColliderComponent::isCollidingWith(const ColliderComponent& other) const {
    return aabbIntersects(boundingBox, other.boundingBox);
}

bool ColliderComponent::aabbIntersects(const sf::FloatRect& a, const sf::FloatRect& b) const {
    return (a.position.x < b.position.x + b.size.x &&
            a.position.x + a.size.x > b.position.x &&
            a.position.y < b.position.y + b.size.y &&
            a.position.y + a.size.y > b.position.y);
}

