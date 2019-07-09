#include <iostream>
#include <cstring>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Rect.hpp>

float enemySpeed = 0.1;

int main()
{
	sf::RenderWindow window(sf::VideoMode(750, 750), "Sprites!");

	//sprites
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
	goblinSprite.setOrigin(26, 16);
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

	sf::Clock batClock;
	int ImgCountBat = 0;
	float batTimer = 0;

	sf::Clock goblinClock;
	int imgCountGoblin = 0;
	float goblinTimer = 0;

	bool movingUp = false;
	bool movingDown = false;
	bool movingLeft = false;
	bool movingRight = false;
	bool batMoving = false;
	bool goblinMoving = false;

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
		//player speed
		sf::Vector2f movement(0, 0);
		if (movingUp)
			movement.y -= 0.25f;
		if (movingDown)
			movement.y -= -0.25f;
		if (movingLeft)
			movement.x -= 0.25f;
		if (movingRight)
			movement.x -= -0.25f;
		mySprite.move(movement);
		//animate on command
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

		//goblin ai
		if (mySprite.getPosition().x > goblinSprite.getPosition().x) {
			goblinSprite.move(enemySpeed, 0);
			goblinMoving = true;
		}
		else if (mySprite.getPosition().x < goblinSprite.getPosition().x) {
			goblinSprite.move(-enemySpeed, 0);
			goblinMoving = true;
		}
		else {
			goblinMoving = false;
		}

		if (mySprite.getPosition().y > goblinSprite.getPosition().y) {
			goblinSprite.move(0, enemySpeed);
			goblinMoving = true;
		}
		else if (mySprite.getPosition().y < goblinSprite.getPosition().y) {
			goblinSprite.move(0, -enemySpeed);
			goblinMoving = true;
		}
		else {
			goblinMoving = false;
		}
		if (goblinMoving) {
			goblinTimer = goblinClock.getElapsedTime().asSeconds();
			if (goblinTimer > 0.25f)
			{
				if (imgCountGoblin < 3)
					imgCountGoblin++;
				else
					imgCountGoblin = 0;
				goblinClock.restart();
			}
		}
		else
			imgCountGoblin = 0;

		
		//bat ai
		if (mySprite.getPosition().x > batSprite.getPosition().x) {
			batSprite.move(enemySpeed, 0);
			batMoving = true;
			if (mySprite.getScale().x > 0)
				mySprite.scale(-1, 1);
		}
		else if (mySprite.getPosition().x < batSprite.getPosition().x) {
			batSprite.move(-enemySpeed, 0);
			batMoving = true;
		}
		else {
			batMoving = false;
		}

		if (mySprite.getPosition().y > batSprite.getPosition().y) {
			batSprite.move(0, enemySpeed);
			batMoving = true;
		}
		else if (mySprite.getPosition().y < batSprite.getPosition().y) {
			batSprite.move(0, -enemySpeed);
			batMoving = true;
		}
		else {
			batMoving = false;
		}

		if (batMoving) {
			batTimer = batClock.getElapsedTime().asSeconds();
			if (batTimer > 0.25f)
			{
				if (ImgCountBat < 3)
					ImgCountBat++;
				else
					ImgCountBat = 0;
				batClock.restart();
			}
		}
		else
			ImgCountBat = 0;

		//animation on player movement code
		if (movingLeft || movingRight || movingUp || movingDown)
			mySprite.setTextureRect(rect[imgCount]);
		else
			mySprite.setTextureRect(rect[0]);
		//animation on bat movement code
		if (batMoving)
			batSprite.setTextureRect(bat[ImgCountBat]);
		else
			batSprite.setTextureRect(bat[0]);
		//animation on bat movement code
		if (goblinMoving)
			goblinSprite.setTextureRect(goblin[imgCountGoblin]);
		else
			goblinSprite.setTextureRect(goblin[0]);

		window.clear(sf::Color::Blue);
		window.draw(mySprite);
		window.draw(goblinSprite);
		window.draw(batSprite);
		window.display();
	}
}