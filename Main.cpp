#include <SFML/Graphics.hpp>

const sf::Keyboard::Key controls[4] =
{
	sf::Keyboard::A,
	sf::Keyboard::Z,
	sf::Keyboard::Up,
	sf::Keyboard::Down
};

const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f;

sf::CircleShape ball;
sf::RectangleShape paddles[2];

void Init() 
{
	for (sf::RectangleShape& p : paddles) 
	{
		p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
	}

	ball.setRadius(ballRadius);
	ball.setOrigin(ballRadius / 2.f, ballRadius / 2.f);

	paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
	paddles[1].setPosition(gameWidth - paddleSize.x / 2.f, gameHeight / 2.f);

	ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);
}