#pragma once
#include "Component.h"
#include <SFML/Audio.hpp>
#include <string>

class SoundComponent : public Component {
public:
    sf::Sound sound;

    SoundComponent(const sf::SoundBuffer& buffer);

    virtual ~SoundComponent() = default;

    virtual std::string GetComponentName() const override;

    void play();
    void pause();
    void stop();
    void setLoop(bool loop);

    bool isPlaying() const;
};
