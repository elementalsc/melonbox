#ifndef PROGRESSION_H
#define PROGRESSION_H

#include <vector>
#include <string>
#include "Chord.h"
#include "Modes.h"

class Progression
{
private:

    std::vector<Chord>  mChords     = {};
    Note                mScale      = NoDefinedNote;
    Mode                mMode       = NoDefinedMode;
    ModeType            mModeType   = NoDefinedModeType;

//=====================================================================================================================
// PRIVATE METHODS
//=====================================================================================================================

    void refreshChordsModeAndScale();

public:

//=====================================================================================================================
// CONSTRUCTORS
//=====================================================================================================================

    Progression()
    {}

    /*Progression(std::vector<Chord> iChords) :
        mChords(iChords)
    {}*/

    Progression(std::vector<Chord> iChords, Note iScale = C, Mode iMode = Ionian, ModeType iModeType = NaturalMode) :
        mChords(iChords),
        mScale(iScale),
        mMode(iMode),
        mModeType(iModeType)
    {}


//=====================================================================================================================
// VECTOR-LIKE METHODS
//=====================================================================================================================

    int  size();
    void removeChord(int wIndex);
    void insertChord(Chord iChord, int wIndex);
    Chord& operator[](int i){return mChords[i];}

    Progression& append(const Chord& iChord)
    {
        mChords.push_back(iChord);
        return *this;
    }

    // More of a utility... TODO: REMOVE THIS
    std::vector<int> indexList();

//=====================================================================================================================
// PUBLIC METHODS
//=====================================================================================================================

    // GET & SET
    std::vector<Chord>& getChords()
    {
        return mChords;
    }

    Note& getScale()
    {
        return mScale;
    }

    Mode& getMode()
    {
        return mMode;
    }

    ModeType& getModeType()
    {
        return mModeType;
    }
    Progression& setChords(std::vector<Chord> iChords)
    {
        mChords = iChords;
        refreshChordsModeAndScale();
        return *this;
    }

    Progression& setScale(Note iNote)
    {
        mScale = iNote;
        refreshChordsModeAndScale();
        return *this;
    }

    Progression& setMode(Mode iMode)
    {
        mMode = iMode;
        refreshChordsModeAndScale();
        return *this;
    }

    Progression& setModeType(ModeType iModeType)
    {
        mModeType = iModeType;
        refreshChordsModeAndScale();
        return *this;
    }

    // PRINTING METHODS

    // toString
    std::string toString();

    std::string printChords(Alteration sharpOrFlat = Sharp);

}; // class Progression

#endif // PROGRESSION_H
