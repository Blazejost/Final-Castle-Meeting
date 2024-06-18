#include "stdafx.h"
#include "Item.h"
#include "Coin.h"
#include "Level.h"
#include "Player.h"


Coin::Coin(Level* level, Texture texture, int value) {
	this->name = "coin";
	this->level = level;
	this->value = value;
	this->texture = texture;

	isOnMap = false;
	used = false;

	sprite.setTexture(this->texture);
}

Coin::~Coin() {

}

void Coin::takeItem(Player* player)
{
	useItem(player);
	
	cout << "take coin" << endl;
}
void Coin::useItem(Player* player)
{
	level->player->money += value;
	used = true;

	cout << player->money << endl;
}
#pragma once

#include "Item.h"
#include "Level.h"


