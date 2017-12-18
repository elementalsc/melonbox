#ifndef PROGRESSION_H
#define PROGRESSION_H

#include <vector>
#include <string>
#include "Chord.h"
#include "Modes.h"

class Progression
{
public:

    std::vector<Chord>  mChords;
    Note                mRoot;
    Note                mScale;
    Mode                mMode;

    Progression();
    Progression(std::vector<Chord> iChords);

    // Replication of vector functions
    Chord& operator[](int iIndex);
    int  size();
    void removeChord(int wIndex);
    void insertChord(Chord iChord, int wIndex);

    // Fluent chord appender
    Progression& append(const Chord& iChord)
    {
        mChords.push_back(iChord);
        return *this;
    }

    // Returns vector of "remaning chords" ({0,1,2,3}) for Harmony.h use
    std::vector<int> indexList();

    // toString
    std::string toString();

};

#endif // PROGRESSION_H
