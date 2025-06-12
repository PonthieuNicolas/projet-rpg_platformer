#include "pch.h"
#include "Skill.h"
#include <iostream>

Skill::Skill(const std::string& name, const sf::Vector2f& pos)
    : name(name), unlocked(false), position(pos)
{
    initializeBackground();
}

void Skill::initializeBackground() {
    background.setSize(sf::Vector2f(64.f, 64.f));
    background.setFillColor(sf::Color(50, 50, 50, 200));  // Fond semi-transparent.
    background.setOutlineThickness(2.f);
    background.setOutlineColor(sf::Color::White);
    background.setPosition(position);
}

bool Skill::isUnlocked() const {
    return unlocked;
}

void Skill::unlock() {
    if (!unlocked) {
        unlocked = true;
        std::cout << "Skill " << name << " unlocked !" << std::endl;
        if (onUnlock)
            onUnlock();
    }
}

void Skill::draw(sf::RenderWindow& window) const {
    window.draw(background);
}

void Skill::handleEvent(const std::optional<sf::Event>& eventOpt, sf::RenderWindow& window) {
    if (!unlocked && eventOpt) {
        if (const auto* mouseEvent = eventOpt->getIf<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (background.getGlobalBounds().contains(mousePos)) {
                unlock();
            }
        }
    }
}

