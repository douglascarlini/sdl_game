#pragma once

#include "../Engine/Game.hpp"
#include <iostream>
#include <fstream>

class Util
{
public:
    template <typename T>
    static void echo(T v)
    {
        std::cout << v << std::endl;
    }

    static bool file_exists(const char *path)
    {
        std::ifstream file(path);
        return file.is_open();
    }

    static double distance(Vector2D p1, Vector2D p2)
    {
        double dx = abs(p1.x - p2.x);
        double dy = abs(p1.y - p2.y);
        return sqrt((dx * dx) + (dy * dy));
    }

    static bool out_bounds(Vector2D p)
    {
        return (p.x > Game::camera.x + Game::camera.w ||
                p.y > Game::camera.y + Game::camera.h ||
                p.x < Game::camera.x ||
                p.y < Game::camera.y);
    }
};