#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

class MusicComponent {
public:
    sf::Music music;

    MusicComponent(const std::string& filepath);

    ~MusicComponent() = default;
    void play();
    void pause();
    void stop();
    void setLoop(bool loop);
    bool isPlaying() const;
};
