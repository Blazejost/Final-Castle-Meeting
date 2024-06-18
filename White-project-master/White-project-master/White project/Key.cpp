#include "stdafx.h"
#include "Level.h"
#include "Player.h"
#include "Inventory.h"
#include "Item.h"
#include "Key.h"

//Constructor
Key::Key(Level* level, Texture texture) {
	this->name = "key";
	this->texture = texture;

	isOnMap = false;
	used = false;

	sprite.setTexture(this->texture);
}

//Destructor
Key::~Key() {

}

//Player takes the key
void Key::takeItem(Player* player)
{
	player->hasKey = true;
	player->inventory->addItem(this);
	cout << "Player took key" << endl;
}

//Player uses key
void Key::useItem(Player* player)
{
	player->hasKey = false;
	used = true;

	cout << "Player used key" << endl;
}

