#pragma once

class Enemy
{
public:
	//Variables
	Level* level;

	bool isDead = false;

	//enemy stats
	int health;
	int damage;
	int speed;

	//appearance
	Texture texture;
	Sprite sprite;

	char direction;
	//positions
	float positionX;
	float positionY;

	float attackTimer; //Timer to control enemy's attack frequency
	const float attackDelay = 10.0f; // Delay between attacks (in seconds)

    bool blockDamage = false;

	//Constructors
	Enemy();

	Enemy(Level* level, Texture texture, int health, int damage, int speed);
	virtual ~Enemy();

	Enemy(const Enemy& other);

	//Functions
	void update(float deltaTime);
	void startAttack(float deltaTime);

	bool reverseDirection();
    void attack(Player* player);

	void block();

	void specialAttack(Player* player);


	void takeDamage(int damage);

};

