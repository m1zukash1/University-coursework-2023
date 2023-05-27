#include "EnemyBase.h"
#include "CollisionBox.h"

EnemyBase::EnemyBase(sf::Vector2f size, sf::Vector2f startPosition)
{
	healthColor[3] = sf::Color(82, 255, 184, 255);
	healthColor[2] = sf::Color(197, 165, 7, 255);
	healthColor[1] = sf::Color(238, 46, 49, 255);

	rect.setSize(size);
	rect.setFillColor(healthColor[3]);
	rect.setOrigin(rect.getLocalBounds().width / 2.f, rect.getLocalBounds().height / 2.f);
	rect.setPosition(startPosition);
}

void EnemyBase::checkCollision(std::list<EnemyBase*>& enemies)
{
	for (auto& enemy : enemies)
	{
		if (enemy != this && rect.getGlobalBounds().intersects(enemy->getRect().getGlobalBounds()))
		{
			sf::Vector2f thisPos = getPosition();
			sf::Vector2f otherPos = enemy->getPosition();
			sf::Vector2f diff = thisPos - otherPos;
			float length = lenght(diff);
			if (length != 0)
			{
				sf::Vector2f push = (diff / length) * 0.5f;
				setPosition(thisPos + push);
				enemy->setPosition(otherPos - push);
			}
		}
	}
}

void EnemyBase::update(sf::RenderWindow& window, sf::View& camera, float deltaTime, std::list<EnemyBase*>& enemies, Player& player, std::list<CollisionBox*>& collisionBoxes, Map& mapInsantce)
{
	window.draw(rect);
}

void EnemyBase::setDamage(int damage)
{
	if (damageCooldown.getElapsedTime().asSeconds() < gameplay::playerFireRate)
	{
		return;
	}

	damageCooldown.restart();
	health -= damage;
	sprite.setTexture(texture[health]);
	rect.setFillColor(healthColor[health]);

	if (health <= 0)
	{
		queueForDeletion = true;
		return;
	}
}

bool EnemyBase::raycast(const sf::Vector2f& castTo, std::list<CollisionBox*>& collisionBoxes, sf::RenderWindow& window)
{
	float rayStep = 8.f;
	float raySize = 32.f;

	sf::Vector2f startPoint = getPosition();
	sf::Vector2f castDirection = castTo - startPoint;

	sf::Vector2f rayDirection = normalize(castDirection);
	float distance = std::hypot(castDirection.x, castDirection.y);

	sf::RectangleShape rayShape(sf::Vector2f(rayStep, raySize));
	rayShape.setRotation(atan2(rayDirection.y, rayDirection.x) * 180 / 3.14159265);
	rayShape.setFillColor(sf::Color::Red);
	rayShape.setPosition(startPoint);

	float currentStep = 0;

	float stepLength = std::hypot(rayDirection.x * rayStep, rayDirection.y * rayStep);

	while (currentStep <= distance)
	{
		if (gameplay::toggleDebug)
		{
			rayShape.setSize(sf::Vector2f(rayStep, 1.f));
			window.draw(rayShape);
			rayShape.setSize(sf::Vector2f(rayStep, raySize));
		}
		rayShape.move(rayDirection * rayStep);
		currentStep += stepLength;

		sf::Rect rayGlobalBounds = rayShape.getGlobalBounds();

		for (CollisionBox* box : collisionBoxes)
		{
			const sf::Rect<float>& boxGlobalBounds = box->getRect().getGlobalBounds();
			if (boxGlobalBounds.intersects(rayGlobalBounds))
			{
				return true;
			}
		}
	}

	return false;
}