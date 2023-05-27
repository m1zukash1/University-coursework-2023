#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "RandomFunctions.h"

class Bullet
{

private:
	sf::Texture arrowTexture;
	sf::Clock lifeClock;

public:
	bool queueForDeletion = false;
	Bullet(float rotation, sf::Vector2f startPosition);
	void update(sf::RenderWindow& window, sf::View& camera, float deltaTime, std::list<Bullet*>& bullets);
	sf::Sprite arrowSprite;
};

#endif
