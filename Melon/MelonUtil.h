
#pragma once

#include <random>
#include <cstdlib>

int randomInt(int min, int max)
{
    /*std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);

    return uni(rng);*/
    return min + (rand() % static_cast<int>(max - min + 1));
}

bool YesOrNo()
{
    return static_cast<bool>(randomInt(0, 1));
}

