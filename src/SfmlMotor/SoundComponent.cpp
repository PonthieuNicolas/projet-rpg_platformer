#include "pch.h"
#include "SoundComponent.h"

SoundComponent::SoundComponent(const sf::SoundBuffer& buffer)
    : sound(buffer)
{
}

std::string SoundComponent::GetComponentName() const {
    return "SoundComponent";
}

void SoundComponent::play() {
    sound.play();
}

void SoundComponent::pause() {
    sound.pause();
}

void SoundComponent::stop() {
    sound.stop();
}

void SoundComponent::setLoop(bool loop)
{
    sound.setLooping(loop);
}

bool SoundComponent::isPlaying() const {
    return sound.getStatus() == sf::Sound::Status::Playing;
}