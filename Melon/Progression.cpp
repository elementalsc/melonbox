#include "Progression.h"

Progression::Progression(){}

Progression::Progression(Chord iChords...)
{
    for(auto chord : iChords)
    {
        mChords.push_back(chord);
    }
}

Chord& Progression::operator[](int iIndex)
{
    return mChords[iIndex];
}

int Progression::size()
{
    return mChords.size();
}

void Progression::removeChord(int wIndex)
{
    mChords.erase(mChords.begin() + (wIndex), mChords.end());
}

void Progression::insertChord(Chord iChord, int wIndex)
{
    mChords.insert(mChords.begin() + wIndex, iChord);
}

Progression& Progression::append(Chord& iChord)
{

}

std::string Progression::toString()
{
    std::string oString;

    for (Chord chord : mChords)
    {
        oString.append(chord.toString());
        oString.append(" - ");
    }

    return oString.substr(0, oString.size() - 3);

}

std::vector<int> Progression::indexList()
{
    std::vector<int> wReturnedVector;

    for(int i = 0; i < mChords.size(); ++i)
    {
        wReturnedVector.push_back(i);
    }

    return wReturnedVector;
}
