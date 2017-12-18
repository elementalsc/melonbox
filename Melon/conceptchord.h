#ifndef CONCEPTCHORD_H
#define CONCEPTCHORD_H

#include <string>
#include "Chord.h"

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

#endif // CONCEPTCHORD_H
