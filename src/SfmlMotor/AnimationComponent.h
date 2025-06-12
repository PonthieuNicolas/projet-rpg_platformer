#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Component.h"

class AnimationComponent : public Component {
private:
    std::vector<sf::IntRect> frames;
    float timeBetweenFrames;
    float elapsedTime;
    int currentFrameIndex;
    static int instanceCount;
    int instanceId;

public:
    AnimationComponent(const std::vector<sf::IntRect>& frames, float timeBetweenFrames = 0.1f);
    ~AnimationComponent();

    void update(float deltaTime);
    const sf::IntRect& getCurrentFrame() const;
    void reset();
    void setFrames(const std::vector<sf::IntRect>& newFrames);
    void setCurrentAnimationIndex(int index);

    virtual std::string GetComponentName() const override;
};
