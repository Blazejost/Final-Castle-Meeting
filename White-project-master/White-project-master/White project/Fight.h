#pragma once

class Fight {
public:
    //VAriables
    sf::Texture playerTexture;
    Sprite playerSprite;

    Texture enemyTexture;
    Sprite enemySprite;

    Font font;

    Text playerHealthText;
    Text enemyHealthText;
    
    Text actionText;
    bool playerTurnActive = true;

    sf::Text statusText;

    Text winText;
    Text loseText;


    Fight(Level*level, Player* player, Enemy* enemy, int maxTurns);
    RenderWindow* window;
    Level* level;

    Player* player;
	Enemy* enemy;

    int maxTurns;
    void startFight();

    bool playerWon;
    bool playerLost;

    bool enemyPrepareSpecialAttack = false;

public:
    void playerTurn();

    void enemyTurn();

    void update();

    void render(sf::RenderWindow* window);
};
