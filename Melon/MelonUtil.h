#ifndef MELONUTIL_H
#define MELONUTIL_H

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>

int randomInt(int min, int max);

bool Probability(int percentageOfSuccess);

template <class T>
int randVectorIndex(std::vector<T>& iVector)
{
      return randomInt(0,iVector.size()-1);
}

template <class T, class V>
void removeEraseValue(std::vector<T>& oVector, V& valueToRemove)
{
    oVector.erase(std::remove(oVector.begin(),oVector.end(),valueToRemove),oVector.end());
}

template <class T>
void insertAtIndex(std::vector<T>& oVector, int iIndex, T insertedValue)
{
    oVector.insert(oVector.begin() + iIndex, insertedValue);
}

template <class T>
std::vector<int> generateListOfIndex(std::vector<T>& iVector)
{
    std::vector<int> wReturnedVector;

    for(int i = 0; i < iVector.size(); ++i)
    {
        wReturnedVector.push_back(i);
    }

    return wReturnedVector;
}



#endif // MELONUTIL_H
