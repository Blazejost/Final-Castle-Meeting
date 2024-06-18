#include "stdafx.h"
#include "Game.h"
#include "Interface.h"
#include "Level.h"
#include "Player.h"

Interface::Interface(Player* player) {
	this->player = player;
	this->health = player->health;
	this->money = player->money;
	this->currentLevel = &player->game->currentLevel;

	//Create panel for stats
	statsPanel.setFillColor(sf::Color(10, 10, 10, 100));
	//statsPanel.setOutlineColor(sf::Color::White);
	//statsPanel.setOutlineThickness(5);
	statsPanel.setSize(sf::Vector2f(300, 120));
	statsPanel.setPosition(sf::Vector2f(0, 0));

	//Text for stats
	font.loadFromFile("Fonts/Garton.ttf");
	healthText.setFont(font);
	healthText.setCharacterSize(30);
	healthText.setFillColor(sf::Color::White);
	healthText.setString("Health: " + to_string(health) + "\n" + "Money: " + to_string(money) + "\n" + "Level: " + to_string(*currentLevel));
}

Interface::~Interface()
{
}

void Interface::update(float dt) {
	this->health = player->health;
	this->currentLevel = &player->game->currentLevel;
	this->money = player->money;

	healthText.setString("Health: " + to_string(health) + "/" + to_string(player->maxHealth) + "\n"
		+ "Money: " + to_string(money) + "\n"
		+ "Level: " + to_string(*currentLevel));
}

void Interface::render(RenderWindow* window)
{
	statsPanel.setPosition(player->positionX + 250, player->positionY - 460);
	healthText.setPosition(player->positionX + 270, player->positionY - 450);

	window->draw(statsPanel);
	window->draw(healthText);
}
