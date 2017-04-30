#pragma once
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "GameState.hpp"



const unsigned int videoHeight = 600;
const unsigned int videoWidth = 800;
const unsigned int rectangleWidth = 60;


 static bool stuck = true;

class Circle
{
public:
	sf::CircleShape shape;
	virtual void update() { };

	float left();
	float right();
	float top();
	float bottom();
	float x();
	float y();


};

class Ball : public Circle//, GameState
{
public:
	Ball(float x, float y);
	~Ball();
	void  update();
	const float ballVelocity = 0.5;
	sf::Vector2f velocity{ -ballVelocity, -ballVelocity };
	float DTPositionx = 400.0f;
	float DTPositiony = 450.0f;
	sf::Vector2f position{ DTPositionx, DTPositiony };//w main.cpp uzyje wektora position zamiast "magic numbers"
	sf::Clock zegar;
	sf::Time czas;
	void resetPosition();
private:
	float ballRadius = 10;
	sf::Color defColorFill{ sf::Color::Green };
	void solveBoundCollisions();
};
