#include "stdafx.h"
#include "Enemy.h"
#include "Goblin.h"
#include "Level.h"

Goblin::Goblin(Level* level, Texture texture, int health, int damage, int speed)
{
	this->level = level;
	this->health = health * 1,5;
	this->damage = damage / 2;
	this->speed = speed;

	this->texture = texture;
	this->sprite = Sprite(texture);
}

Goblin::~Goblin()
{
}
