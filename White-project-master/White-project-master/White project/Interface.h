#pragma once

class Interface
{
public:
	//Variables
	Player* player;

	int health;
	int money;
	int* currentLevel;

	RectangleShape statsPanel;

	Font font;

	Text healthText;
	Text moneyText;
	Text currentLevelText;

	//Constructor/Destructor
	Interface(Player* player);
	~Interface();

	//Functions
	void update(float dt);
	void render(RenderWindow* window);
};

