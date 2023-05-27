#pragma once
#ifndef ENEMY_CHARGER_H
#define ENEMY_CHARGER_H
#include "EnemyBase.h"

class EnemyCharger : public EnemyBase
{

private:

	enum State
	{
		MOVING,
		AIMING,
		CHARGE
	};

	State state = MOVING;
	sf::Clock aimClock;

public:
	EnemyCharger(sf::Vector2f size, sf::Vector2f startPosition);
	void update(sf::RenderWindow& window, sf::View& camera, float deltaTime, std::list<EnemyBase*>& enemies, Player& player, std::list<CollisionBox*>& collisionBoxes, Map& mapInsantce);
};


#endif