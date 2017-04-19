#include "GameState.hpp"
//#include "Globals.hpp"

float clamp(float value, float min, float max) {
	return std::max(min, std::min(max, value));
}

void CollisionPaddle(Ball &ball, Paddle &paddle) // AABB - Circle collision
{

	float distance = ball.x() - paddle.x();
	float percentage = distance / (paddle.shape.getSize().x / 2);
	float strength = 1.0;

	// Calculate AABB info (center, half-extents)
	//Vector2f BallCenter{ ball.shape.getPosition().x,ball.shape.getPosition().y };

	sf:: Vector2f BallCenter{ ball.x(),ball.y() };

	//Vector2f aabb_center{ paddle.shape.getPosition().x, paddle.shape.getPosition().y };

	sf:: Vector2f aabb_center{ paddle.x(), paddle.y() };

	sf:: Vector2f aabb_half_extents{ paddle.shape.getSize().x / 2, paddle.shape.getSize().y / 2 };


	// Get center point circle first 

	sf:: Vector2f  difference{ BallCenter.x - aabb_center.x,BallCenter.y - aabb_center.y };

	sf:: Vector2f clamped;
	clamped.x = clamp(difference.x, -aabb_half_extents.x, aabb_half_extents.x);
	clamped.y = clamp(difference.y, -aabb_half_extents.y, aabb_half_extents.y);
	// Add clamped value to AABB_center and we get the value of box closest to circle
	sf:: Vector2f closest{ aabb_center.x + clamped.x,aabb_center.y + clamped.y };
	// Retrieve vector between center circle and closest point AABB and check if length <= radius
	difference.x = closest.x - BallCenter.x;
	difference.y = closest.y - BallCenter.y;
	float length = sqrt(pow(difference.x, 2) + pow(difference.y, 2));
	if (length < ball.shape.getRadius())
	{
		ball.velocity.x = percentage * strength;
		ball.velocity.y = -1 * abs(ball.velocity.y);

	}
}

float Length(sf:: Vector2f & vector) { return sqrt(pow(vector.x, 2) + pow(vector.y, 2)); }

sf:: Vector2f NormalizeVector(sf:: Vector2f& vector) {
	return  vector / Length(vector);
}

float dot_product(sf:: Vector2f& vector1, sf:: Vector2f& vector2) {
	return vector1.x*vector2.x + vector1.y*vector2.y;
}


enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

Direction  VectorDirection(sf:: Vector2f target) {

	sf:: Vector2f normalizedDirection[4] = { { 0.0f,  1.0f } ,{ 1.0f,  0.0f },{ 0.0f,  -1.0f },{ -1.0f, 0.0f } };

	float max = 0.0f;
	int best_match = -1;

	for (int i = 0; i < 4; ++i)
	{
		float dot_p = dot_product(NormalizeVector(target), normalizedDirection[i]);

		if (dot_p > max)
		{
			max = dot_p;
			best_match = i;
		}

	}

	return (Direction)best_match;

}


typedef std:: tuple <bool, Direction,sf:: Vector2f> Collision;


Collision CollisionBrick(Ball &ball, Brick &brick) // AABB - Circle collision
{

	//Collision collision = CollisionPaddle(ball, paddle);
	// Calculate AABB info (center, half-extents)
	sf:: Vector2f BallCenter{ ball.x(),ball.y() };

	sf:: Vector2f aabb_center{ brick.x(), brick.y() };

	sf:: Vector2f aabb_half_extents{ brick.shape.getSize().x / 2, brick.shape.getSize().y / 2 };

	sf:: Vector2f  difference{ BallCenter.x - aabb_center.x,BallCenter.y - aabb_center.y };

	sf:: Vector2f clamped{ clamp(difference.x, -aabb_half_extents.x, aabb_half_extents.x),clamp(difference.y, -aabb_half_extents.y, aabb_half_extents.y) };

	sf:: Vector2f closest{ aabb_center.x + clamped.x,aabb_center.y + clamped.y };

	difference.x = closest.x - BallCenter.x;
	difference.y = closest.y - BallCenter.y;


	if (Length(difference) < ball.shape.getRadius())
		/*{
		ball.velocity.y *= -1;
		brick.destroyed = true;
		}*/
		return 	std:: make_tuple(true, VectorDirection(difference), difference);// to jest funckcja
	else
		return  std:: make_tuple(false, UP, sf:: Vector2f{ 0, 0 });

}

void DoCollisions(Ball &ball, Brick &brick) {

	Collision collision = CollisionBrick(ball, brick);
	float ballx = ball.shape.getPosition().x;
	float bally = ball.shape.getPosition().y;

	if (std:: get<0>(collision)) // If collision is true
	{
		brick.destroyed = true;
		Direction dir = std:: get<1>(collision);
		sf:: Vector2f diff_vector = std:: get<2>(collision);
		if (dir == LEFT || dir == RIGHT) {
			ball.velocity.x = -ball.velocity.x;
			float penetration = ball.shape.getRadius() - abs(diff_vector.x);
			if (dir == LEFT)
				ballx += penetration;
			else
				ballx -= penetration;
		}

		else // Vertical collision
		{
			ball.velocity.y = -ball.velocity.y; // Reverse vertical velocity
												// Relocate
			float penetration = ball.shape.getRadius() - abs(diff_vector.y);
			if (dir == UP)
				bally -= penetration; // Move ball back up
			else
				bally += penetration; // Move ball back down
		}



	}

}


/*void GameState::loadEverything()
{
	soundEffect.loadAudio2();
}*/


void GameState::restart()
{
	//soundEffect.audio[4]->play();
//	state = State::PAUSED;

	bricks.clear();
	

	
		for (iX = 0; iX < countBlocksX; ++iX) {
			for (iY = 0; iY < countBlocksY; ++iY)
				bricks.push_back({ (iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3) });//emplace_back ?

	}

	Ball   ball( 400,450 );
	Paddle paddle( 400,470 );

}


void::GameState::run()
{

	//Ball   ball(400, 450);
	//Paddle paddle(400, 470);
	
	//window.setMouseCursorVisible(false);
	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}


		

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
				{

					
					//soundEffect.audio[3]->play();
					if (!pausePressed)
					{
						if (state == State::PAUSED)
							state = State::INPROGRESS;
						else if (state == State::INPROGRESS)
							state = State::PAUSED;
					}
					pausePressed = true;
					
				}
				else pausePressed = false;



				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
					restart();

				// if not paused, then the game must be running, so we update.
				if (state != State::PAUSED)
				//if (state == State::INPROGRESS)
				{

			paddle.update();
			ball.update();

			//for (auto& brick : bricks) window.draw(brick.shape);//range loop //C++ 11 range-based for: for (auto& elem : container)/ auto oznacza,ze typ jest sprawdzany na podstawi elementów													//BallPaddleCollision(&ball, &paddle);
				CollisionPaddle(ball, paddle);
			for (auto& brick : bricks) DoCollisions(ball, brick);
			bricks.erase(remove_if(begin(bricks), end(bricks),//The erase–remove idiom is a common C++ technique to eliminate elements that fulfill a certain criterion//poczatek,koniec ,co usuwac
				[](const Brick  &p_brick)// operator lambda, const zaklada ze nie zmieni sie stan obiektu brick, np.ze nagle nie zmieni sie,ze jednak nie jest zniszczony.
			{
				return p_brick.destroyed;//usuwa zniszczone
			}),
				end(bricks));
				}
				// otherwise, just continously draw the same positions


			window.draw(ball.shape);
			window.draw(paddle.shape);

			for (auto& brick : bricks) window.draw(brick.shape);

			window.display();
			/*czas = zegar.getElapsedTime();
			zegar.restart().asMilliseconds();*/
			ball.czas = ball.zegar.getElapsedTime();
			ball.zegar.restart().asMilliseconds();
			paddle.czas = paddle.zegar.getElapsedTime();
			paddle.zegar.restart().asMilliseconds();
			
		
	}
}


