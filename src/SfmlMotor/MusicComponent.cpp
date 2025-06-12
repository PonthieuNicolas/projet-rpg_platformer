#include "pch.h"
#include "MusicComponent.h"

MusicComponent::MusicComponent(const std::string& filepath)
{
    if (!music.openFromFile(filepath)) {
        std::cerr << "Erreur: Impossible de charger le fichier musique: " << filepath << std::endl;
    }
}

void MusicComponent::play() {
    music.play();
}

void MusicComponent::pause() {
    music.pause();
}

void MusicComponent::stop() {
    music.stop();
}

void MusicComponent::setLoop(bool loop) {
    music.setLooping(loop);
}

bool MusicComponent::isPlaying() const {
    return music.getStatus() == sf::SoundSource::Status::Playing;
}
