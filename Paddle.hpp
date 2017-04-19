//#pragma once
#ifndef Paddle_hpp
#define Paddle_hpp
#include "Ball.hpp"


class Rectangle {

public:

	sf:: RectangleShape shape;

	virtual void update() {};


	float left();
	float right();
	float top();
	float bottom();
	float x();
	float y();




};

class Paddle : public Rectangle {

public:

	sf:: Vector2f velocity;
	const float rectangleWidth = 60;
	const float rectangleHeight = 20;

	Paddle(float x, float y);
	~Paddle();
	void update();
	sf::Clock zegar;
	sf::Time czas;
private:
	sf::Color defColorRectFill{ sf::Color::Red };
	float DTPositionx = 400;
	float DTPositiony = 450 + 20;
	sf::Vector2f position{ DTPositionx, DTPositiony };
	const float rectangleVelocity = 0.5;

};
#endif