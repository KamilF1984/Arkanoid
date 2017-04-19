//#pragma once
#ifndef GameState_hpp
#define GameState_hpp
#include <iostream>
//#include <limits>
#include "Brick.hpp"
//#include "Resource.h"
#include <vector>
//#include <algorithm>
//#include <time.h>
//#include <stdlib.h>
#include <array>
#include <tuple>

//const float videoHeight = 600;
//const float videoWidth = 800;

class GameState
{

private:
	enum class State { PAUSED, INPROGRESS };

	

	int countBlocksX = 11, countBlocksY = 4;
	float blockWidth = 60.f, blockHeight = 20.f;
	int iX, iY;

	sf::RenderWindow window{ sf::VideoMode{ videoWidth, videoHeight }, "Arkanoid" };
	sf::Event event;
	

	std::vector<Brick> bricks;

	// initialize current state
	State state{ State::INPROGRESS };
	bool pausePressed{ false };
	Ball ball{ 400, 450 };
	Paddle paddle { 400, 470 };
public:
	
	//Resource soundEffect;
	GameState()
	{
		window.setFramerateLimit(60);
	}
	~GameState() { };


	void restart();
	//void loadEverything();
	void run();


};
#endif