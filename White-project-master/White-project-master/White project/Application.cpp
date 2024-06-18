#include "stdafx.h"
#include "Application.h"
#include "Menu.h"
#include "Game.h"

Application::Application()
{
    //Initialization
    initVariables();
    initWindow();
    initMenu();
}

Application::~Application()
{
    delete menu;
    if (gameStarted)
        delete game;

    window->close(); // Close the window before setting the pointer to nullptr
    window = nullptr; // Set the pointer to nullptr
}

void Application::run()
{
    while (running())
    {
        update(dt);
        render();
    }
}

const bool Application::running() const
{
    return window->isOpen();
}


void Application::initVariables()
{
    window = nullptr;
    menu = nullptr;
    game = nullptr;
    gameStarted = false;
}

void Application::initWindow()
{
    //Create window
    videomode.height = 1000;
    videomode.width = 1200;
    window = new RenderWindow(videomode, "Simple game", Style::Titlebar | Style::Close);
}

void Application::initMenu()
{
    menu = new Menu(this);
}

void Application::update(float dt)
{
    sf::Event event;
    while (window->pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            window->close();
        }

        // Calculate deltaTime
        dt = clock.restart().asSeconds();
        cout << dt << endl;

        if (menu->isActive()) {
            //menu->update(dt);
        }

        else if (gameStarted)
            game->update(dt);
    }
}

void Application::render()
{
    window->clear();

    if (menu->isActive()) {
        //menu->render(*window);
    }
    //else if (gameStarted)
        //game->render(window);

    window->display();
}

void Application::initGame()
{
    //game = new Game();
}