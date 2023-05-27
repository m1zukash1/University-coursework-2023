#pragma once
#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "EnemyBase.h"

class CollisionBox
{
private:
    sf::RectangleShape rect;

public:
    CollisionBox(sf::Vector2f position, sf::Vector2f size);
    bool checkCollision(Player& player);
    bool checkCollision(Bullet& bullet);
    bool checkCollision(EnemyBase& bullet);
    void setPosition(sf::Vector2f pos);
    void update(sf::RenderWindow& window);
    sf::RectangleShape getRect() { return rect; };
};


#endif