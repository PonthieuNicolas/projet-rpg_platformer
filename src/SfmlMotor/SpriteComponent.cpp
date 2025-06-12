#include "pch.h"
#include "SpriteComponent.h"
#include <iostream>

SpriteComponent::SpriteComponent()
    : Component(), animation(nullptr), defaultTexture(), sprite(defaultTexture)
{
    sf::Image image({ 1, 1 }, sf::Color::White);
    defaultTexture.loadFromImage(image);
    sprite.setTexture(defaultTexture);

    std::cout << "SpriteComponent cree" << std::endl;
}

SpriteComponent::~SpriteComponent() {
    std::cout << "SpriteComponent detruit" << std::endl;
}

std::string SpriteComponent::GetComponentName() const {
    return "SpriteComponent";
}

void SpriteComponent::setTexture(const sf::Texture& texture, bool mustChangeRect) {
    currentTexture = texture;
    sprite.setTexture(currentTexture, mustChangeRect);
    std::cout << "Texture appliquee au sprite (taille: " << currentTexture.getSize().x 
              << "x" << currentTexture.getSize().y << ")" << std::endl;
}

void SpriteComponent::setPosition(float x, float y) {
    sprite.setPosition(sf::Vector2f(x, y));
}

void SpriteComponent::setScale(float x, float y) {
    sprite.setScale(sf::Vector2f(x, y));
}

void SpriteComponent::setAnimation(std::shared_ptr<AnimationComponent> newAnimation) {
    animation = newAnimation;
    if (animation) {
        sprite.setTextureRect(animation->getCurrentFrame());
        std::cout << "Animation appliquee au sprite" << std::endl;
    }
}

void SpriteComponent::update(float deltaTime) {
    if (animation) {
        animation->update(deltaTime);
        sprite.setTextureRect(animation->getCurrentFrame());
    }
}

const sf::Sprite& SpriteComponent::getSprite() const {
    return sprite;
}

sf::Sprite& SpriteComponent::getSprite() {
    return sprite;
}
