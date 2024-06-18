#include "stdafx.h"
#include "Game.h"
#include "Enemy.h"
#include "Level.h"
#include "Player.h"


Enemy::Enemy() {

}

Enemy::Enemy(Level* level, Texture texture, int health, int damage, int speed)
{
    this->level = level;

    this->texture = texture;
    sprite.setTexture(texture);

    attackTimer = 0.0f;

}

Enemy::Enemy(const Enemy& other) {
    // Copy the members of the other object
    //positionX = other.positionX;
    //positionY = other.positionY;
    level = other.level;
    texture = other.texture;
    sprite = Sprite(texture);
    health = other.health; 
    damage = other.damage;
    speed = other.speed;
	positionX = other.positionX;
	positionY = other.positionY;
    direction = other.direction;

    // Assign the texture to the sprite
    //... copy other members...
}

Enemy::~Enemy() {}

void Enemy::update(float deltaTime) {

    // Update enemy attack
   /* startAttack(deltaTime);*/

   /* attackTimer += deltaTime;*/
}

    //void Enemy::move(float deltaTime) {
    //    // Implement enemy movement logic here
    //    // Update enemy position based on its movement pattern
    //    // You can use a timer and frame index to control the enemy's movement animation

    //    // Example: Simple enemy movement pattern (move left and right)
    //    static float movementTimer = 0.0f;
    //    const float movementSpeed = 50.0f; // Adjust this value to control the enemy's movement speed

    //    movementTimer += deltaTime;

    //    if (movementTimer >= 1.0f) {
    //        movementTimer = 0.0f; 
    //        direction = (direction == 'l') ? 'r' : 'l'; 
    //    }

    //    if (direction == 'l') {
    //        positionX -= movementSpeed * deltaTime; 
    //    }
    //    else {
    //        positionX += movementSpeed * deltaTime;
    //    }

    //    sprite.setPosition(positionX, positionY);
    //
//}

    void Enemy::startAttack(float deltaTime) {
        // Implement enemy attack logic here
        // Check if the enemy is within attack range and attack the player
        // You can use a timer and frame index to control the enemy's attack animation

        // Example: Simple enemy attack pattern (attack when within a certain distance)
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

//bool Enemy::canAttack() {
//    if (attackTimer >= attackDelay) {
//        attackTimer = 0.0f; // Reset the timer
//        return true; // Enemy can attack
//    }
//    return false; // Enemy cannot attack yet
//}

bool Enemy::reverseDirection() {
    if(direction == 'l') {
		direction = 'r';
	} else {
		direction = 'l';
	}
	return true;
}

void Enemy::attack(Player* player) {
    int damage = 2; // default attack damage
    player->takeDamage(damage);
    cout << "Enemy attacks player for " << damage << " damage!" << endl;
}

void Enemy:: block() {
    cout << "Enemy blocks!" << endl;
    blockDamage = true; // set block flag
}

void Enemy::specialAttack(Player* player) {
    // triple attack damage
    player->takeDamage(damage * 3);
    cout << "Enemy uses special attack on player for " << damage << " damage!" << endl;
}

void Enemy::takeDamage(int damage) {
    if (blockDamage) {
        damage /= 3; // reduce damage if blocking
        blockDamage = false; // reset block flag
    }
    this->health -= damage;
    cout << "Enemy takes " << damage << " damage!" << endl;
}