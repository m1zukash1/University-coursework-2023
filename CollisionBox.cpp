#include "CollisionBox.h"

CollisionBox::CollisionBox(sf::Vector2f position, sf::Vector2f size)
    : rect(sf::RectangleShape(size))
{
    rect.setPosition(position);
    rect.setFillColor(sf::Color(7, 10, 14, 255));
}

bool CollisionBox::checkCollision(EnemyBase& enemy)
{
    if (rect.getGlobalBounds().intersects(enemy.getRect().getGlobalBounds()))
    {
        sf::Vector2f enemyPosition = enemy.getPosition();
        sf::Vector2f enemyVelocity = enemy.getVelocity();

        sf::FloatRect rectBounds = rect.getGlobalBounds();
        sf::FloatRect enemyBounds = enemy.getRect().getGlobalBounds();

        float overlapX = std::min(rectBounds.left + rectBounds.width, enemyPosition.x + enemyBounds.width / 2.f)
            - std::max(rectBounds.left, enemyPosition.x - enemyBounds.width / 2.f);
        float overlapY = std::min(rectBounds.top + rectBounds.height, enemyPosition.y + enemyBounds.height / 2.f)
            - std::max(rectBounds.top, enemyPosition.y - enemyBounds.height / 2.f);

        if (overlapX > overlapY) {
            if (enemyPosition.y < rectBounds.top + rectBounds.height / 2.f)
            {
                enemyPosition.y -= overlapY;
            }
            else
            {
                enemyPosition.y += overlapY;
            }
            enemyVelocity.y = 0;
        }
        else {
            if (enemyPosition.x < rectBounds.left + rectBounds.width / 2.f)
            {
                enemyPosition.x -= overlapX;
            }
            else
            {
                enemyPosition.x += overlapX;
            }
            enemyVelocity.x = 0;
        }

        enemy.setPosition(enemyPosition);
        enemy.setVelocity(enemyVelocity);

        return true;
    }

    return false;
}


bool CollisionBox::checkCollision(Player& player)
{
    if (rect.getGlobalBounds().intersects(player.getRect().getGlobalBounds()))
    {
        sf::Vector2f playerPosition = player.getPosition();
        sf::Vector2f playerVelocity = player.getVelocity();
        sf::Vector2f playerDirection = player.getDirection();

        sf::FloatRect rectBounds = rect.getGlobalBounds();

        float overlapX = std::min(rectBounds.left + rectBounds.width, playerPosition.x + player.getRect().getSize().x / 2.f)
            - std::max(rectBounds.left, playerPosition.x - player.getRect().getSize().x / 2.f);
        float overlapY = std::min(rectBounds.top + rectBounds.height, playerPosition.y + player.getRect().getSize().y / 2.f)
            - std::max(rectBounds.top, playerPosition.y - player.getRect().getSize().y / 2.f);

        if (overlapX > overlapY) {
            if (playerPosition.y < rectBounds.top + rectBounds.height / 2.f)
            {
                playerPosition.y -= overlapY;
                playerVelocity.y = 0;
                playerDirection.y = -1;
            }
            else
            {
                playerPosition.y += overlapY;
                playerVelocity.y = 0;
                playerDirection.y = 1;
            }
        }
        else {
            if (playerPosition.x < rectBounds.left + rectBounds.width / 2.f)
            {
                playerPosition.x -= overlapX;
                playerVelocity.x = 0;
                playerDirection.x = -1;
            }
            else
            {
                playerPosition.x += overlapX;
                playerVelocity.x = 0;
                playerDirection.x = 1;
            }
        }

        player.setPosition(playerPosition);
        player.setVelocity(playerVelocity);
        player.setDirection(playerDirection);

        return true;
    }

    return false;
}

bool CollisionBox::checkCollision(Bullet& bullet)
{
    if (rect.getGlobalBounds().intersects(bullet.arrowSprite.getGlobalBounds()))
    {
        return true;
    }

    return false;
}

void CollisionBox::setPosition(sf::Vector2f pos)
{
    rect.setPosition(pos);
}

void CollisionBox::update(sf::RenderWindow& window)
{
    window.draw(rect);
}
