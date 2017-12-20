#ifndef PROGRESSION_H
#define PROGRESSION_H

#include <vector>
#include <string>
#include "Chord.h"
#include "Modes.h"

class Progression
{
public:

    std::vector<Chord>  mChords = {};
    Note                mScale  = NoDefinedNote;
    Mode                mMode   = NoDefinedMode;

//=====================================================================================================================
// CONSTRUCTORS
//=====================================================================================================================

    Progression()
    {}

    Progression(std::vector<Chord> iChords) :
        mChords(iChords)
    {}

    Progression(std::vector<Chord> iChords, Note iScale, Mode iMode) :
        mChords(iChords),
        mScale(iScale),
        mMode(iMode)
    {}


//=====================================================================================================================
// REPLICATION OF VECTOR METHODS
//=====================================================================================================================

    Chord& operator[](int iIndex);
    int  size();
    void removeChord(int wIndex);
    void insertChord(Chord iChord, int wIndex);


//=====================================================================================================================
// BASIC HARMONIC STRUCTURAL UNIT
//=====================================================================================================================

    Progression& append(const Chord& iChord)
    {
        mChords.push_back(iChord);
        return *this;
    }


//=====================================================================================================================
// PUBLIC METHODS
//=====================================================================================================================

    // Returns vector of "remaning chords" ({0,1,2,3}) for Harmony.h use
    std::vector<int> indexList();

    // toString
    std::string toString();

}; // class Progression

#endif // PROGRESSION_H
