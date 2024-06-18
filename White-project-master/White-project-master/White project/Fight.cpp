#include "stdafx.h"
#include "Fight.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"

//constructor
Fight::Fight(Level* level, Player* player, Enemy* enemy, int maxTurns)
{
    this->window = level->target;

	this->level = level;
    this->player = player;
	this->enemy = enemy;
    this->maxTurns = maxTurns;
}
//starts the fight
void Fight::startFight()
{
    //player sprite
    playerTexture.loadFromFile("Images/AnimationSheet_Character.png", IntRect(0, 0, 32, 32));
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(100, 100);

    //enemy sprite
    enemyTexture = enemy->texture;
    enemySprite.setTexture(enemyTexture);
    enemySprite.setPosition(300, 100);

    //font
    font.loadFromFile("Fonts/Garton.ttf");

    //player health text
    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(24);
    playerHealthText.setPosition(100, 50);
    //enemy health text
    enemyHealthText.setFont(font);
    enemyHealthText.setCharacterSize(24);
    enemyHealthText.setPosition(300, 50);
    //sets information about health
    playerHealthText.setString("Player Health: " + std::to_string(player->health));
    enemyHealthText.setString("Enemy Health: " + std::to_string(enemy->health));

    //information about action in fight
    actionText.setFont(font);
	actionText.setCharacterSize(24);
	actionText.setPosition(50, 300);
    actionText.setFillColor(Color::Red);
    actionText.setString("Choose an action: 1. Attack, 2. Block, 3. Special Attack");

    //win text
    winText.setFont(font);
    winText.setCharacterSize(48);
    winText.setPosition(200, 200);
    //lose text
    loseText.setFont(font);
    loseText.setCharacterSize(48);
    loseText.setPosition(200, 200);
    //status text
    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setPosition(200, 260);

    Clock clock;

}

//player turn in fight
void Fight::playerTurn() {
    sf::Event event;
	statusText.setString("Player's turn");
    render(window);
    //if someones health is 0 it dies
    if(player->health <= 0 || enemy->health <= 0) {
		return;
	}
    //checks for player choice
    while (true) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }//attack
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    player->attack(enemy);

                    actionText.setString("Player attacks");
                    render(window); // Update the actionText
                    
                    window->display(); // Update the window to display the changes
                    sleep(seconds(2)); // Add 2-second delay

                    return;
                }//block
                else if (event.key.code == sf::Keyboard::Num2 && player->shield > 0) {
                    player->block();
                    enemy->blockDamage = false;
                    

                    actionText.setString("Player blocks");
                    render(window); // Update the actionText
                    window->display(); // Update the window to display the changes
                    sleep(seconds(2)); // Add 2-second delay

                    return;
                }//special attack
                else if (event.key.code == sf::Keyboard::Num3 && player->energy > 0) {
                    player->specialAttack(enemy);
                    player->energy--;

                    actionText.setString("Player uses special attack");
                    render(window); // Update the actionText
                    window->display(); // Update the window to display the changes
                    sleep(seconds(2)); // Add 2-second delay

                    return;
                }
            }
        }
    }
}
//enemy turn in fight
void Fight::enemyTurn() {
    playerTurnActive = false;
    statusText.setString("Enemy's turn");
    render(window); // Update the actionText
    window->display();

    int choice;
    if (!enemyPrepareSpecialAttack){
        choice = rand() % 3; // random choice of the enemy
    }
    else {
        choice = 2;//if player prepared special attack it uses it
    }

    switch (choice) {
        //enemy attack
    case 0:
        enemy->attack(player);

        actionText.setString("Enemy attacks");
        render(window); // Update the actionText
        window->display(); // Update the window to display the changes

        break;
        //enemy block
    case 1:
        enemy->block();
        player->blockDamage = false;

        actionText.setString("Enemy blocks");
        render(window); // Update the actionText
        window->display(); // Update the window to display the changes

        break;
        //enemy special attack
    case 2:
        if (!enemyPrepareSpecialAttack) {
            cout << "Enemy prepares special attack!" << endl;
            enemyPrepareSpecialAttack = true;

            actionText.setString("Enemy prepares special attack!");
            render(window); // Update the actionText
            window->display(); // Update the window to display the changes

        }
        else if (enemyPrepareSpecialAttack) {
            cout << "Enemy uses special attack!" << endl;
            enemy->specialAttack(player);
            enemyPrepareSpecialAttack = false;

            actionText.setString("Enemy uses special attack!");
            render(window); // Update the actionText
            window->display(); // Update the window to display the changes

        }
        else {
            enemy->attack(player);

            actionText.setString("Enemy attack!");
            render(window); // Update the actionText
            window->display(); // Update the window to display the changes

        }

        break;
    }
}
//update of the fight
void Fight::update()
{
    if (player->health <= 0) {
        // The fight is over, so we can exit the loop
        cout << "Fight is over!" << endl;
        playerLost = true;
        return;
    }
    if (enemy->health <= 0) {
        // The fight is over, so we can exit the loop
        cout << "Fight is over!" << endl;
        playerWon = true;

        enemy->isDead = true;
        delete enemy;
        level->fightStarted = false;
        return;
    }
    //initial action text
    if (playerTurnActive) {
        actionText.setString("Choose an action: 1. Attack, 2. Block, 3. Special Attack");
    }
    else {
        actionText.setString("");
    }
    //player turn
    if (player->health > 0 && enemy->health > 0) {
        playerTurn();
    }
    //enemy turn
    if (player->health > 0 && enemy->health > 0) {
        enemyTurn();
    }
    //updates information about healths 
    playerHealthText.setString("Player Health: " + std::to_string(player->health));
    enemyHealthText.setString("Enemy Health: " + std::to_string(enemy->health));

    render(window); // Render the action text and other elements
    window->display(); // Display the rendered frame
}

//renders fight
    void Fight::render(sf::RenderWindow* window)
    {
        window->clear(Color::Black);
        window->draw(playerSprite);
        window->draw(enemySprite);
        window->draw(playerHealthText);
        window->draw(enemyHealthText);

        window->draw(actionText);

        if (player->health > 0 && enemy->health > 0) {
            window->draw(statusText);
        }
        else if (player->health > 0) {
            window->draw(winText);
        }
        else {
            window->draw(loseText);
        }
    }