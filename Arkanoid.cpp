// Arkanoid.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;


const float videoHeight = 600;
const float videoWidth = 800;
const float ballVelocity = 2.0;
const float ballRadius = 10;
const float rectangleWidth = 60;
const float rectangleHeight = 20;
const float rectangleVelocity = 2;
int countBlocksX = 11, countBlocksY = 4;
float blockWidth = 60.f, blockHeight = 20.f;
int iX, iY;
int z;

class Ball {

public:

	CircleShape shape;
	Vector2f velocity{ -ballVelocity, -ballVelocity };

	Ball(float x, float y) {
		shape.setRadius(ballRadius);
		shape.setPosition(x, y);
		shape.setFillColor(Color::Green);
		shape.setOrigin(ballRadius, ballRadius);
	}

	float left() { return shape.getPosition().x - shape.getRadius(); }
	float right() { return shape.getPosition().x + shape.getRadius(); }
	float top() { return shape.getPosition().y - shape.getRadius(); }
	float bottom() { return shape.getPosition().y + shape.getRadius(); }
	float x() { return shape.getPosition().x; }

	void update() {

		shape.move(velocity);
		//top
		if (top()< 0)
			velocity.y = ballVelocity;
		//left
		if (left()< 0)
			velocity.x = ballVelocity;
		//bottom
		if (bottom()> videoHeight)
			velocity.y = -ballVelocity;
		//right
		if (right()> videoWidth)
			velocity.x = -ballVelocity;
	}

};


class Rectangle {

public:

	RectangleShape shape;

	virtual void update() {};


	float left() { return shape.getPosition().x - shape.getSize().x / 2; }
	float right() { return shape.getPosition().x + shape.getSize().x / 2; }
	float top() { return shape.getPosition().y - shape.getSize().y / 2; }
	float bottom() { return shape.getPosition().y + shape.getSize().y / 2; }
	float x() { return shape.getPosition().x; }




};

class Paddle : public Rectangle {

public:

	Vector2f velocity;

	Paddle(float x, float y) {
		shape.setPosition(x, y);
		shape.setFillColor(Color::Red);
		shape.setSize(Vector2f(rectangleWidth, rectangleHeight));
		shape.setOrigin(rectangleWidth / 2, rectangleHeight / 2);

	}

	void update() {

		shape.move(velocity);
		if (Keyboard::isKeyPressed(Keyboard::Left) && left()>0)
			velocity.x = -rectangleVelocity;

		else   if (Keyboard::isKeyPressed(Keyboard::Right) && right() <videoWidth)
			velocity.x = rectangleVelocity;

		else
			velocity.x = 0;

	}

};


class Brick : public Rectangle {

public:
	bool destroyed= false;

	Brick(float x, float y) {
		shape.setPosition(x, y);
		shape.setFillColor(Color::Blue);
		shape.setSize(Vector2f(rectangleWidth, rectangleHeight));
		shape.setOrigin(rectangleWidth / 2, rectangleHeight / 2);
	}

	
};

/*This is going to be exactly the same as doing a pure intersect check, and unless it is done as a per-pixel update it isn't going to solve the problem.
An intersect check, as outlined by the OP, or as done by you, checks if one object has hit another
(as Trienco said, either of these is going to fail if the ball is moving too fast).
In order to get this to work perfectly you have to consider the previous position, calculate the path of the ball up until the point of collision, 
and then determine which side of the block the ball hit. If you can give details on how you're storing and updating your positions then I might
be able to help with a bit more detail. 
If the ball hits the right or left, you want it to bounce back right or left, so you reverse the X motion.
If the ball hits the top or bottom, you want it to bounce back up or down, so you reverse the Y motion.
If the ball hits a corner, you want it to bounce back diagonally, so you reverse both the X and Y motion.
The way to get it to behave perfectly is either to redraw upon every pixel of movement (an obscenely intensive thing to do in most circumstances),
or using vector math to determine if the path of the ball passed through an object, calculate point of impact, and react accordingly
Considering that this is for a breakout style game, even though the path based collision may seem more complicated, it would be simpler in the long run 
I think because it also reduces the need for consideration of how to react to multiple collisions. If you use intersect checking against two blocks together,
then there's a high likelihood that the ball is going to intersect with (for example) the bottom left corner of one block, and the bottom right corner of another, 
or even intersecting with 3 (or more) blocks.*/

void BallPaddleCollision(Ball *p_ball, Paddle *p_rect) {

	if( p_ball->top() <= p_rect->bottom() && p_ball->bottom() >= p_rect->top()  && p_ball->right()>=p_rect->left() && p_ball->left()<=p_rect->right())
//	if(	p_ball->bottom() >= p_rect->top() && p_ball->top() <= p_rect->bottom()  && p_ball->left()>= (p_rect->x()-p_rect->shape.getSize().x/4) && p_ball->right() <=(p_rect->x()+p_rect->shape.getSize().x/4 ))
	{
		p_ball->velocity.y *= -1;
	}
	
	/*else if(p_ball->bottom() >= p_rect->top() && p_ball->top() <= p_rect->bottom() && ( p_ball->left()>=p_rect->left() &&  p_ball->right() <= (p_rect->left() + p_rect->shape.getSize().x/4)) 
		&& (p_ball->right() <= p_rect->right() && p_ball->left() >= (p_rect->right() - p_rect->shape.getSize().x / 4)))
	{
		p_ball->velocity.y *= -1;
		p_ball->velocity.x *= -1;

	}

	/*else if (p_ball->bottom() >= p_rect->top() && p_ball->top() <= p_rect->bottom()  && p_ball->right() <= p_rect->right() && p_ball->left() >= (p_rect->right() - p_rect->shape.getSize().x / 4) )
	{
		p_ball->velocity.y *= -1;
		p_ball->velocity.x *= -1;

	}*/
	
	
}




void BallBrickCollision(Ball &r_ball, Brick &r_rect) {

	//if (p_rect.right() <= p_ball.right() && p_ball.left() >= p_rect.left() && p_rect.bottom()
	//	<= p_ball.top() && p_rect.top() >= p_ball.bottom())

	
	if( r_ball.top() <= r_rect.bottom() && r_ball.bottom() >= r_rect.top() && r_ball.right() >= r_rect.left() && r_ball.left() <= r_rect.x() )//&& r_ball.right()>=r_rect.left() && r_ball.left()<=r_rect.left())
		
	{
		r_ball.velocity.y *= -1;
		//r_ball.velocity.x *= -1;
		r_rect.destroyed = true;
	}

	

}




int main()
{
	RenderWindow window(VideoMode(videoWidth, videoHeight), "Arkanoid");
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	Ball ball(400, 300);

	Paddle paddle(400, 450);

	vector<Brick> bricks;// tworzę kontener(wektor), do którego wsadzam obiekty klasy Brick

	for (iX = 0; iX < countBlocksX; ++iX) {
		for (iY = 0; iY < countBlocksY; ++iY)
			bricks.push_back({ (iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3) });//
		
	}



	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		ball.update();
		paddle.update();
		window.clear();
		window.draw(ball.shape);
		window.draw(paddle.shape);
		for (auto& brick : bricks) window.draw(brick.shape);// C++ 11 range-based for: for (auto& elem : container)/ auto oznacza,ze typ jest sprawdzany na podstawi elementów
		BallPaddleCollision(&ball, &paddle);
		for (auto& brick : bricks) BallBrickCollision(ball, brick);
		bricks.erase(remove_if(begin(bricks), end(bricks),
			[](const Brick  &p_brick)
		{
			return p_brick.destroyed;
		}),
			end(bricks));
		window.display();
	}

	return 0;
}

