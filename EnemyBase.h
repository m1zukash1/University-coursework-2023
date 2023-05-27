#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "Bullet.h"
#include "Player.h"
#include "RandomFunctions.h"
#include "Map.cpp"
#include <list>
#include <thread>
#include <future>

class CollisionBox;

class EnemyBase
{

protected:
	sf::Clock damageCooldown;
	int health = 3;
	sf::Color healthColor[3 + 1] = {};
	sf::Vector2f velocity;
	sf::Vector2f direction;

	sf::Texture texture[3 + 1];
	sf::Sprite sprite;

	std::thread rayThread;
	bool raycastResult = false;
	sf::Clock raycastUpdateClock;
	std::vector<sf::Vector2i> path;

public:
	sf::RectangleShape rect;
	bool queueForDeletion = false;
	EnemyBase(sf::Vector2f size, sf::Vector2f startPosition); //constructor
	virtual ~EnemyBase() {};
	virtual void update(sf::RenderWindow& window, sf::View& camera, float deltaTime, std::list<EnemyBase*>& enemies, Player& player, std::list<CollisionBox*> &collisionBoxes, Map &mapInsantce);
	virtual void setDamage(int damage);
	sf::Vector2f getVelocity() { return velocity; };
	void setVelocity(sf::Vector2f vel) { velocity = vel; };
	void setDirection(sf::Vector2f dir) { direction = dir; };
	sf::Vector2f getDirection() { return direction; };
	sf::RectangleShape getRect() { return rect; };
	sf::Vector2f getPosition() { return rect.getPosition(); };
	void setPosition(sf::Vector2f pos) { rect.setPosition(pos); };
	void checkCollision(std::list<EnemyBase*>& enemies);
	bool raycast(const sf::Vector2f& castTo, std::list<CollisionBox*> &collisionBoxes, sf::RenderWindow& window);
};


#endif