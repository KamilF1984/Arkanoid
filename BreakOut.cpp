// BreakOut.cpp : Defines the entry point for the console application.
//

#include "GameState.hpp"

void pause() { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }




int main()
{


	GameState game;
	//game.loadEverything();
	game.restart();
	game.run();

	return 0;

	

}

