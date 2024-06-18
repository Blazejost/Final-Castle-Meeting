#pragma once



class Goblin :
    public Enemy
{
public:
	//Constructor/Destructor
	Goblin(Level* level, Texture texture, int health, int damage, int speed);
	~Goblin();
};

