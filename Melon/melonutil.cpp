#include "MelonUtil.h"

int
randomInt(int min, int max)
{
    /*std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);

    return uni(rng);*/
    return min + (rand() % static_cast<int>(max - min + 1));
}

bool
probability(int percentageOfSuccess)
{
    return percentageOfSuccess >= randomInt(1, 100);
}
