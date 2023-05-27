#include "Player.h"
#include "Bullet.h"
#include "EnemyCharger.h"
#include "EnemyFollower.h"
#include "CollisionBox.h"
#include "Map.cpp"

int main()
{
    //srand(time(0));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kursinis", sf::Style::Default, settings);
    window.setFramerateLimit(0);

    sf::Clock deltaClock;
    sf::Clock fpsDisplayClock;

    std::list<Bullet*> bullets;
    std::list<EnemyBase*> enemies;

    std::list<CollisionBox*> collisionBoxes;

    sf::Font fontOpenSans;
    fontOpenSans.loadFromFile("Fonts/OpenSans.ttf");
    sf::Text infoBoardText("Press [ to spawn enemyFollower\nPress ] to spawn enemyCharger\n\nPress ; to toggle pathfinding and raycast debug info", fontOpenSans, 24);
    sf::Text debugBoardText("Enemies on screen: 0\n", fontOpenSans, 24);
    debugBoardText.setOrigin(0, debugBoardText.getGlobalBounds().height / 2);
    infoBoardText.setPosition(25, 25);
    debugBoardText.setPosition(25, window.getSize().y - debugBoardText.getGlobalBounds().height);

    Map mapInstance; //(collisionBoxes);

    Player player;
    player.setPosition(sf::Vector2f(2 * mapInstance.tileSize, 2 * mapInstance.tileSize));



    for (int i = 0; i < 0; i++)
    {
        enemies.push_back(new EnemyCharger(sf::Vector2f(48, 16), sf::Vector2f(mapInstance.tileSize * 11, mapInstance.tileSize * 12)));
    }

    for (int i = 0; i < 0; i++)
    {
        enemies.push_back(new EnemyFollower(sf::Vector2f(16, 48), sf::Vector2f(randIntRange(1152, mapInstance.tileSize * 16), randIntRange(1152, mapInstance.tileSize * 16))));
    }

    
    // MAP INIT
    for (int i = 0; i < mapInstance.height; i++)
    {
        for (int j = 0; j < mapInstance.width; j++)
        {
            if (mapInstance.map[i][j] == 1)
            {
                collisionBoxes.push_back(new CollisionBox(sf::Vector2f(j * mapInstance.tileSize, i * mapInstance.tileSize), sf::Vector2f(mapInstance.tileSize, mapInstance.tileSize)));
            }
        }
    }
    

    sf::View camera;
    sf::View hud;

    camera = window.getDefaultView();
    hud = window.getDefaultView();
    camera.setSize(sf::Vector2f(1920 * 1, 1080 * 1));
    hud.setSize(sf::Vector2f(1920, 1080));

    float mapWidth = mapInstance.width * mapInstance.tileSize;
    float mapHeight = mapInstance.height * mapInstance.tileSize;

    float viewHalfWidth = camera.getSize().x / 2;
    float viewHalfHeight = camera.getSize().y / 2;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::LBracket) // [
                {
                    enemies.push_back(new EnemyFollower(sf::Vector2f(16, 48), sf::Vector2f(randIntRange(1152, mapInstance.tileSize * 16), randIntRange(1152, mapInstance.tileSize * 16))));
                }
                else if (event.key.code == sf::Keyboard::RBracket) // ]
                {
                    enemies.push_back(new EnemyCharger(sf::Vector2f(48, 16), sf::Vector2f(mapInstance.tileSize * 11, mapInstance.tileSize * 12)));
                }
                else if (event.key.code == sf::Keyboard::Semicolon)
                {
                    gameplay::toggleDebug = !gameplay::toggleDebug;
                }
            }
        }

        float deltaTime = deltaClock.restart().asSeconds();
        float fps = 1.f / deltaTime;

        window.clear(sf::Color(14, 20, 28, 255));

        float cameraClampedX = std::clamp(player.getPosition().x, viewHalfWidth, mapWidth - viewHalfWidth);
        float cameraClampedY = std::clamp(player.getPosition().y, viewHalfHeight, mapHeight - viewHalfHeight);

        camera.setCenter(cameraClampedX, cameraClampedY);

        window.setView(camera);


        for (CollisionBox* box : collisionBoxes)
        {

            (*box).update(window);
            (*box).checkCollision(player);
            for (EnemyBase* enemy : enemies)
            {
                (*box).checkCollision((*enemy));
            }

            for (Bullet* bullet : bullets)
            {
                if ((*box).checkCollision((*bullet)))
                {
                    bullet->queueForDeletion = true;
                }
            }
            
        }

        player.update(window, deltaTime, camera, bullets);
        //std::cout << player.getPosition().x << std::endl;
        //std::cout << player.getPosition().y << std::endl << std::endl;
        
        
        
        for (EnemyBase* enemy : enemies)
        {
            for (Bullet* bullet : bullets)
            {
                if (bullet->arrowSprite.getGlobalBounds().intersects(enemy->rect.getGlobalBounds()))
                {
                    enemy->setDamage(1);
                }
            }
        }

        for (auto it = enemies.begin(); it != enemies.end();)
        {
            if ((*it)->queueForDeletion == true)
            {
                delete (*it);
                it = enemies.erase(it);
            }
            else
            {
                (*it)->update(window, camera, deltaTime, enemies, player, collisionBoxes, mapInstance);
                ++it;
            }
        }

        for (auto it = bullets.begin(); it != bullets.end();)
        {
            if ((*it)->queueForDeletion == true)
            {
                delete (*it);
                it = bullets.erase(it);
            }
            else
            {
                (*it)->update(window, camera, deltaTime, bullets);
                ++it;
            }
        }

        window.setView(hud);
        window.draw(infoBoardText);

        std::stringstream debugInfoString;

        debugInfoString << "Enemies on screen: " << enemies.size() << std::endl;
        debugInfoString << "Bullets on screen: " << bullets.size() << std::endl;
        debugBoardText.setString(debugInfoString.str());

        window.draw(debugBoardText);

        window.display();

        if (fpsDisplayClock.getElapsedTime().asSeconds() >= 0.25f)
        {
            window.setTitle("FPS: " + std::to_string(static_cast<int>(fps)));
            fpsDisplayClock.restart();
        }
    }

    return 0;
}