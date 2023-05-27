#include "EnemyCharger.h"

EnemyCharger::EnemyCharger(sf::Vector2f size, sf::Vector2f startPosition) : EnemyBase(size, startPosition)
{
	healthColor[3] = sf::Color(82, 255, 184, 255);
	healthColor[2] = sf::Color(197, 165, 7, 255);
	healthColor[1] = sf::Color(238, 46, 49, 255);

	texture[3].loadFromFile("Sprites/EnemyCharger/Charger3.png");
	texture[2].loadFromFile("Sprites/EnemyCharger/Charger2.png");
	texture[1].loadFromFile("Sprites/EnemyCharger/Charger1.png");

	texture->setSmooth(true);

	//sprite.setTexture(texture[3]);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);

	rect.setSize(size);
	rect.setFillColor(healthColor[3]);
	rect.setOrigin(rect.getLocalBounds().width / 2.f, rect.getLocalBounds().height / 2.f);
	rect.setPosition(startPosition);
}

void EnemyCharger::update(sf::RenderWindow& window, sf::View& camera, float deltaTime, std::list<EnemyBase*>& enemies, Player& player, std::list<CollisionBox*>& collisionBoxes, Map& mapInsantce)
{
    
    sf::Vector2f targetPos = player.getPosition();
    float dx = targetPos.x - rect.getPosition().x;
    float dy = targetPos.y - rect.getPosition().y;

    float targetAngle = atan2(dy, dx) * 180 / 3.14159265;

    float currentAngle = rect.getRotation();

    float interpolatedAngle = lerpAngle(currentAngle, targetAngle, gameplay::enemyLookLerp * deltaTime);

    float radians = rect.getRotation() * (3.14159265 / 180.0f);

    float distance = lenght(sf::Vector2f(dx, dy));

    if (raycastUpdateClock.getElapsedTime().asSeconds() > 0.0f)
    {
        raycastResult = raycast(player.getPosition(), collisionBoxes, window); //true = no direct sight, false = is direct sight (from enemy to player)
        raycastUpdateClock.restart();
    }

    switch (state)
    {
    case MOVING:
        targetPos = player.getPosition();
        if (raycastResult)
        {
            path = mapInsantce.findPath(rect.getPosition(), player.getPosition());
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

        dx = targetPos.x - rect.getPosition().x;
        dy = targetPos.y - rect.getPosition().y;
        targetAngle = atan2(dy, dx) * 180 / 3.14159265;

        currentAngle = rect.getRotation();
        interpolatedAngle = lerpAngle(currentAngle, targetAngle, gameplay::enemyLookLerp * deltaTime);

        rect.setRotation(interpolatedAngle);

        radians = rect.getRotation() * (3.14159265 / 180.0f);
        velocity = sf::Vector2f(std::cos(radians) * gameplay::enemySpeed * deltaTime, std::sin(radians) * gameplay::enemySpeed * deltaTime);
        rect.move(velocity);

        distance = lenght(sf::Vector2f(dx, dy));

        if (distance < 225 && !raycastResult)
        {
            state = AIMING;
            aimClock.restart();
        }

        break;

    case AIMING:

        if (raycastResult)
        {
            state = MOVING;
            aimClock.restart();
        }

        rect.setRotation(targetAngle);
        radians = rect.getRotation() * (3.14159265 / 180.0f);
        if (aimClock.getElapsedTime().asSeconds() >= 0.5f)
        {
            state = CHARGE;
            aimClock.restart();
        }
        break;
    case CHARGE:
        radians = rect.getRotation() * (3.14159265 / 180.0f);
        velocity = sf::Vector2f(std::cos(radians) * 1000 * deltaTime, std::sin(radians) * 1000 * deltaTime);
        rect.move(velocity);

        if (aimClock.getElapsedTime().asSeconds() >= 1)
        {
            state = MOVING;
        }
        break;
    }


	checkCollision(enemies);	

	window.draw(rect);
}
