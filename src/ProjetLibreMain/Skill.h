#ifndef SKILL_H
#define SKILL_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <optional>

class Skill {
public:
    Skill(const std::string& name, const sf::Vector2f& position);
    ~Skill() = default;

    bool isUnlocked() const;
    void unlock();

    void draw(sf::RenderWindow& window) const;
    void handleEvent(const std::optional<sf::Event>& eventOpt, sf::RenderWindow& window);

    std::function<void()> onUnlock;

private:
    void initializeBackground();

    std::string name;
    bool unlocked;
    sf::RectangleShape background;
    sf::Vector2f position;
};

#endif
