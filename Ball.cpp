#include "Ball.hpp"
//#include "Globals.hpp"
//#include "stdafx.h"


Ball::Ball(float x, float y) {
	shape.setRadius(ballRadius);
	shape.setPosition(x, y);
	shape.setFillColor(defColorFill);
	shape.setOrigin(ballRadius, ballRadius);


}

float Circle::left() { return shape.getPosition().x - shape.getRadius(); }
float Circle::right() { return shape.getPosition().x + shape.getRadius(); }
float Circle::top() { return shape.getPosition().y - shape.getRadius(); }
float Circle::bottom() { return shape.getPosition().y + shape.getRadius(); }
float Circle::x() { return shape.getPosition().x; }
float Circle::y() { return shape.getPosition().y; }

void Ball::solveBoundCollisions()
{
	if (top() < 0)
		velocity.y = ballVelocity;
	//left
	if (left() < 0)
		velocity.x = ballVelocity;
	//bottom
	if (bottom() > videoHeight)
		velocity.y = -ballVelocity;
	//right
	if (right() > videoWidth)
		velocity.x = -ballVelocity;
}



void Ball::update()
{
	shape.move(velocity.x*czas.asMilliseconds(), velocity.y *czas.asMilliseconds());
	solveBoundCollisions();
	if (sf:: Keyboard::isKeyPressed(sf:: Keyboard::Up))
	{
		stuck = false;
		velocity.y = -ballVelocity;

	}

	if (stuck == true) {

		if (sf:: Keyboard::isKeyPressed(sf:: Keyboard::Left) && left() > 0 + rectangleWidth / 2 - ballRadius)
		{
			velocity.x = -ballVelocity;

		}

		else   if (sf:: Keyboard::isKeyPressed(sf:: Keyboard::Right) && right() < videoWidth - rectangleWidth / 2 + ballRadius)
		{
			velocity.x = ballVelocity;
		}

		else

		{
			velocity.x = 0;
			velocity.y = 0;
		}

	}
}

/*void Ball::draw(sf::RenderWindow &window)
{
window.draw(circle);
}*/


Ball::~Ball()
{
}