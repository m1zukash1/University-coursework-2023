#pragma once
#ifndef MAP_H
#define MAP_H


#include <SFML/Graphics.hpp>
#include <deque>
//#include "CollisionBox.h"

class Map
{
public:

    /*
    Map(std::list<CollisionBox*> &collisionBoxes)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (map[i][j] == 1)
                {
                    collisionBoxes.push_back(new CollisionBox(sf::Vector2f(j * tileSize, i * tileSize), sf::Vector2f(tileSize, tileSize)));
                }
            }
        }
    }
    */

    const int map[24][24] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1},
    {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1},
    {1,0,0,0,0,1,1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };

    static const inline int tileSize = 128;

    static const inline int width = sizeof(map) / sizeof(map[0]);
    static const inline int height = sizeof(map[0]) / sizeof(int);

    sf::Vector2i worldToMap(sf::Vector2f pos)
    {
        return sf::Vector2i(static_cast<int>(pos.x / 128), static_cast<int>(pos.y / 128));
    }

    sf::Vector2f mapToWorld(sf::Vector2i pos)
    {
        return sf::Vector2f(static_cast<float>(pos.x * 128 + 64), static_cast<float>(pos.y * 128 + 64));
    }

    std::vector<sf::Vector2i> findPath(sf::Vector2f start, sf::Vector2f end)
    {
        std::vector<sf::Vector2i> path;

        sf::Vector2i mapStart = worldToMap(start);
        sf::Vector2i mapEnd = worldToMap(end);

        std::vector<std::vector<bool>> visited(24, std::vector<bool>(24, false));
        std::vector<std::vector<sf::Vector2i>> parent(24, std::vector<sf::Vector2i>(24, sf::Vector2i(-1, -1)));

        std::deque<sf::Vector2i> queue;
        queue.push_back(mapStart);
        visited[mapStart.x][mapStart.y] = true;

        std::vector<sf::Vector2i> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        //std::vector<sf::Vector2i> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };


        //std::cout << mapEnd.x << std::endl;
        //std::cout << mapEnd.y << std::endl << std::endl;

        //std::cout << map[mapEnd.x][mapEnd.y] << std::endl;

        while (!queue.empty())
        {
            sf::Vector2i current = queue.front();
            queue.pop_front();

            if (current == mapEnd)
            {
                while (parent[current.x][current.y] != sf::Vector2i(-1, -1))
                {
                    path.push_back(current);
                    current = parent[current.x][current.y];
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            for (const auto& dir : directions)
            {
                sf::Vector2i next(current.x + dir.x, current.y + dir.y);

                if (next.x >= 0 && next.x < 24 && next.y >= 0 && next.y < 24 && !visited[next.x][next.y] && map[next.y][next.x] == 0)
                {
                    queue.push_back(next);
                    visited[next.x][next.y] = true;
                    parent[next.x][next.y] = current;
                }
            }
        }

        return path;

    }
};

#endif 