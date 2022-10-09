#pragma once

struct Animation
{
    int index;
    int speed;
    int frames;
    bool repeat;

    Animation() {}
    Animation(int i, int f, int s, bool r)
    {
        index = i;
        speed = s;
        frames = f;
        repeat = r;
    }
};
