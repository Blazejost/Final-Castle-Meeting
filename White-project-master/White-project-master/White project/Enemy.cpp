#include "stdafx.h"
#include "Game.h"
#include "Enemy.h"
#include "Level.h"
#include "Player.h"

//Constructors
Enemy::Enemy() {

}

Enemy::Enemy(Level* level, Texture texture, int health, int damage, int speed)
{
    this->level = level;

    this->texture = texture;
    sprite.setTexture(texture);

    attackTimer = 0.0f;

}

//Copy constructor
Enemy::Enemy(const Enemy& other) {
    // Copy the members of the other object
    level = other.level;
    texture = other.texture;
    sprite = Sprite(texture);
    health = other.health; 
    damage = other.damage;
    speed = other.speed;
	positionX = other.positionX;
	positionY = other.positionY;
    direction = other.direction;
}

//Destructor
Enemy::~Enemy() {}

//Update enemy
void Enemy::update(float deltaTime) {}

//if player near the enemy it attacks
    void Enemy::startAttack(float deltaTime) {

        static float attackTimer = 0.0f;
        const float attackRange = 100.0f; // Adjust this value to control the enemy's attack range
        const float attackDelay = 10.0f; // Increase the attack delay to make the pause longer

        sf::Vector2f playerPosition(level->player->sprite.getPosition());
        sf::Vector2f enemyPosition(sprite.getPosition());
        float distance = sqrt(pow(playerPosition.x - enemyPosition.x, 2) + pow(playerPosition.y - enemyPosition.y, 2));

        attackTimer += deltaTime;

        if (distance <= attackRange && attackTimer >= attackDelay) {
            attackTimer = 0.0f;
            // Perform enemy attack (e.g., reduce player's health)
            *level->gamemode = GameModes::FIGHT;
        }
    }

    bool Enemy::reverseDirection() {
        if (direction == 'l') {
            direction = 'r';
        }
        else {
            direction = 'l';
        }
        return true;
    }

//attack of enemy
void Enemy::attack(Player* player) {
    int damage = 2; // default attack damage
    player->takeDamage(damage);
    cout << "Enemy attacks player for " << damage << " damage!" << endl;
}

//block of the enemy
void Enemy:: block() {
    cout << "Enemy blocks!" << endl;
    blockDamage = true; // set block flag
}

//Special attack of the enemy
void Enemy::specialAttack(Player* player) {
    // triple attack damage
    player->takeDamage(damage * 3);
    cout << "Enemy uses special attack on player for " << damage << " damage!" << endl;
}

//takes damage(enemy) from player
void Enemy::takeDamage(int damage) {
    if (blockDamage) {
        damage /= 3; // reduce damage if blocking
        blockDamage = false; // reset block flag
    }
    this->health -= damage;
    cout << "Enemy takes " << damage << " damage!" << endl;
}