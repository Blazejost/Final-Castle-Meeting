#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Interface.h"
#include "Level.h"
#include "Map.h"
#include "Inventory.h"
#include "Fight.h"

//Initialization
void Game::initVariables()
{
	//Music
	music.openFromFile("Music/Pixel 5.ogg");
	music.setLoop(true);
	music.setVolume(0); //*****
	music.play();


	//Init player
	playerTexture.loadFromFile("Images/AnimationSheet_Character.png", IntRect(0, 0, 32, 32));
	player = new Player(this, "Knight", playerTexture);
	player->velocity = 600;

	// Initialize the view with the window's size
	view.setSize(window->getSize().x, window->getSize().y);
	view.setCenter(player->positionX, player->positionY);

	//Init gamemode
	gameMode = GameModes::TRAVEL;
	pause = false;

	//Init location
	location = Locations::CASTLE_HALL;
	
	//Init level
	currentLevel = 1;
	levelCompleted = false;
	level = new Level(this);

	//Set player to level
	//level->setPlayer(player);
}

void Game::initWindow()
{
	//Create window
	videomode.height = 1000;
	videomode.width = 1200;
	window = new RenderWindow(videomode, "Simple game", Style::Titlebar | Style::Close);
}

//Constructor
Game::Game()
{
	//Initialization
	initWindow();
	initVariables();
}

//Destructor
Game::~Game()
{
	delete level; //Remove later
	delete player;
	delete window;
}

//Accessors
const bool Game::running() const {
	return window->isOpen();
}

//Functions

//Check for events and basic input
void Game::pollEvents() {
	//event polling
	while (window->pollEvent(event)) {
		switch(event.type) {

		//Close window
		case Event::Closed:
			window->close();
			break;

		case Event::KeyPressed:

			if (event.key.code == Keyboard::Escape) {
				window->close();
			}
		//Game pause
			if (!menu) {
				if (event.key.code == Keyboard::P) {
					if (!pause) {
						pause = true;
					}
					else {
						pause = false;
					}
				}
				if (event.key.code == Keyboard::I) {
					if (gameMode != GameModes::INVENTORY) {
						previousGameMode = gameMode;
						gameMode = GameModes::INVENTORY;
					}
					else {
						//gameMode = previousGameMode;
						gameMode = previousGameMode;
					}
				}

				//Edtor mode
				if (event.key.code == Keyboard::K) {
					if (!editorMode) {
						editorMode = true;
					}
					else {
						editorMode = false;
					}
				}

			}

			//Menu
			/*if (event.key.code == Keyboard::M) {
				if (!editorMode) {
					menu = true;
				}
				else {
					menu = false;
				}
			}
			break;*/
		}
	}
}

//Update game
void Game::update()
{
	//SFML events
	pollEvents();

	// Delta time calculation
	dt = clock.restart().asSeconds();;

	checkGameProcess();

	//Update game objects
	if (!pause) {
		//Update player

		
		// Update the view's center
		view.setCenter(player->positionX,  player->positionY);



		//Update travel mode
		switch (gameMode) {
		case GameModes::TRAVEL:
			level->update(dt);
			player->interface->update(dt);
			break;
		case GameModes::INVENTORY: 
			player->interface->update(dt);
			break;
		case GameModes::FIGHT:
			while (level->fightStarted){
				level->fight->update();
				if (level->fight->playerLost == true) {
					gameMode = GameModes::LOSE;
					level->fightStarted = false;
				}
			}
			if (!level->fight->playerLost == true) {
				delete level->fight;
				gameMode = GameModes::TRAVEL;
			}
			break;
		case GameModes::LOSE:
			break;
		}
	}
	view.setSize(window->getSize().x, window->getSize().y);
	//Set editor mode - TEST!!!!!!!!!!!!!!
	if (editorMode) {
		//view.setSize(window->getSize().x * 8, window->getSize().y * 8);
		player->hasKey = true;
		player->damage = 1000;
		player->health = 1000;
	}
	/*else {
		view.setSize(window->getSize().x, window->getSize().y);
		player->velocity = 400.f;
	}*/

	

}

//Render
void Game::render()
{
	/*
		@return void
			- clear old frame
			- render objects
			- display frame in window

		renders game objects
	*/

	
	window->clear();
	if (!menu){
		//Set view
		
		//Render game
		if (gameMode == GameModes::TRAVEL) {
			window->setView(view);
			level->renderLevel();
		}
		else if (gameMode == GameModes::INVENTORY) {
			window->setView(view);
			level->renderLevel();

			player->inventory->render(window);
		}
		else if (gameMode == GameModes::FIGHT) {
			view.setCenter(260, 230);
			view.setSize(600, 400);
			window->setView(view);
			level->fight->render(window);
		}
		else if (gameMode == GameModes::LOSE) {
			window->clear();
			Font font;
			Text loseText;
			font.loadFromFile("Fonts/Garton.ttf");
			loseText.setFont(font);
			loseText.setCharacterSize(40);
			loseText.setPosition(player->positionX - 100, player->positionY);
			loseText.setFillColor(Color::Red);
			loseText.setString("YOU LOSE!");

			window->setView(view);
			window->draw(loseText);
		}
		else if (gameMode == GameModes::WIN) {
			window->clear();
			Font font;
			Text loseText;
			font.loadFromFile("Fonts/Garton.ttf");
			loseText.setFont(font);
			loseText.setCharacterSize(40);
			loseText.setPosition(player->positionX - 100, player->positionY);
			loseText.setFillColor(Color::Red);
			loseText.setString("YOU WIN!");

			window->setView(view);
			window->draw(loseText);
		}

}


		player->interface->render(window);
		//Set window
		//window->setView(window->getDefaultView());

		// Display the rendered frame
		window->display();
	}


void Game::checkGameProcess()
{

	if (currentLevel == 3 ) {
		location = Locations::CASTLE_MIDDLE;
		/*currentLevel = 1;*/
		cout << "New location! " << endl;
	}

	if (currentLevel == 5 ) {
		location = Locations::CASTLE_STAIRS;
		/*currentLevel = 1;*/
		cout << "New location! " << endl;
	}
	if (currentLevel == 7 ) {
		gameMode = GameModes::WIN;

		cout << "You won! " << endl;
	}

	if(levelCompleted) {
		delete level;
		level = new Level(this);
		gameMode = GameModes::TRAVEL;

		currentLevel++;
		levelCompleted = false;
	}
}