#pragma once

class Application
{
private:
	//Variables:
		//Window
	RenderWindow* window;
	VideoMode videomode;

	//Time
	Clock clock;
	float dt; //Delta time

	//Components
	Menu* menu;
	Game* game;

	bool gameStarted = false;

	//Initialization functions
	void initVariables();

	void initWindow();
	void initMenu();
	void initGame();

public:
	//Constructor and destructor:
	Application();
	~Application();

	//Functions:
		//Run application
	void run();
	const bool running() const;

	//Update and render application
	void update(float dt);
	void render();

};

