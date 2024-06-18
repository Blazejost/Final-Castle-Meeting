#pragma once

class Interface
{
public:
	//Variables
	Player* player;

	int health;
	int money;
	//int experience;
	int* currentLevel;

	RectangleShape statsPanel;

	Font font;

	Text healthText;
	Text moneyText;
	//Text experienceText;
	Text currentLevelText;

	Interface(Player* player);
	~Interface();

	void update(float dt);
	void render(RenderWindow* window);
};

