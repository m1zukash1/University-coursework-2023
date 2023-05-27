#include "EnemyFollower.h"

#include<algorithm>
#include<deque>

EnemyFollower::EnemyFollower(sf::Vector2f size, sf::Vector2f startPosition) : EnemyBase(size, startPosition)
{
	healthColor[3] = sf::Color(82, 255, 184, 255);
	healthColor[2] = sf::Color(197, 165, 7, 255);
	healthColor[1] = sf::Color(238, 46, 49, 255);

	rect.setSize(size);
	rect.setFillColor(healthColor[3]);
	rect.setOrigin(rect.getLocalBounds().width / 2.f, rect.getLocalBounds().height / 2.f);
	rect.setPosition(startPosition);
}

bool once = false;

void EnemyFollower::update(sf::RenderWindow& window, sf::View& camera, float deltaTime, std::list<EnemyBase*>& enemies, Player& player, std::list<CollisionBox*>& collisionBoxes, Map& mapInsantce)
{
    sf::Vector2f targetPos = player.getPosition();

    if (raycastUpdateClock.getElapsedTime().asSeconds() > 0.25f)
    {
        raycastResult = raycast(player.getPosition(), collisionBoxes, window); //true = no direct sight, false = is direct sight (from enemy to player)
        if (raycastResult)
        {
            path = mapInsantce.findPath(rect.getPosition(), player.getPosition());
        }
        raycastUpdateClock.restart();
    }

    if (!path.empty() && raycastResult)
    {
        targetPos = mapInsantce.mapToWorld(*path.begin());
    }

    if (gameplay::toggleDebug)
    {
        for (sf::Vector2i pos : path)
        {
            sf::CircleShape shape(16);
            shape.setOrigin(16, 16);

            sf::Vector2f _pos = mapInsantce.mapToWorld(pos);

            shape.setPosition(_pos.x, _pos.y);
            window.draw(shape);
        }
    }
    //std::cout << (*path.rbegin()).x << std::endl;
    //std::cout << (*path.rbegin()).y << std::endl << std::endl;

	float dx = targetPos.x - rect.getPosition().x;
	float dy = targetPos.y - rect.getPosition().y;

	float targetAngle = atan2(dy, dx) * 180 / 3.14159265;

	float currentAngle = rect.getRotation();

	float interpolatedAngle = lerpAngle(currentAngle, targetAngle, gameplay::enemyLookLerp * deltaTime);

	rect.setRotation(interpolatedAngle);

	float radians = rect.getRotation() * (3.14159265 / 180.0f);
	velocity = sf::Vector2f(std::cos(radians) * gameplay::enemySpeed * deltaTime, std::sin(radians) * gameplay::enemySpeed * deltaTime);
	rect.move(velocity);

	checkCollision(enemies);
    window.draw(rect);
}