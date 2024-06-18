
#pragma once
#include "Item.h"


class Heart
	: public Item
{
public:
	Level* level;
	Heart(Level* level, Texture texture, int value);
	~Heart();

	void takeItem(Player* player);
	void useItem(Player* player);
};

