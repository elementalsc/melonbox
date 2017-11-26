#pragma once
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

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

int probHsuVariation = 0;
int probGenericSubstitutions = 0;
int probSecondaryDominant = 0;
int probModalMixture = 0;

bool Probability(int percentageOfSuccess)
{
    return percentageOfSuccess > randomInt(0, 99);
}

template <class T>
int randVectorIndex(vector<T>& iVector)
{
      return randomInt(0,iVector.size()-1);
}

template <class T, class V>
void removeEraseValue(vector<T>& oVector, V& valueToRemove)
{
    oVector.erase(std::remove(oVector.begin(),oVector.end(),valueToRemove),oVector.end());
}
