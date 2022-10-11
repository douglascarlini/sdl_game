#pragma once

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
};