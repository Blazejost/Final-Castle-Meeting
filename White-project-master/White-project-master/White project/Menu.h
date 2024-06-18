#pragma once

#include "Game.h"

class Menu {
public:
    Menu(Game* game);
    ~Menu();

    void update();
    void render();

private:
    Game* game;
    Font font;
    Text menuText;
    int selectedItem;
};