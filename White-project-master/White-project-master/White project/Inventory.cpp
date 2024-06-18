#include "stdafx.h"
#include "Player.h"
#include "Inventory.h"
#include "Item.h"
#include "Key.h"

Inventory::Inventory(Player* player) {
    this->player = player;

    background = sf::RectangleShape(sf::Vector2f(800, 1200));
	background.setFillColor(sf::Color(12, 32, 122, 150));

    font.loadFromFile("Fonts/Garton.ttf");
    titleText.setFont(font);
    titleText.setString("Inventory");
	titleText.setScale(2.f, 2.f);

    inventoryText.setFont(font);
    inventoryText.setPosition(sf::Vector2f(500, 100));
    inventoryText.setScale(2.f, 2.f);

    selectedItemIndex = 0;

	//Upgrade inventory
    backgroundUpgrade = RectangleShape(sf::Vector2f(800, 500));
    backgroundUpgrade.setFillColor(sf::Color(222,222,0, 100));

    upgradeTitleText.setFont(font);
    upgradeTitleText.setString("Upgrade menu");
    upgradeTitleText.setScale(2.f, 2.f);

    increaseMaxHealth.setFont(font);
    increaseMaxHealth.setScale(1.f, 1.f);

    increaseShield.setFont(font);
    increaseShield.setScale(1.f, 1.f);

    increaseEnergy.setFont(font);
    increaseEnergy.setScale(1.f, 1.f);

    Clock clock;
}

void Inventory::addItem(Item* item) {
    items.push_back(std::move(item));
}

void Inventory::removeItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
    }
}

void Inventory::removeItem(Item* item) {
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
    }
}
void Inventory::render(sf::RenderWindow* window) {
    upgrade();

    std::string inventoryString;
    for (size_t i = 0; i < items.size(); ++i) {
        if (i == selectedItemIndex) {
            inventoryString += "> ";
            inventoryString += items[i]->name + "\n";
        }
    }
    inventoryText.setString(inventoryString);

    background.setPosition(player->positionX - 400, player->positionY - 600);
    titleText.setPosition(player->positionX - 100, player->positionY - 400);
    inventoryText.setPosition(player->positionX - 100, player->positionY - 300);

    //Upgrade menu update
    backgroundUpgrade.setPosition(player->positionX - 400, player->positionY + 200);
    upgradeTitleText.setPosition(player->positionX - 200, player->positionY + 200);

    //Increase max health
    increaseMaxHealth.setPosition(player->positionX - 380, player->positionY + 300);
    increaseMaxHealth.setString("Key 1 - to by health potion (2 hearts), 10 coins. You have: " + to_string(player->maxHealth));

    //Increase shield
    increaseShield.setPosition(player->positionX - 380, player->positionY + 350);
    increaseShield.setString("Key 2 - to buy shield, 20 coins. You have: " + to_string(player->shield));

    //Increase energy
    increaseEnergy.setPosition(player->positionX - 380, player->positionY + 400);
    increaseEnergy.setString("Key 3 - to buy energy for special attack, 30 coins. You have: " + to_string(player->energy));

    //Draw invetntory text
    window->draw(background);
    window->draw(titleText);
    window->draw(inventoryText);

    //Draw upgrade text
	window->draw(backgroundUpgrade);
    window->draw(upgradeTitleText);
    window->draw(increaseMaxHealth);
    window->draw(increaseShield);
    window->draw(increaseEnergy);

  
    if (isUpgraded) {
        isUpgraded = false;
        sleep(seconds(1));
    }
}

void Inventory::upgrade() {
    if (Keyboard::isKeyPressed(Keyboard::Num1) && player->money >= 10) {
        if (player->health == player->maxHealth) {
            player->maxHealth++;
            player->money -= 10;
            isUpgraded = true;
        }
        else if (player->health < player->maxHealth) {
            player->health += 2;
			player->money -= 10;
			isUpgraded = true;
		}
    }
    else if (Keyboard::isKeyPressed(Keyboard::Num2) && player->money >= 20) {
        player->shield++;
        player->money -= 20;
        isUpgraded = true;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Num3) && player->money >= 30) {
        player->energy++;
        player->money -= 30;
        isUpgraded = true;
    }
}