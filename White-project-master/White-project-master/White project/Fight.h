#pragma once

class Fight {
public:
    //Variables
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

    //fight variables
    int maxTurns;

    bool playerWon;
    bool playerLost;

    bool enemyPrepareSpecialAttack = false;

    //constructor
    Fight(Level*level, Player* player, Enemy* enemy, int maxTurns);

    //pointers
    RenderWindow* window;
    Level* level;

    Player* player;
    Enemy* enemy;
    
    //functions
    void startFight();

public:
    //functions
    void playerTurn();

    void enemyTurn();

    void update();

    void render(sf::RenderWindow* window);
};
