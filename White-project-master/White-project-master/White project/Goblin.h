#pragma once



class Goblin :
    public Enemy
{
public:

	Goblin(Level* level, Texture texture, int health, int damage, int speed);
	~Goblin();
};

