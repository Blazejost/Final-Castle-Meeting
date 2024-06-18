#include "stdafx.h"
#include "Game.h"
#include "Interface.h"
#include "Level.h"
#include "Player.h"

//Constructor
Interface::Interface(Player* player) {
	//interface information
	this->player = player;
	this->health = player->health;
	this->money = player->money;
	this->currentLevel = &player->game->currentLevel;

	//Create panel for stats
	statsPanel.setFillColor(sf::Color(10, 10, 10, 100));
	statsPanel.setSize(sf::Vector2f(300, 120));
	statsPanel.setPosition(sf::Vector2f(0, 0));

	//Text for stats
	font.loadFromFile("Fonts/Garton.ttf");
	healthText.setFont(font);
	healthText.setCharacterSize(30);
	healthText.setFillColor(sf::Color::White);
	healthText.setString("Health: " + to_string(health) + "\n" + "Money: " + to_string(money) + "\n" + "Level: " + to_string(*currentLevel));
}
//destructor
Interface::~Interface()
{
}
//Updates interface information about player stats
void Interface::update(float dt) {
	this->health = player->health;
	this->currentLevel = &player->game->currentLevel;
	this->money = player->money;

	//updates the stats
	healthText.setString("Health: " + to_string(health) + "/" + to_string(player->maxHealth) + "\n"
		+ "Money: " + to_string(money) + "\n"
		+ "Level: " + to_string(*currentLevel));
}
//Renders interface
void Interface::render(RenderWindow* window)
{
	//stes position of stats panel
	statsPanel.setPosition(player->positionX + 250, player->positionY - 460);
	healthText.setPosition(player->positionX + 270, player->positionY - 450);
	//draws the panel
	window->draw(statsPanel);
	window->draw(healthText);
}
