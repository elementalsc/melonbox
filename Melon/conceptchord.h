#ifndef CHORD_H
#define CHORD_H


#include <string>

enum Note
{
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




class ConceptChord
{

public:

    int mDegree;
    Triad           mTriad              = NoDefinedTriad;
    Inversion       mInversion          = Root;
    Alteration      mAlteration         = NoAlteration;
    SuspendedDegree mSuspendedDegree	= NoSuspendedDegree;
    AddedDegree     mAddedDegree        = NoAddedDegree;
    SecondaryDegree mSecondaryDegree	= NoSecondaryDegree;

    virtual ~ConceptChord() = default;

//=====================================================================================================================
// CONSTRUCTORS
//=====================================================================================================================

    ConceptChord() {}

    ConceptChord(int degree) :
        mDegree(degree)
    {}

    ConceptChord(int degree, Triad triad) :
        mDegree(degree),
        mTriad(triad)
    {}

    ConceptChord(int degree, Inversion inversion) :
        mDegree(degree),
        mInversion(inversion)
    {}

    ConceptChord(int degree, Triad triad, Alteration alteration) :
        mDegree(degree),
        mTriad(triad),
        mAlteration(alteration)
    {}

    ConceptChord(int degree, Triad triad, Inversion inversion) :
        mDegree(degree),
        mTriad(triad),
        mInversion(inversion)
    {}

    ConceptChord(int degree, Triad triad, Inversion inversion, Alteration alteration) :
        mDegree(degree),
        mTriad(triad),
        mInversion(inversion),
        mAlteration(alteration)
    {}

//=====================================================================================================================
//	FLUENT SETTERS
//=====================================================================================================================

    ConceptChord& Triad(Triad triad)
    {
        mTriad = triad;
        return *this;
    }

    ConceptChord& Inversion(Inversion inversion)
    {
        mInversion = inversion;
        return *this;
    }

    ConceptChord& Alteration(Alteration alteration)
    {
        mAlteration = alteration;
        return *this;
    }

    ConceptChord& AddedDegree(AddedDegree addedDegree)
    {
        mAddedDegree = addedDegree;
        return *this;
    }

    ConceptChord& SuspendedDegree(SuspendedDegree suspendedDegree)
    {
        mSuspendedDegree = suspendedDegree;
        return *this;
    }
    ConceptChord& SecondaryDegree(SecondaryDegree secondaryDegree)
    {
        mSecondaryDegree = secondaryDegree;
        return *this;
    }

//=====================================================================================================================
//	OPERATORS
//=====================================================================================================================

    bool operator==(const ConceptChord& other) const
    {
        if (
            mDegree		== other.mDegree &&
            mTriad		== other.mTriad &&
            mInversion		== other.mInversion &&
            mAlteration		== other.mAlteration &&
            mSuspendedDegree	== other.mSuspendedDegree &&
            mAddedDegree	== other.mAddedDegree &&
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

    bool operator!=(const ConceptChord& other) const
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
};


#endif // CHORD_H
