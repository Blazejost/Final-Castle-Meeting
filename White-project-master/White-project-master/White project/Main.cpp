#include "stdafx.h"
#include "Game.h"

//Start program
int main()
{
	//init random seed
	srand(time(NULL));
	//init Game engine
	Game game;

	//Game loop
	while (game.running())
	{
		//Update
		game.update();
		//Render
		game.render();
	}

	//End program
	return 0;
}