#include "Player.h"

Player::Player(sf::Vector2f size)
{

    rect.setSize(sf::Vector2f(size.x, size.y));
    rect.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));

    bow.loadFromFile("Sprites/bowTestWhite.png");
    bow.setSmooth(true);
    bowSprite.setTexture(bow);
    bowSprite.setPosition(500, 500);
    bowSprite.setOrigin(0, bowSprite.getLocalBounds().height / 2.f);


    texture.loadFromFile("Sprites/player.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
}

Player::~Player()
{

}

sf::Vector2f Player::getPosition()
{
    return rect.getPosition();
    //return sprite.getPosition();
}
sf::Vector2f Player::getDirection()
{
    return direction;
}

void Player::handleMovement(float deltaTime)
{
    direction = sf::Vector2f(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        direction.x += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        direction.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        direction.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        direction.y += 1;
    }

    direction = normalize(direction);

    sf::Vector2f acceleration = direction * speed - velocity;
    acceleration *= gameplay::playerAcceleration;

    velocity += acceleration * deltaTime;

    rect.setPosition(rect.getPosition() + velocity * deltaTime);
    //sprite.setPosition(rect.getPosition() + velocity * deltaTime);

}



void Player::handleDash(sf::RenderWindow &window, float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (dashClock.getElapsedTime().asSeconds() >= gameplay::playerDashCooldown)
        {
            dashClock.restart();
            velocity += normalize(direction) * gameplay::playerDashStrenght;
        }
    }
}

void Player::handleMouseMovement(sf::RenderWindow& window, float deltaTime)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

    float targetAngle = std::atan2(worldPos.y - bowSprite.getPosition().y, worldPos.x - bowSprite.getPosition().x) * 180 / 3.14159265;
    float currentAngle = bowSprite.getRotation();

    float interpolatedAngle = lerpAngle(currentAngle, targetAngle, gameplay::mouseSmoothing * deltaTime);

    bowSprite.setRotation(interpolatedAngle);
    bowSprite.setPosition(getPosition());
}

void Player::handleCameraSmoothing(sf::RenderWindow &window, sf::View &camera, float deltaTime)
{
    sf::Vector2f distance = getPosition() - camera.getCenter();
    sf::Vector2f movement = distance * (gameplay::cameraSmoothing * deltaTime);
    camera.setCenter(camera.getCenter() + movement);

    window.setView(camera);
}

void Player::handleShooting(sf::RenderWindow& window, sf::View& camera, float deltaTime, std::list<Bullet*>& bullets)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (fireRateClock.getElapsedTime().asSeconds() >= gameplay::playerFireRate)
        {
            Bullet* bullet = new Bullet(bowSprite.getRotation(), getPosition());

            float radians = bowSprite.getRotation() * (3.14159265 / 180.0f);
            sf::Vector2f movement(std::cos(radians) * gameplay::arrowOffsetFromPlayer, std::sin(radians) * gameplay::arrowOffsetFromPlayer);
            bullet->arrowSprite.move(movement);


            bullets.push_back(bullet);

            fireRateClock.restart();
        }
    }
}

void Player::update(sf::RenderWindow& window, float deltaTime, sf::View &camera, std::list<Bullet*> &bullets)
{
    handleMovement(deltaTime);
    handleDash(window, deltaTime);
    handleMouseMovement(window, deltaTime);
    //handleCameraSmoothing(window, camera, deltaTime);
    handleShooting(window, camera, deltaTime, bullets);

    window.draw(rect);
    //window.draw(sprite);

    window.draw(bowSprite); 
}
