#include "Brick.hpp"


Brick::Brick(float x, float y) {
	shape.setPosition(x, y);
	shape.setFillColor(defColor);
	shape.setSize({ 60, 20 });
	shape.setOrigin(30, 10);
}

Brick::~Brick()
{
}