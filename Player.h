#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Bullet.h"
#include "RandomFunctions.h"

class Player
{
private:
    sf::RectangleShape rect;
    sf::Clock dashClock;
    sf::Clock fireRateClock;
    sf::Texture bow;
    sf::Sprite bowSprite;
    float speed = gameplay::playerSpeed;
    sf::Vector2f velocity = sf::Vector2f(0, 0);
    sf::Vector2f direction = sf::Vector2f(0, 0);
    sf::Sprite sprite;
    sf::Texture texture;
    void handleMovement(float deltaTime);
    void handleDash(sf::RenderWindow &window, float deltaTime);
    void handleMouseMovement(sf::RenderWindow &window, float deltaTime);
    void handleCameraSmoothing(sf::RenderWindow& window, sf::View &camera, float deltaTime);
    void handleShooting(sf::RenderWindow& window, sf::View& camera, float deltaTime, std::list<Bullet*>& bullets);

public:
    Player(sf::Vector2f size = sf::Vector2f(32, 32)); //constructor
    ~Player(); //destructor
    sf::Vector2f getPosition();
    sf::Vector2f getDirection();
    void update(sf::RenderWindow& window, float deltaTime, sf::View &camera, std::list<Bullet*> &bullets);



    sf::RectangleShape getRect() { return rect; };
    void setPosition(sf::Vector2f pos) { rect.setPosition(pos); };
    void setDirection(sf::Vector2f dir) { direction = dir; };
    void setVelocity(sf::Vector2f vel) { velocity = vel; };
    sf::Vector2f getVelocity() { return velocity; };
};

#endif
