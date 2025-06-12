#include "pch.h"
#include "InputSystem.h"
#include <SFML/Window/Keyboard.hpp>

bool InputSystem::isKeyPressed(int key)
{
    switch (key) {
    case 'Q': return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    case 'D': return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    case 'Z': return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
    case 'S': return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    default:  return false;
    }
}

POINT InputSystem::getMousePosition()
{
    POINT mousePos;
    GetCursorPos(&mousePos);
    return mousePos;
}

bool InputSystem::isMouseButtonPressed(int button)
{
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
}
