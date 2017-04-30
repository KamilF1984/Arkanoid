#pragma once
#include "Paddle.hpp"

class Brick : public Rectangle {

public:
	bool destroyed = false;
	Brick(sf:: Vector2f Position,sf:: Vector2f Size, sf::Color defColor);
	~Brick();
};



