#include "Brick.hpp"


Brick::Brick(sf::Vector2f Position, sf::Vector2f Size, sf::Color defColor) {
	shape.setPosition(Position.x, Position.y);
	shape.setFillColor(defColor);
	shape.setSize(Size);
	shape.setOrigin(Size.x/2, Size.y/2);
	
}

Brick::~Brick()
{
}