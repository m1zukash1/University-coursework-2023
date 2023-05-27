#pragma once
#ifndef ENEMY_FOLLOWER_H
#define ENEMY_FOLLOWER_H
#include "EnemyBase.h"

class EnemyFollower : public EnemyBase
{

private:

public:
	EnemyFollower(sf::Vector2f size, sf::Vector2f startPosition);
	void update(sf::RenderWindow& window, sf::View& camera, float deltaTime, std::list<EnemyBase*>& enemies, Player& player, std::list<CollisionBox*>& collisionBoxes, Map& mapInsantce);
};


#endif