#pragma once



class Coin
	: public Item
{


public:
	Level* level;
	Coin(Level* level, Texture texture, int value);
	~Coin();

	void takeItem(Player* player);
	void useItem(Player * player);
};
