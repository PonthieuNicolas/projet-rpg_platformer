#include "pch.h"
#include "AnimationComponent.h"

int AnimationComponent::instanceCount = 0;

AnimationComponent::AnimationComponent(const std::vector<sf::IntRect>& frames, float timeBetweenFrames)
    : frames(frames), timeBetweenFrames(timeBetweenFrames), elapsedTime(0.0f), currentFrameIndex(0)
{
    instanceId = ++instanceCount;
}

AnimationComponent::~AnimationComponent() {
}

void AnimationComponent::update(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= timeBetweenFrames) {
        int oldFrame = currentFrameIndex;
        currentFrameIndex = (currentFrameIndex + 1) % frames.size();
        elapsedTime = 0.0f;
    }
}

const sf::IntRect& AnimationComponent::getCurrentFrame() const {
    return frames[currentFrameIndex];
}

void AnimationComponent::reset() {
    currentFrameIndex = 0;
    elapsedTime = 0.0f;
}

void AnimationComponent::setFrames(const std::vector<sf::IntRect>& frames) {
    this->frames = frames;
    currentFrameIndex = 0;
}

void AnimationComponent::setCurrentAnimationIndex(int index) {
    if (index >= 0 && index < frames.size()) {
        currentFrameIndex = index;
        elapsedTime = 0;
    }
}

std::string AnimationComponent::GetComponentName() const {
    return "AnimationComponent";
}

