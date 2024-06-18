#pragma once




class Level
{
public:
	//Window
	RenderWindow* target;

	//Game
	Game* game;

	//Player
	Player* player;
	GameModes* gamemode;

	Fight* fight;
	bool fightStarted;

	//Location
	Locations location;

	//Level
	int* currentLevel;

	Enemy* enemy;

	//Map
	Map* map;
	int tileSize;
	int newXTile;


	//Items
	int itemAmount;
	vector <Item*> mapItems;

	unsigned coinValue;
	Texture coinTexture;
	Texture heartTexture;

	//Enemies
	int enemiesAmount;
	vector <Enemy*> mapEnemies;

	Texture skeletonTexture;
	Texture goblinTexture;

	//Controls
	bool up;
	bool down;
	bool left;
	bool right;

	bool isActiveKey;

	//Constructor
	Level(Game* game);
	//Destructor
	virtual ~Level();

//Functions:
	//Update
	void update(float deltaTime);
	void updatePlayerAnimation(float deltaTime);
	void updateEnemies();
	//Input
	void input(float deltaTime);
	//Render
	void renderLevel();
	
	//Add items that will appear on map
	void addMapItems(int itemAmount);

	
	void addEnemies(int enemiesAmount);

	void nearPlayer();
	void takeItem(Item* item);

	//void animateEnemy(Enemy* enemy, float deltaTime);
};