#ifndef CHORD_H
#define CHORD_H

#include <string>
#include <vector>

#include "Modes.h"

enum Note
{
    NoDefinedNote = -1,
    C   = 0,
    Cs  = 1,
    Db  = 1,
    D   = 2,
    Ds  = 3,
    Eb  = 3,
    E   = 4,
    F   = 5,
    Fs  = 6,
    Gb  = 6,
    G   = 7,
    Gs  = 8,
    Ab  = 8,
    A   = 9,
    As  = 10,
    Bb  = 10,
    B   = 11
};

enum Triad
{
    NoDefinedTriad		= 0,
    MajorTriad,
    MinorTriad,
    DiminishedTriad,
    AugmentedTriad
};

enum Seventh
{
    NoSeventh			= 0,
    MajorSeventh,
    MinorSeventh,
    DiminishedSeventh
};

enum AddedDegree
{
    NoAddedDegree		= 0,
    Add6				= 6,
    Add9				= 9,
    Add11				= 11,
    Add13				= 13
};

enum SuspendedDegree
{
    NoSuspendedDegree	= 0,
    Sus2				= 2,
    Sus4				= 4
};

enum Alteration
{
    NoAlteration		= 0,
    Flat				=-1,
    Sharp				= 1
};

enum Inversion
{
    Root				= 0,
    First				= 1,
    Six					= 1,
    Second				= 2,
    SixFour				= 2,
    Third				= 3
};

enum SecondaryDegree
{
    NoSecondaryDegree	= 0,
    IV					= 4,
    V					= 5,
    VII					= 7
};

static Triad mNaturalTriads[7] = // Natural triads
{
    Triad::MajorTriad,
    Triad::MinorTriad,
    Triad::MinorTriad,
    Triad::MajorTriad,
    Triad::MajorTriad,
    Triad::MinorTriad,
    Triad::DiminishedTriad
};

static Triad mHarmonicTriads[7] = // Harmonic triads
{
    Triad::AugmentedTriad,
    Triad::MinorTriad,
    Triad::MajorTriad,
    Triad::MajorTriad,
    Triad::DiminishedTriad,
    Triad::MinorTriad,
    Triad::DiminishedTriad
};

class Chord
{

private:

    int              mDegree             = 0;
    std::vector<int> mNotes              = {};
    Note             mRoot               = NoDefinedNote;
    Note             mScale              = NoDefinedNote;
    Mode             mMode               = NoDefinedMode;
    ModeType         mModeType           = NoDefinedModeType;
    Triad            mTriad              = NoDefinedTriad;
    Inversion        mInversion          = Root;
    Alteration       mAlteration         = NoAlteration;
    SuspendedDegree  mSuspendedDegree	 = NoSuspendedDegree;
    AddedDegree      mAddedDegree        = NoAddedDegree;
    SecondaryDegree  mSecondaryDegree	 = NoSecondaryDegree;
    MelonLogger*     logger              = logger->getInstance();

public:


    virtual ~Chord() = default;

//=====================================================================================================================
// CONSTRUCTORS
//=====================================================================================================================

    Chord() {}

    Chord(int iDegree) :
        mDegree(iDegree)
    {}

    Chord(int iDegree, Triad iTriad) :
        mDegree(iDegree),
        mTriad(iTriad)
    {}

    Chord(int iDegree, Inversion iInversion) :
        mDegree(iDegree),
        mInversion(iInversion)
    {}

    Chord(int iDegree, Triad iTriad, Alteration iAlteration) :
        mDegree(iDegree),
        mTriad(iTriad),
        mAlteration(iAlteration)
    {}

    Chord(int iDegree, Triad iTriad, Inversion iInversion) :
        mDegree(iDegree),
        mTriad(iTriad),
        mInversion(iInversion)
    {}

    Chord(int iDegree, Triad iTriad, Inversion iInversion, Alteration iAlteration) :
        mDegree(iDegree),
        mTriad(iTriad),
        mInversion(iInversion),
        mAlteration(iAlteration)
    {}

//=====================================================================================================================
//	GET & SET
//=====================================================================================================================

    Chord& setScale(Note& iNote)
    {
        mScale = iNote;
        return *this;
    }

    Note& getScale()
    {
        return mScale;
    }

    int& getDegree()
    {
        return mDegree;
    }

    Chord& setRoot(Note& iNote)
    {
        mRoot = iNote;
        return *this;
    }

    Note& getRoot()
    {
        return mRoot;
    }

    Chord& setMode(Mode& iMode)
    {
        mMode = iMode;
        return *this;
    }

    Mode& getMode()
    {
        return mMode;
    }


    Chord& setModeType(ModeType& iModeType)
    {
        mModeType = iModeType;
        return *this;
    }

    ModeType& getModeType()
    {
        return mModeType;
    }

    Chord& setTriad(Triad& iTriad)
    {
        mTriad = iTriad;
        return *this;
    }

    Triad& getTriad()
    {
        return mTriad;
    }

    Chord& setInversion(Inversion& iInversion)
    {
        mInversion = iInversion;
        return *this;
    }

    Inversion& getInversion()
    {
        return mInversion;
    }

    Chord& setAlteration(Alteration& iAlteration)
    {
        mAlteration = iAlteration;
        return *this;
    }

    Alteration& getAlteration()
    {
        return mAlteration;
    }

    Chord& setAdd(AddedDegree& iAddedDegree)
    {
        mAddedDegree = iAddedDegree;
        return *this;
    }

    AddedDegree& getAdd()
    {
        return mAddedDegree;
    }

    Chord& setSus(SuspendedDegree& iSuspendedDegree)
    {
        mSuspendedDegree = iSuspendedDegree;
        return *this;
    }

    SuspendedDegree& getSus()
    {
        return mSuspendedDegree;
    }

    Chord& setSecondaryDegree(SecondaryDegree& iSecondaryDegree)
    {
        mSecondaryDegree = iSecondaryDegree;
        return *this;
    }

    Chord& setSecondaryDegree(SecondaryDegree&& iSecondaryDegree)
    {
        mSecondaryDegree = std::move(iSecondaryDegree);
        return *this;
    }

    SecondaryDegree& getSecondaryDegree()
    {
        return mSecondaryDegree;
    }

//=====================================================================================================================
//	OPERATORS
//=====================================================================================================================

    bool operator==(const Chord& other) const
    {
        if (
            mDegree             == other.mDegree &&
            mTriad              == other.mTriad &&
            mInversion          == other.mInversion &&
            mAlteration         == other.mAlteration &&
            mSuspendedDegree	== other.mSuspendedDegree &&
            mAddedDegree        == other.mAddedDegree &&
            mSecondaryDegree	== other.mSecondaryDegree
           )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(const Chord& other) const
    {
        if (!(*this == other))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

//=====================================================================================================================
//	METHODS
//=====================================================================================================================

    std::string toString();
    std::string printDegree(Mode iRelativeMode = Ionian, ModeType iModeType = NaturalMode);
    Alteration calculateSharpOrFlat(Note iScale, Mode iMode, ModeType iModeType);
    Note calculateEquivalentIonianRoot(Note iScale, Mode iMode, ModeType iModeType);
    // PRINTING METHODS

    // All defaults values to NoDefinedX to use Chord members value a priori
    std::string printChord(Mode iMode = NoDefinedMode, ModeType iModeType = NoDefinedModeType, Note iScale = NoDefinedNote);

    // Take and int value and return note string according to MIDI reference (0/12/24/26/48/60/...  = C)
    // Do not return octave number
    std::string intToNote(int iNoteValue, Alteration iSharpOrFlat = Sharp);

}; // class Chord


#endif // CHORD_H
