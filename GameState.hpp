#pragma once
#include <iostream>
//#include <limits>
//#include "Brick.hpp"
//#include "Resource.h"
#include <vector>
//#include <algorithm>
//#include <time.h>
//#include <stdlib.h>
#include <array>
//#include <tuple>
#include "GameLevels.hpp"
#include <sstream>
//const float videoHeight = 600;
//const float videoWidth = 800;

class GameState: public GameLevel
{

private:
	enum class State { PAUSED, INPROGRESS };
	
	/*int countBlocksX = 11, countBlocksY = 4;
	float blockWidth = 60.f, blockHeight = 20.f;
	int iX, iY;*/

	sf::RenderWindow window{ sf::VideoMode{ videoWidth, videoHeight }, "Arkanoid" };
	sf::Event event;
	
	// initialize current state
	State state{ State::INPROGRESS };
	bool pausePressed{ false };
	

public:

	Ball ball{ 400, 450 };
	Paddle paddle{ 400, 470 };

	int lives = 5;

	
	//Resource soundEffect;
	GameState()
	{
		window.setFramerateLimit(60);
	}
	~GameState() { };


	//void restart();
	void loadMenu();
	void run();
	void gameOver();
	//void loadLevel();
	void printText();
	void lost();
	void HighScorerList();

};

