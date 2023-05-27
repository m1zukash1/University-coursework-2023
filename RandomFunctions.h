#pragma once

#ifndef RANDOM_FUNCS_H
#define RANDOM_FUNCS_H

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <list>


namespace gameplay
{
	const float playerSpeed = 350.f;
	const float playerAcceleration = 3.75f;
	const float playerDashStrenght = 500.f;
	const float playerDashCooldown = 0.5f;
	const float playerFireRate = 0.5f;

	const float arrowSpeed = 1250.f;
	const float arrowLifeTime = 7.5f;
	const float arrowOffsetFromPlayer = 50.f;

	const float cameraSmoothing = 7.5f;
	const float mouseSmoothing = 7.5f;

	const float enemyLookLerp = 5.f;
	const float enemySpeed = 325.f;

	extern bool toggleDebug;
}


namespace settings
{

}

float lenght(sf::Vector2f source);
sf::Vector2f normalize(sf::Vector2f source);
float lerp(float a, float b, float t);
float lerpAngle(float a, float b, float t);
int randIntRange(int from, int to);
float randFloatRange(float from, float to);

#endif