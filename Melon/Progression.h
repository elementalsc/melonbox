#ifndef PROGRESSION_H
#define PROGRESSION_H

#include <vector>
#include <string>
#include "Chord.h"

class Progression
{
    std::vector<Chord> mChords;

public:
    Progression();
    Progression(Chord iChords...);

    // Replication of vector functions
    Chord& operator[](int iIndex);
    int  size();
    void removeChord(int wIndex);
    void insertChord(Chord iChord, int wIndex);

    // Fluent chord appender
    Progression& append(Chord& iChord);

    // Returns vector of "remaning chords" ({0,1,2,3}) for Harmony.h use
    std::vector<int> indexList();

    // toString
    std::string toString();

};

#endif // PROGRESSION_H
