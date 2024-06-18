#pragma once

class Key
	: public Item
{


public:
	Level* level;
	Key(Level* level, Texture texture);
	~Key();

	void takeItem(Player* player);
	void useItem(Player* player);
};


