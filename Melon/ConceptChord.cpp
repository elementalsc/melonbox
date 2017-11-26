#pragma once
#include "MelonUtil.h"
#include "Chords.h"

using namespace std;

struct ConceptChord
{

    int mDegree;
    Triad			mTriad				= NoDefinedTriad;
    Inversion		mInversion			= Root;
    Alteration		mAlteration			= NoAlteration;
    SuspendedDegree mSuspendedDegree	= NoSuspendedDegree;
    AddedDegree		mAddedDegree		= NoAddedDegree;
    SecondaryDegree mSecondaryDegree	= NoSecondaryDegree;

    virtual ~ConceptChord() = default;


    //
    // CONSTRUCTORS
    //

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

    //
    //	FLUENT SETTERS
    //

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

    string toString()
    {
        string oString;


        switch (mDegree)
        {
        case 1: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("i")   : oString.append("I");		break;
        case 2: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("ii")	: oString.append("II");		break;
        case 3: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("iii")	: oString.append("III");	break;
        case 4: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("iv")	: oString.append("IV");		break;
        case 5: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("v")   : oString.append("V");		break;
        case 6: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("vi")	: oString.append("VI");		break;
        case 7: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("vii")	: oString.append("VII");	break;
        default: break;
        }

        switch (mTriad)
        {
        case AugmentedTriad:
            oString.append("+");
            break;
        case DiminishedTriad:
            oString.append("�");
            break;
        default: break;
        }

        switch (mAlteration)
        {
        case Flat:
            oString.append("b");
            break;
        case Sharp:
            oString.append("#");
            break;
        default: break;
        }

        switch (mSuspendedDegree)
        {
        default: break;
        }

        switch (mAddedDegree)
        {
        default: break;
        }

        switch (mInversion)
        {
            //
            // TODO: Consider 7th chords
            //
        case First :
            oString.append("6");
            break;

        case Second :

            oString.append("64");
            break;

        case Third:
            oString.append("");
            break;

        default: break;
        }

        switch (mSecondaryDegree)
        {
        case IV:	oString.insert(0, "IV/"); break;
        case V:     oString.insert(0, "V/"); break;
        case VII:	oString.insert(0, "VII/"); break;
        default: break;
        }

        return oString;
    }

    //
    //	OPERATORS
    //

    bool operator==(const ConceptChord& other) const
    {
        if (
            mDegree				== other.mDegree &&
            mTriad				== other.mTriad &&
            mInversion			== other.mInversion &&
            mAlteration			== other.mAlteration &&
            mSuspendedDegree	== other.mSuspendedDegree &&
            mAddedDegree		== other.mAddedDegree &&
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
};
