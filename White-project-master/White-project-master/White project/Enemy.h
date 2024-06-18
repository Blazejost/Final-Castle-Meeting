#pragma once

class Enemy
{
public:
	Level* level;

	bool isDead = false;

	int health;
	int damage;
	int speed;

	Texture texture;
	Sprite sprite;

	char direction;
	float positionX;
	float positionY;

	float attackTimer; //Timer to control enemy's attack frequency
	const float attackDelay = 10.0f; // Delay between attacks (in seconds)

    bool blockDamage = false;

	Enemy();

	Enemy(Level* level, Texture texture, int health, int damage, int speed);
	virtual ~Enemy();

	Enemy(const Enemy& other);

	void update(float deltaTime);
	void move(float deltaTime);
	void startAttack(float deltaTime);

	bool canAttack();

	bool reverseDirection();

    void attack(Player* player);

	void block();

	void specialAttack(Player* player);

    //bool canSeeSpecialAttack() {
    //    return true; // enemy's special attack preparation is visible
    //}


	void takeDamage(int damage);

};

