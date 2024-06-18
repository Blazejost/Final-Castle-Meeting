#pragma once



class Map
{
public:
//Variables:
 
	//Window
	RenderWindow* target;

	//Player
	Player* player;

	//Levels
	Locations location;
	Level* level;
	int* currentLevel;

	//Size
	int height;
	int width;

	float tileSize;
	//float tileScale;

	//Tiles
	vector<vector<Tile>> tiles;

	//Sprites
	Sprite wallSprite;
	Texture wallTexture;

	Sprite emptySprite;
	Texture emptyTexture;

	Key* key;
	Texture keyTexture;

	Sprite lockSprite;
	Texture lockTexture;

	//Items
	vector<Item*> items;
	int itemAmount;

	//Inemies
	vector<Enemy*> enemies;
	int enemiesAmount;

public:
	//Tiles coordinates
	int startX;
	int startY;
	int endX;
	int endY;

	int secretX;
	int secretY;

	//Constructor
	Map(Level *level);
	~Map();

	//Basic functions
	void update();
	void render();

	//Functions
	void generateMap(int width, int height, int tileSize);
	void generateItems(vector <Item*> mapItems);

	void generateEnemies(vector<Enemy*> mapEnemies);

	void loadTileTextures();
};

