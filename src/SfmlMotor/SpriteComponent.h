#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Component.h"
#include "AnimationComponent.h"

class SpriteComponent : public Component {
private:
    sf::Sprite sprite;
    std::shared_ptr<AnimationComponent> animation;
    sf::Texture defaultTexture;
    sf::Texture currentTexture;

public:
    SpriteComponent();
    virtual ~SpriteComponent();

    virtual std::string GetComponentName() const override;

    void setTexture(const sf::Texture& texture, bool mustChangeRect = false);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void setAnimation(std::shared_ptr<AnimationComponent> newAnimation);
    void update(float deltaTime);

    const sf::Sprite& getSprite() const;
    sf::Sprite& getSprite();
};
