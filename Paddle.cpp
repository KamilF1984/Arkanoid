#include "Paddle.hpp"
//#include "Globals.hpp"
//#include "stdafx.h"

//texture.loadFromFile("paddle.png"); 
//sprite.setTexture(texture);

Paddle:: Paddle(float x, float y) {
shape.setPosition(x, y);
shape.setFillColor(defColorRectFill);
shape.setSize({ rectangleWidth, rectangleHeight });
shape.setOrigin(rectangleWidth / 2, rectangleHeight / 2);

}


//sf::Texture Paddle::loadTexture() { return texture.loadFromFile("paddle.png"); }

/*void Paddle::loadSprite() {

  sprite.setTexture(texture);
}*/
float Rectangle::	left() { return shape.getPosition().x - shape.getSize().x / 2; }
float Rectangle::	right() { return shape.getPosition().x + shape.getSize().x / 2; }
float Rectangle::	top() { return shape.getPosition().y - shape.getSize().y / 2; }
float Rectangle::	bottom() { return shape.getPosition().y + shape.getSize().y / 2; }
float Rectangle::	x() { return shape.getPosition().x; }
float Rectangle::	y() { return shape.getPosition().y; }

void Paddle::  update() {


	shape.move(velocity.x * czas.asMilliseconds(), velocity.y*czas.asMilliseconds());
	if (sf:: Keyboard::isKeyPressed(sf:: Keyboard::Left) && left()>0)
		velocity.x = -rectangleVelocity;


	else   if (sf:: Keyboard::isKeyPressed(sf:: Keyboard::Right) && right() <videoWidth)
		velocity.x = rectangleVelocity;

	else
		velocity.x = 0;



}

void Paddle::resetPosition(){

	sf::Time::Zero;
	shape.setPosition(400, 470);

}
Paddle:: ~Paddle()
{
}