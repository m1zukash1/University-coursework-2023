#include "Bullet.h"

Bullet::Bullet(float rotation, sf::Vector2f startPosition)
{
	arrowTexture.loadFromFile("Sprites/Arrow.png");
	arrowTexture.setSmooth(true);
	arrowSprite.setTexture(arrowTexture);
	arrowSprite.setOrigin(arrowSprite.getLocalBounds().width / 2.f, arrowSprite.getLocalBounds().height / 2.f);
	arrowSprite.setRotation(rotation);
	arrowSprite.setPosition(startPosition);
}

void Bullet::update(sf::RenderWindow& window, sf::View& camera, float deltaTime, std::list<Bullet*>& bullets)
{

	if (lifeClock.getElapsedTime().asSeconds() >= gameplay::arrowLifeTime)
	{
		queueForDeletion = true;
		return;
	}

	float radians = arrowSprite.getRotation() * (3.14159265 / 180.0f);
	sf::Vector2f movement(std::cos(radians) * gameplay::arrowSpeed * deltaTime, std::sin(radians) * gameplay::arrowSpeed * deltaTime);
	arrowSprite.move(movement);

	window.draw(arrowSprite);
}