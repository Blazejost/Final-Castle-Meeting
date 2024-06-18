#pragma once

class Key
	: public Item
{


public:
	Level* level;
	//Constructor/destructor
	Key(Level* level, Texture texture);
	~Key();

	//Functions
	void takeItem(Player* player);
	void useItem(Player* player);
};


