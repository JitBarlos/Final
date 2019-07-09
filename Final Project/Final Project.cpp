#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Rect.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(750, 750), "Sprites!");

	sf::Sprite mySprite;
	sf::Texture myTexture;
	sf::IntRect rect[8];
	rect[0] = sf::IntRect(0, 0, 52, 56);
	rect[1] = sf::IntRect(52, 0, 52, 56);
	rect[2] = sf::IntRect(104, 0, 52, 56);
	rect[3] = sf::IntRect(0, 56, 52, 56);
	rect[4] = sf::IntRect(52, 56, 52, 56);
	rect[5] = sf::IntRect(104, 56, 52, 56);
	rect[6] = sf::IntRect(0, 112, 52, 56);
	rect[7] = sf::IntRect(52, 112, 52, 56);

	myTexture.loadFromFile("Texture/TPosingGuyFloatingR.png");

	mySprite.setTexture(myTexture);
	mySprite.setTextureRect(rect[0]);
	mySprite.setOrigin(26, 16);
	mySprite.setScale(3, 3);
	mySprite.setPosition(350, 350);

	sf::Sprite goblinSprite;
	sf::Texture goblinTexture;
	sf::IntRect goblin[4];
	goblin[0] = sf::IntRect(0, 0, 64, 64);
	goblin[1] = sf::IntRect(64, 0, 64, 64);
	goblin[2] = sf::IntRect(0, 64, 64, 64);
	goblin[3] = sf::IntRect(64, 64, 64, 64);

	goblinTexture.loadFromFile("Texture/GoblinWalking.png");

	goblinSprite.setTexture(goblinTexture);
	goblinSprite.setTextureRect(goblin[0]);
	goblinSprite.setOrigin(15, 16);
	goblinSprite.setScale(2, 2);
	goblinSprite.setPosition(100, 100);

	sf::Sprite batSprite;
	sf::Texture batTexture;
	sf::IntRect bat[4];
	bat[0] = sf::IntRect(0, 0, 64, 64);
	bat[1] = sf::IntRect(64, 0, 64, 64);
	bat[2] = sf::IntRect(0, 64, 64, 64);
	bat[3] = sf::IntRect(64, 64, 64, 64);

	batTexture.loadFromFile("Texture/BatEnemy.png");

	batSprite.setTexture(batTexture);
	batSprite.setTextureRect(bat[0]);
	batSprite.setOrigin(15, 16);
	batSprite.setScale(1.5, 1.5);
	batSprite.setPosition(300, 100);

	sf::Clock clock;
	int imgCount = 0;
	float timer = 0;
	bool movingUp = false;
	bool movingDown = false;
	bool movingLeft = false;
	bool movingRight = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();


			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W)
				{
					movingUp = true;
				}
				if (event.key.code == sf::Keyboard::A)
				{
					movingLeft = true;
					if (mySprite.getScale().x > 0)
						mySprite.scale(-1, 1);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					movingRight = true;
					if (mySprite.getScale().x < 0)
						mySprite.scale(-1, 1);
				}
				if (event.key.code == sf::Keyboard::S)
				{
					movingDown = true;
				}


			}


			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					movingUp = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					movingLeft = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					movingDown = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					movingRight = false;
				}
			}
		}
		sf::Vector2f movement(0, 0);
		if (movingUp)
			movement.y -= 0.1f;
		if (movingDown)
			movement.y -= -0.1f;
		if (movingLeft)
			movement.x -= 0.1f;
		if (movingRight)
			movement.x -= -0.1f;
		mySprite.move(movement);

		if (movingLeft || movingRight || movingUp || movingDown) {
			timer = clock.getElapsedTime().asSeconds();
			if (timer > 0.25f)
			{
				if (imgCount < 7)
					imgCount++;
				else
					imgCount = 0;
				clock.restart();
			}
		}
		else
			imgCount = 0;

		
		
		if (movingLeft || movingRight || movingUp || movingDown)
			mySprite.setTextureRect(rect[imgCount]);
		else
			mySprite.setTextureRect(rect[0]);

		window.clear(sf::Color::Green);
		window.draw(mySprite);
		window.draw(goblinSprite);
		window.draw(batSprite);
		window.display();
	}
}