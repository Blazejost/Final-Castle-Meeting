#pragma once

//states of movement
enum class Controls
{
	IDLE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};



class Player
{

public:
	//Variables
	string name;

	Game* game;
	Interface* interface;

	//Stats
	int health;
	int maxHealth;;
	int damage;
	bool blockDamage;
	int shield;
	int energy;

	float velocity;

	int money;

	//inventory
	Inventory* inventory;
	bool hasKey;

	//Position of the player on the map.
	float positionX;
	float positionY;

	int positionXTile;
	int positionYTile;

	//Control keys
	Controls controls;

	//Window
	RenderWindow* window;
	
public:
	//Variables
	Texture texture;
	Sprite sprite;
	char sideLook;

	//Level*
	Level* level;
	Map* map;

	//constructor/destructor
	Player(Game* game, string name, Texture playerTexture);

	~Player();

	//functions
	void update();
	void render();

	void input();

	//Other functions
	void setPosition(int x, int y);

	void takeDamage(int damage);

	void attack(Enemy* enemy);

	void block();

	void specialAttack(Enemy* enemy);
};