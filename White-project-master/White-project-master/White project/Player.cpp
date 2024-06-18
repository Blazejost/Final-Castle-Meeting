#include "stdafx.h"

#include "Game.h"
#include "Player.h"
#include "Interface.h"
#include "Inventory.h"
#include "Level.h"
#include "Map.h"
#include "Item.h"
#include "Enemy.h"


//Constructor
Player::Player(Game* game, string name, Texture playerTexture)
{
	//load information about game
	this->window = game->window;
	this->game = game;
	this->level = game->level;

	//name
	this->name = name;
	//created interface
	interface = new Interface(this);

	//Stats
	health = 8;
	maxHealth = 10;
	damage = 3;
	shield = 3;
	energy = 1;

	money = 0;

	blockDamage = false;

	//Inventory
	inventory = new Inventory(this);
	hasKey = false;

	//sets texture and position of the player
	this->texture = playerTexture;
	positionX = 0.f;
	positionY = 0.f;

	positionXTile = 0;
	//sets sprite
	sprite.setTexture(texture);
	sprite.setScale(1.5f, 1.5f);
	sprite.setPosition(positionX, positionY);
	sideLook = 'l';

	//initialize speed
	velocity = 10.f;


	
}
//Destructor
Player::~Player() {
	delete interface;
	delete inventory;
}
//update player
void Player::update() {

	
	
}

//render player
void Player::render() {
	
	window->draw(sprite);
}
//sets position of player
void Player::setPosition(int x, int y) {
	positionX = x;
	positionY = y;
	sprite.setPosition(positionX, positionY);
}
//Players attack
void Player::attack(Enemy *enemy) {
	// default attack damage
	
	enemy->takeDamage(damage);
	cout << "Player attacks enemy for " << damage << " damage!" << endl;
}
//Players block
void Player::block() {
	cout << "Player blocks!" << endl;
	blockDamage = true; // set block flag
}
//Players special attack
void Player::specialAttack(Enemy* enemy){
	int damage = 6; 
	enemy->takeDamage(damage);
	cout << "Player uses special attack on enemy for " << damage << " damage!" << endl;
}
//Player takes damage
void Player::takeDamage(int damage) {
	if (blockDamage) {
		damage /= 5; // reduce damage if blocking
		blockDamage = false; // reset block flag
		shield--;
	}
	this->health -= damage;

	cout << "Player takes " << damage << " damage!" << endl;
}