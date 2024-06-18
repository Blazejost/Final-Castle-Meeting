
#pragma once
#include "Item.h"


class Heart
	: public Item
{
public:
	Level* level;
	//Constructor/Destructor
	Heart(Level* level, Texture texture, int value);
	~Heart();

	//Functions
	void takeItem(Player* player);
	void useItem(Player* player);
};

