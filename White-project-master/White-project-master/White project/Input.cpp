#include "Input.h"

Input::Input(const sf::Event & event) : event(event) {}

bool Input::isKeyPressed(sf::Keyboard::Key key) const {
    return event.type == sf::Event::KeyPressed && event.key.code == key;
}