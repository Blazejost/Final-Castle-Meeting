#pragma once



class Coin
	: public Item
{


public:
	Level* level;
	//Constructor/Destructor
	Coin(Level* level, Texture texture, int value);
	~Coin();

	//Functions
	void takeItem(Player* player);
	void useItem(Player * player);
};
