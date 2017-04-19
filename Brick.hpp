//#pragma once
#ifndef Brick_hpp
#define Brick_hpp
#include "Paddle.hpp"

class Brick : public Rectangle {

public:
	bool destroyed = false;
	sf::Color defColor{ sf::Color::Blue };

	Brick(float x, float y);
	~Brick();


};
#endif