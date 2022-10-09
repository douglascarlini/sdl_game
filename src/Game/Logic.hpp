#pragma once

#include "../Engine/Game.hpp"
#include "../Engine/ECS/Components.hpp"

class Logic
{
public:
    void init();
    void render();
    void update();
    int lvl() { return level; }
    void lvl(int n) { level = 1; }

private:
    int level;
};