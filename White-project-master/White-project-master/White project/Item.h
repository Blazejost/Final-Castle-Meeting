#pragma once


class Item
{
public:
	//Position
	int positionX;
	int positionY;

	//Look
	Texture texture;
	Sprite sprite;

	//variables
	bool isOnMap;
	bool used;

	//Parameters
	string name;
	int value;

	//Constructors
	Item();
	Item(Texture texture);
	

	//Copy constructor
	Item(const Item& sItem);

	//Destructor
	virtual ~Item();
	//Functions
	virtual void takeItem(Player* player) = 0;
	virtual void useItem(Player* player) = 0;
    void setScale(float x, float y);
};

