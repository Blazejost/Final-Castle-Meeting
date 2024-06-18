#pragma once

#include <SFML/Window/Event.hpp>

class Input {
public:
    Input(const sf::Event& event);

    bool isKeyPressed(sf::Keyboard::Key key) const;

private:
    sf::Event event;
};