#ifndef CHORD_H
#define CHORD_H

#include <string>
#include <vector>

enum Note
{
    NoDefinedNote = 0,
    C   = 1,
    Cs  = 2,
    Db  = 2,
    D   = 3,
    Ds  = 4,
    Eb  = 4,
    E   = 5,
    F   = 6,
    Fs  = 7,
    Gb  = 7,
    G   = 8,
    Gs  = 9,
    Ab  = 9,
    A   = 10,
    As  = 11,
    Bb  = 11,
    B   = 12
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

public:

    int              mDegree;
    std::vector<int> mNotes;
    Note             mRoot               = NoDefinedNote;
    Note             mScale              = NoDefinedNote;
    Triad            mTriad              = NoDefinedTriad;
    Inversion        mInversion          = Root;
    Alteration       mAlteration         = NoAlteration;
    SuspendedDegree  mSuspendedDegree	 = NoSuspendedDegree;
    AddedDegree      mAddedDegree        = NoAddedDegree;
    SecondaryDegree  mSecondaryDegree	 = NoSecondaryDegree;

    virtual ~Chord() = default;

//=====================================================================================================================
// CONSTRUCTORS
//=====================================================================================================================

    Chord() {}

    Chord(int degree) :
        mDegree(degree)
    {}

    Chord(int degree, Triad triad) :
        mDegree(degree),
        mTriad(triad)
    {}

    Chord(int degree, Inversion inversion) :
        mDegree(degree),
        mInversion(inversion)
    {}

    Chord(int degree, Triad triad, Alteration alteration) :
        mDegree(degree),
        mTriad(triad),
        mAlteration(alteration)
    {}

    Chord(int degree, Triad triad, Inversion inversion) :
        mDegree(degree),
        mTriad(triad),
        mInversion(inversion)
    {}

    Chord(int degree, Triad triad, Inversion inversion, Alteration alteration) :
        mDegree(degree),
        mTriad(triad),
        mInversion(inversion),
        mAlteration(alteration)
    {}

//=====================================================================================================================
//	FLUENT SETTERS
//=====================================================================================================================

    Chord& Triad(Triad triad)
    {
        mTriad = triad;
        return *this;
    }

    Chord& Inversion(Inversion inversion)
    {
        mInversion = inversion;
        return *this;
    }

    Chord& Alteration(Alteration alteration)
    {
        mAlteration = alteration;
        return *this;
    }

    Chord& AddedDegree(AddedDegree addedDegree)
    {
        mAddedDegree = addedDegree;
        return *this;
    }

    Chord& SuspendedDegree(SuspendedDegree suspendedDegree)
    {
        mSuspendedDegree = suspendedDegree;
        return *this;
    }
    Chord& SecondaryDegree(SecondaryDegree secondaryDegree)
    {
        mSecondaryDegree = secondaryDegree;
        return *this;
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


}; // class Chord


#endif // CHORD_H
