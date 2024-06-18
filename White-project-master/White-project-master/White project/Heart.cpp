#include "stdafx.h"
#include "Heart.h"
#include "Level.h"
#include "Player.h"

//Constructor
Heart::Heart(Level* level, Texture texture, int value) {
	this->name = "heart";
	this->level = level;
	this->texture = texture;
	this->value = value;

	isOnMap = false;
	used = false;

	sprite.setTexture(this->texture);
}

//Destructor
Heart::~Heart() {

}

//Player takes heart
void Heart::takeItem(Player* player)
{
	useItem(player);
}

//Player uses heart
void Heart::useItem(Player* player)
{
	//If player has less than maxHealth, gets plus 1 heart
	if (player->health < player->maxHealth) {
		level->player->health += value;
		used = true;
	}
	cout << "Increse health by " << value << endl;
}