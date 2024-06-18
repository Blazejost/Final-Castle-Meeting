#include "stdafx.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Level.h"

Skeleton::Skeleton(Level* level, Texture texture, int health, int damage, int speed)
{
	this->level = level;

	this->health = health / 2;
	this->damage = damage * 1,5;
	this->speed = speed;

	this->texture = texture;
	this->sprite = Sprite(texture);
}

Skeleton::~Skeleton()
{
}
