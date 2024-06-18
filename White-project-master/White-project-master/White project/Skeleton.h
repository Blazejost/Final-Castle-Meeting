#pragma once
class Skeleton
	: public Enemy
{
	public:
	Skeleton(Level* level, Texture texture, int health, int damage, int speed);
	~Skeleton();
};

