#include "stdafx.h"
#include "Level.h"

#include "Game.h"
#include "Map.h"
#include "Tile.h"
#include "Item.h"
#include "Coin.h"
#include "Heart.h"
#include "Key.h"
#include "Player.h"
#include "Inventory.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Goblin.h"

#include "Fight.h"



enum class Locations;
//constructor
Level::Level(Game* game)
{
    //Take data from game
    this->game = game;
    this->player = game->player;
    this->gamemode = &game->gameMode;
    this->currentLevel = &game->currentLevel;
    this->target = game->window;
    this->location = game->location;

	//Create map
    tileSize = 140;
    map = new Map(this);
    map->generateMap(30, 30, tileSize);

    //Item info
    coinValue = 10;

    //Add map items for level
    itemAmount = 2;
    addMapItems(itemAmount);

    //Generate items on map
	map->generateItems(mapItems);
    

    //Add enemies that will apear in the level
    enemiesAmount = 2;
    addEnemies(enemiesAmount);

	//Generate enemies on map
	map->generateEnemies(mapEnemies);

	//Game process
    isActiveKey = false;
}
//destructor
Level::~Level() {
    delete map;
}



    void Level::update(float deltaTime) {
        float playerX = player->sprite.getPosition().x;
        float playerY = player->sprite.getPosition().y;

      input(deltaTime);

     

        // Move player
        sf::FloatRect playerBounds(playerX, playerY, player->sprite.getGlobalBounds().width, player->sprite.getGlobalBounds().height);

        if (player->controls == Controls::UP) {
            playerBounds.top -= player->velocity * deltaTime;
        }
        if (player->controls == Controls::DOWN) {
            playerBounds.top += player->velocity * deltaTime;
        }
        if (player->controls == Controls::LEFT) {
            playerBounds.left -= player->velocity * deltaTime;
            player->sideLook = 'l';
        }
        if (player->controls == Controls:: RIGHT) {
            playerBounds.left += player->velocity * deltaTime;
            player->sideLook = 'r';
        }


    // Check for collisions with walls
    for (int y = playerBounds.top / map->tileSize; y <= (playerBounds.top + playerBounds.height) / map->tileSize; ++y) {
        for (int x = playerBounds.left / map->tileSize; x <= (playerBounds.left + playerBounds.width) / map->tileSize; ++x) {
            if (map->tiles[y][x].wall && playerBounds.intersects(map->tiles[y][x].sprite.getGlobalBounds())) {
                // Handle collision with wall
                // Move the player back to the previous position
                switch (player->controls) {
                case Controls::UP:
                    playerBounds.top += player->velocity * deltaTime;
                    break;

                case Controls::DOWN:
                    playerBounds.top -= player->velocity * deltaTime;
                    break;

                case Controls::LEFT:
                    playerBounds.left += player->velocity * deltaTime;
                    break;

                case Controls::RIGHT:
                    playerBounds.left -= player->velocity * deltaTime;
                    break;

                default:
                    break;
                }
                break;
            }
        }
    }

    // Prevent the player from moving into the first and last lines of the map
    if (playerBounds.top < map->tileSize || playerBounds.top + playerBounds.height > map->height * map->tileSize - map->tileSize) {
        playerBounds.top = clamp(playerBounds.top, static_cast<float>(map->tileSize), static_cast<float>(map->height * map->tileSize - player->sprite.getGlobalBounds().height - map->tileSize));
    }

    if (playerBounds.left < map->tileSize || playerBounds.left + playerBounds.width > map->width * map->tileSize - map->tileSize) {
        playerBounds.left = clamp(playerBounds.left, static_cast<float>(map->tileSize), static_cast<float>(map->width * map->tileSize - player->sprite.getGlobalBounds().width - map->tileSize));
    }

    player->sprite.setPosition(playerBounds.left, playerBounds.top);
    player->positionX = playerBounds.left;
    player->positionY = playerBounds.top;
    player->positionXTile = static_cast<int>(playerBounds.left) / map->tileSize;
    player->positionYTile = static_cast<int>(playerBounds.top) / map->tileSize;

    updatePlayerAnimation(deltaTime);
    nearPlayer();

    // Update enemies
    for (Enemy* enemy : map->enemies) {
        enemy->update(deltaTime);

        // Check for collisions between player and enemies
        sf::FloatRect playerBounds(player->sprite.getPosition().x, player->sprite.getPosition().y, player->sprite.getGlobalBounds().width, player->sprite.getGlobalBounds().height);
        sf::FloatRect enemyBounds(enemy->positionX, enemy->positionY, enemy->sprite.getGlobalBounds().width, enemy->sprite.getGlobalBounds().height);

        if (playerBounds.intersects(enemyBounds) && fightStarted == false) {
            // Player has touched the enemy, so handle the enemy's interaction
            //player->takeDamage(enemy->damage);
            fightStarted = true;

            fight = new Fight(this, player, enemy, 10);
            
            fight->startFight();
            *gamemode = GameModes::FIGHT;
        }
    }

    
}

//Player controls
    void Level::input(float deltaTime) {
		if (!isActiveKey)
        {
            up = Keyboard::isKeyPressed(Keyboard::W);
            down = Keyboard::isKeyPressed(Keyboard::S);
            left = Keyboard::isKeyPressed(Keyboard::A);
            right = Keyboard::isKeyPressed(Keyboard::D);
        }

        player->controls = Controls::IDLE;
        if (up) {
            player->controls = Controls::UP;
            up = false;
        }
        else if (left) {
            player->controls = Controls::LEFT;
			left = false;
        }
        else if (right) {
            player->controls = Controls::RIGHT;
			right = false;
        }
        else if (down) {
            player->controls = Controls::DOWN;
			down = false;
        }

        if (up || left || right || down) {
            isActiveKey = true;
		}
		else {
			isActiveKey = false;
		}
    }
    


void Level::renderLevel()
{
    if (target == nullptr) {
        // Error handling: target is null
        //return;
    }

    
    
    // Render the level
    updateEnemies();
    map->render();
    player->render();


}

//Other

//add items that will appear on map
void Level::addMapItems(int itemAmount) {
    mapItems.resize(itemAmount);
    
    //Coin
	coinTexture.loadFromFile("Images/Level/Items/Golden Coin.png");
    Coin* goldenCoin = new Coin(this, coinTexture, coinValue);

    mapItems[0] = goldenCoin;

    //Heart
    heartTexture.loadFromFile("Images/Level/Items/Heart.png");
    Heart* heart = new Heart(this, heartTexture, 1);

    mapItems[1] = heart;
}

//adds enemies
void Level::addEnemies(int enemiesAmount)
{
    mapEnemies.resize(enemiesAmount);

    //Enemies parametres
    int health = 10;
    int damage = 2;
    int speed = 1;

    //every location has different enemy parameters
	if (location == Locations::CASTLE_MIDDLE) {
        health = 15;
        damage = 3;
    }
    else if (location == Locations::CASTLE_STAIRS) {
        health = 20;
        damage = 4;
    }

    //loads textures and add enemies to map vector
    skeletonTexture.loadFromFile("Images/Enemies/Skeleton enemy.png", IntRect(0, 0, 60, 40));
    Skeleton* skeleton = new Skeleton(this, skeletonTexture, health, damage, speed);
    mapEnemies[0] = skeleton;

    goblinTexture.loadFromFile("Images/Enemies/Bringer-of-Death_Idle_1.png", IntRect(80, 40, 120, 97));
    Goblin* goblin = new Goblin(this, goblinTexture, health, damage, speed);

    mapEnemies[1] = goblin;

}

//updates player animation
void Level::updatePlayerAnimation(float deltaTime) {
    
    //left walking animation
    if (player->controls != Controls::IDLE && player->sideLook == 'l') {
        static int frameIndex = 0;
        static float animationTimer = 0.f;
        const float animationSpeed = 0.3f; // Fixed animation speed

        animationTimer += 0.01f; // Fixed time increment
        if (animationTimer >= animationSpeed) {
            frameIndex = (frameIndex + 1) % 8; // Assuming 8 frames in the animation
            animationTimer = 0.0f;
        }

        int startX = 256; // Starting x-coordinate of the animation frames
        int startY = 160; // Starting y-coordinate of the animation frames (4th line)
        int frameWidth = 32; // Width of each animation frame
        int frameHeight = 32; // Height of each animation frame
        int totalWidth = 8 * frameWidth; // Total width of the animation sheet

        player->texture.loadFromFile("Images/AnimationSheet_CharacterL.png", IntRect(totalWidth - frameIndex * frameWidth - frameWidth, startY, frameWidth, frameHeight));
        player->sprite.setTexture(player->texture);
        player->sprite.setScale(2.5f, 2.5f);
    }
    //right walking animation
    else if (player->controls != Controls::IDLE && player->sideLook == 'r') {
        static int frameIndex = 0;
        static float animationTimer = 0.f;
        const float animationSpeed = 0.3f; // Fixed animation speed

        animationTimer += 0.01f; // Fixed time increment
        if (animationTimer >= animationSpeed) {
            frameIndex = (frameIndex + 1) % 8; // Assuming 3 frames in the animation
            animationTimer = 0.0f;
        }

        int startX = 0; // Starting x-coordinate of the animation frames
        int startY = 160; // Starting y-coordinate of the animation frames (4th line)
        int frameWidth = 32; // Width of each animation frame
        int frameHeight = 32; // Height of each animation frame

        player->texture.loadFromFile("Images/AnimationSheet_Character.png", IntRect(startX + frameIndex * frameWidth, startY, frameWidth, frameHeight));
        player->sprite.setTexture(player->texture);
        player->sprite.setScale(2.5f, 2.5f);
    }
    //left idle animation
    else if (player->controls == Controls::IDLE && player->sideLook == 'l') {
        static int frameIndex = 0;
        static float animationTimer = 0.f;
        const float animationSpeed = 1.f; // Fixed animation speed

        animationTimer += 0.01f; // Fixed time increment
        if (animationTimer >= animationSpeed) {
            frameIndex = (frameIndex + 1) % 2; // Assuming 3 frames in the animation
            animationTimer = 0.0f;
        }

        int startX = 0; // Starting x-coordinate of the animation frames
        int startY = 0; // Starting y-coordinate of the animation frames (4th line)
        int frameWidth = 32; // Width of each animation frame
        int frameHeight = 32; // Height of each animation frame
        int totalWidth = 8 * frameWidth; // Total width of the animation sheet

        player->texture.loadFromFile("Images/AnimationSheet_CharacterL.png", IntRect(totalWidth - frameIndex * frameWidth - frameWidth, startY, frameWidth, frameHeight));
        player->sprite.setTexture(player->texture);
        player->sprite.setScale(2.5f, 2.5f);
    }
    //right idle animation
    else {
        static int frameIndex = 0;
        static float animationTimer = 0.f;
        const float animationSpeed = 1.f; // Fixed animation speed

        animationTimer += 0.01f; // Fixed time increment
        if (animationTimer >= animationSpeed) {
            frameIndex = (frameIndex + 1) % 2; // Assuming 3 frames in the animation
            animationTimer = 0.0f;
        }

        int startX = 0; // Starting x-coordinate of the animation frames
        int startY = 0; // Starting y-coordinate of the animation frames (4th line)
        int frameWidth = 32; // Width of each animation frame
        int frameHeight = 32; // Height of each animation frame
        int totalWidth = 8 * frameWidth;


        player->texture.loadFromFile("Images/AnimationSheet_Character.png", IntRect(startX + frameIndex * frameWidth, startY, frameWidth, frameHeight));
        player->sprite.setTexture(player->texture);
        player->sprite.setScale(2.5f, 2.5f);
    }
      

        
}
//checks if items are near player
void Level::nearPlayer() {
     sf::FloatRect playerBounds(player->sprite.getPosition().x, player->sprite.getPosition().y, player->sprite.getGlobalBounds().width, player->sprite.getGlobalBounds().height);
       
    for (Item* item : map->items) {
        sf::FloatRect itemBounds(item->sprite.getPosition().x, item->sprite.getPosition().y, item->sprite.getGlobalBounds().width, item->sprite.getGlobalBounds().height);

        if (playerBounds.intersects(itemBounds)) {
            // Player has touched the item, so handle the item's interaction
            takeItem(item);
            break;
        }
    }

    //Key
    FloatRect keyBounds(map->key->sprite.getPosition().x, map->key->sprite.getPosition().y, map->key->sprite.getGlobalBounds().width, map->key->sprite.getGlobalBounds().height);

    if (playerBounds.intersects(keyBounds )&& player->hasKey == false) {
		// Player has touched the item, so handle the item's interaction
		takeItem(map->key);
	}

    //Door
    FloatRect doorBounds(map->lockSprite.getPosition().x, map->lockSprite.getPosition().y, map->lockSprite.getGlobalBounds().width * 1.2f, map->lockSprite.getGlobalBounds().height * 1.2f);

    if (playerBounds.intersects(doorBounds) && player->hasKey == true) {
        // Player has touched the item, so handle the item's interaction
        
		player->inventory->removeItem(map->key);
        player->hasKey = false;
        game->levelCompleted = true;
    }
}
//player takes item
void Level::takeItem(Item* item) {
    // Handle the interaction with the item
    //coin
    if (dynamic_cast<Coin*>(item)) {
        item->takeItem(player);
        
        for (auto it = map->items.begin(); it != map->items.end(); ) {
            if (*it == item) {
                delete* it;
                it = map->items.erase(it);
                break;
            }
            else {
                ++it;
            }
        }
    }
    //heart
    else if (dynamic_cast<Heart*>(item) && player->health < player->maxHealth) {
        
        item->takeItem(player);
        cout << player->health << endl;
        
            for (auto it = map->items.begin(); it != map->items.end(); ) {
                if (*it == item) {
                    delete* it;
                    it = map->items.erase(it);
                    break;
                }
                else {
                    ++it;
                }
            }
        }
    //key
    else if (dynamic_cast<Key*>(item)) {
		item->takeItem(player);
    }
}

//void Level::animateEnemy(Enemy* enemy, float deltaTime) {
//    //Implement enemy animation logic here
//        // Update enemy texture based on its animation pattern
//        // You can use a timer and frame index to control the enemy's animation
//
//        // Example: Simple enemy animation pattern (walk left and right)
//        static int frameIndex = 0;
//    static float animationTimer = 0.0f;
//    const float animationSpeed = 0.3f; // Adjust this value to control the enemy's animation speed
//
//    animationTimer += deltaTime;
//
//    if (animationTimer >= animationSpeed) {
//        animationTimer = 0.0f;
//        frameIndex = (frameIndex + 1) % 2; // Assuming 2 frames in the animation
//    }
//
//    int startX = 0; // Starting x-coordinate of the animation frames
//    int startY = 0; // Starting y-coordinate of the animation frames
//    int frameWidth = 32; // Width of each animation frame
//    int frameHeight = 32; // Height of each animation frame
//
//    if (enemy->direction == 'l') {
//        enemy->texture.loadFromFile("Images/EnemyAnimationSheet_Left.png", IntRect(startX + frameIndex * frameWidth, startY, frameWidth, frameHeight));
//    }
//    else {
//        enemy->texture.loadFromFile("Images/EnemyAnimationSheet_Right.png", IntRect(startX + frameIndex * frameWidth, startY, frameWidth, frameHeight));
//    }
//
//    enemy->sprite.setTexture(enemy->texture);
//    enemy->sprite.setScale(2.0f, 2.0f);
//}

//updates enemies
void Level::updateEnemies()
{
    //checks if enemies were deleted from map
    for (int i = 0; i < map->enemies.size(); i++) {
        if (map->enemies[i]->isDead) {
            map->enemies.erase(map->enemies.begin() + i);
            i--; // decrement i to avoid skipping the next enemy
        }
    }
}