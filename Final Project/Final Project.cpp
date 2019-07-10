#include <iostream>
#include <cstring>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <vector>

float goblinSpeed = 0.1;
float batSpeed = 0.12;
int playerHealth = 20;


int main()
{
	sf::RenderWindow window(sf::VideoMode(850, 850), "Sprites!");

	//sprites
	sf::Sprite middleBackround;
	sf::Texture middleBackroundTexture;
	sf::IntRect backOne[4];
	backOne[0] = sf::IntRect(0, 0, 32, 32);
	backOne[1] = sf::IntRect(32, 0, 32, 32);
	backOne[2] = sf::IntRect(0, 32, 32, 32);
	backOne[3] = sf::IntRect(32, 32, 32, 32);

	middleBackroundTexture.loadFromFile("Texture/MiddleBackround.png");

	middleBackround.setTexture(middleBackroundTexture);
	middleBackround.setTextureRect(backOne[0]);
	middleBackround.setOrigin(0, 0);
	middleBackround.setScale(26.55, 26.55);
	middleBackround.setPosition(0, 0);
	
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

	sf::Clock backgroundClock;
	int imgCountBackOn = 0;
	float backOneTimer = 0;
	
	sf::Clock clock;
	int imgCount = 0;
	float timer = 0;

	sf::Clock batClock;
	int ImgCountBat = 0;
	float batTimer = 0;

	sf::Clock goblinClock;
	int imgCountGoblin = 0;
	float goblinTimer = 0;

	sf::Clock goblinAttackClock;
	float goblinAttackTimer = 0;

	sf::Clock batAttackClock;
	float batAttackTimer = 0;

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
		//background One
		backOneTimer = backgroundClock.getElapsedTime().asSeconds();
		if (backOneTimer > 0.7f)
		{
			if (imgCountBackOn < 3)
				imgCountBackOn++;
			else
				imgCountBackOn = 0;
			backgroundClock.restart();
		}
		middleBackround.setTextureRect(backOne[imgCountBackOn]);

		//Collision for goblin fighting
		if (goblinSprite.getGlobalBounds().intersects(mySprite.getGlobalBounds())) {
		goblinAttackTimer = goblinAttackClock.getElapsedTime().asSeconds();

			if (goblinAttackTimer > 1.5) {
				playerHealth -= 2;
				goblinAttackClock.restart();
				std::cout << "hit";
				std::cout << playerHealth << std::endl;

			}
		}
		//Collision for bat fighting
		if (batSprite.getGlobalBounds().intersects(mySprite.getGlobalBounds())) {
			batAttackTimer = batAttackClock.getElapsedTime().asSeconds();

			if (batAttackTimer > 1.5)
			{
				playerHealth -= 2;
				batAttackClock.restart();
				std::cout << "hit";
				std::cout << playerHealth << std::endl;
			}
		}
		//Dead
		if (playerHealth == 0) {
			
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
			goblinSprite.move(goblinSpeed, 0);
			goblinMoving = true;
			if (goblinSprite.getScale().x > 0)
				goblinSprite.scale(-1, 1);
		}
		else if (mySprite.getPosition().x < goblinSprite.getPosition().x) {
			goblinSprite.move(-goblinSpeed, 0);
			goblinMoving = true;
			if (goblinSprite.getScale().x < 0)
				goblinSprite.scale(-1, 1);
		}
		else {
			goblinMoving = false;
		}

		if (mySprite.getPosition().y > goblinSprite.getPosition().y) {
			goblinSprite.move(0, goblinSpeed);
			goblinMoving = true;
		}
		else if (mySprite.getPosition().y < goblinSprite.getPosition().y) {
			goblinSprite.move(0, -goblinSpeed);
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
			batSprite.move(batSpeed, 0);
			batMoving = true;
		}
		else if (mySprite.getPosition().x < batSprite.getPosition().x) {
			batSprite.move(-batSpeed, 0);
			batMoving = true;
		}
		else {
			batMoving = false;
		}

		if (mySprite.getPosition().y > batSprite.getPosition().y) {
			batSprite.move(0, batSpeed);
			batMoving = true;
		}
		else if (mySprite.getPosition().y < batSprite.getPosition().y) {
			batSprite.move(0, -batSpeed);
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
		window.draw(middleBackround);
		window.draw(mySprite);
		window.draw(goblinSprite);
		window.draw(batSprite);
		window.display();
	}
}