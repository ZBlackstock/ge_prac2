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

sf::Vector2f ball_velocity;
bool is_player1_serving = true;
const float initial_velocity_x = 100.f;
const float initial_velocity_y = 60.f;
const float velocity_multiplier = 1.1f;

void reset()
{
	paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
	paddles[1].setPosition(gameWidth - paddleSize.x / 2.f, gameHeight / 2.f);

	ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);
	ball_velocity = { (is_player1_serving ? initial_velocity_x : -initial_velocity_x), initial_velocity_y };
}

void init()
{
	for (sf::RectangleShape& p : paddles)
	{
		p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
	}

	ball.setRadius(ballRadius);
	ball.setOrigin(ballRadius / 2.f, ballRadius / 2.f);

	reset();
}

void update(float deltaTime)
{
	float player1_direction = 0.0f;
	float player2_direction = 0.0f;
	if (sf::Keyboard::isKeyPressed(controls[0]))
	{
		player1_direction--;
	}
	if (sf::Keyboard::isKeyPressed(controls[1]))
	{
		player1_direction++;
	}
	if (sf::Keyboard::isKeyPressed(controls[2]))
	{
		player2_direction--;
	}
	if (sf::Keyboard::isKeyPressed(controls[3]))
	{
		player2_direction++;
	}

	paddles[0].move(0.f, player1_direction * paddleSpeed * deltaTime);
	paddles[1].move(0.f, player2_direction * paddleSpeed * deltaTime);
	ball.move(ball_velocity * deltaTime);

	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

	if (by > gameHeight) 
	{
		ball_velocity.x *= velocity_multiplier;
		ball_velocity.y *= -velocity_multiplier;
		ball.move(sf::Vector2f(0.f, -10.f));
	}
	else if (by < 0)
	{
		ball_velocity.x *= velocity_multiplier;
		ball_velocity.y *= -velocity_multiplier;
		ball.move(sf::Vector2f(0.f, 10.f));
	}
	else if (bx > gameWidth)
	{
		reset();
	}
	else if (bx < 0)
	{
		reset();
	}
	else if (bx < paddleSize.x + paddleOffsetWall
		&& by > paddles[0].getPosition().y - (paddleSize.y * 0.5)
		&& by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
	{
		ball_velocity.x *= -velocity_multiplier;
		ball_velocity.y *= velocity_multiplier;
		ball.move(sf::Vector2f(10.f, 0.f));
	}
	else if (bx > gameWidth - (paddleSize.x + paddleOffsetWall)
		&& by > paddles[1].getPosition().y - (paddleSize.y * 0.5)
		&& by < paddles[1].getPosition().y + (paddleSize.y * 0.5))
	{
		ball_velocity.x *= -velocity_multiplier;
		ball_velocity.y *= velocity_multiplier;
		ball.move(sf::Vector2f(-10.f, 0.f));
	}
}

void render(sf::RenderWindow& window)
{
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode({ gameWidth,gameHeight }), "Pong");
	init();

	while (window.isOpen())
	{
		static sf::Clock clock;
		const float deltaTime = clock.restart().asSeconds();

		window.clear();
		update(deltaTime);
		render(window);
		sf::sleep(sf::seconds(time_step));
		window.display();
	}

	return 0;
}

