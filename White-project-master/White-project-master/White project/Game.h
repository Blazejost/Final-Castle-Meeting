#pragma once

//Game modes
enum class GameModes
{
	TRAVEL,
	FIGHT,
	TRADE,
	UPGRADE,
	INVENTORY,
	
	LOSE,
	WIN
};

//Locations
enum class Locations
{
	CITY,
	CASTLE_HALL,
	CASTLE_MIDDLE,
	CASTLE_STAIRS,
	CASTLE_PRINCESS_ROOM
};




//Game
class Game
{
public:
//Variables:
	//SFML objects
	RenderWindow* window;
	VideoMode videomode;
	Event event;

	Clock clock;
	float dt;

	Music music;
//Game logic:
	
	//Player
	Player* player;
	Texture playerTexture;
	Sprite playerSprite;

	//View
	View view;

	//Game mode
	GameModes gameMode;
	GameModes previousGameMode;
	bool pause;

	//Game world mechanics
	Locations location;

	int currentLevel;
	bool levelCompleted;
	Level* level;

	//Test
	bool editorMode;
	bool menu;

	//Initialization
	void initVariables();
	void initWindow();

	//Game processs

public:
	//constructor
	Game();
	//destructor
	virtual ~Game();

	//accessors
	const bool running() const;

	//functions
	void pollEvents();
	void update();
	void render();

	void checkGameProcess();
};

