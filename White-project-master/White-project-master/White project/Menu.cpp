#include "stdafx.h"
#include "Menu.h"

#include "Input.h"

Menu::Menu(Game* game) : game(game) {
    font.loadFromFile("Fonts/PrincessSofia-Regular.ttf");
    menuText.setFont(font);
    menuText.setCharacterSize(24);
    menuText.setPosition(100, 100);
    selectedItem = 0;
}

Menu::~Menu() {}

void Menu::update() {
    if (game->getInput().isKeyPressed(Keyboard::Up)) {
        selectedItem--;
        if (selectedItem < 0) {
            selectedItem = 2; // wrap around to last item
        }
    }
    if (game->getInput().isKeyPressed(Keyboard::Down)) {
        selectedItem++;
        if (selectedItem > 2) {
            selectedItem = 0; // wrap around to first item
        }
    }
    if (game->getInput().isKeyPressed(Keyboard::Return)) {
        switch (selectedItem) {
        case 0:
            game->setGameMode(GameModes::TRAVEL);
            break;
        case 1:
            game->setGameMode(GameModes::FIGHT);
            break;
        case 2:
            game->setGameMode(GameModes::MENU);
            break;
        }
    }
}

void Menu::render() {
    game->getWindow()->clear();

    menuText.setString("Menu\n"
        "1. Travel\n"
        "2. Fight\n"
        "3. Back to Menu");
    menuText.setFillColor(Color::White);
    game->getWindow()->draw(menuText);
    RectangleShape selector(RectangleShape(Vector2f(10, 10)));
    selector.setFillColor(Color::Red);
    selector.setPosition(90, 100 + selectedItem * 20);
    game->getWindow()->draw(selector);
}