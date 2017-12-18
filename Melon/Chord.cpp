#ifndef CONCEPTCHORD_CPP
#define CONCEPTCHORD_CPP

#include "MelonUtil.h"
#include "ConceptChord.h"

using namespace std;


string
ConceptChord::toString()
{
    string oString;


    switch (mDegree)
    {
    case 1: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("i")   : oString.append("I");	break;
    case 2: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("ii")  : oString.append("II");	break;
    case 3: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("iii") : oString.append("III");	break;
    case 4: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("iv")  : oString.append("IV");	break;
    case 5: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("v")   : oString.append("V");	break;
    case 6: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("vi")  : oString.append("VI");	break;
    case 7: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("vii") : oString.append("VII");	break;
    default: break;
    }

    switch (mTriad)
    {
    case AugmentedTriad:
        oString.append("+");
        break;
    case DiminishedTriad:
        oString.append("°");
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
    case IV:    oString.insert(0, "IV/"); break;
    case V:     oString.insert(0, "V/"); break;
    case VII:   oString.insert(0, "VII/"); break;
    default: break;
    }

    return oString;
}



#endif // CONCEPTCHORD_CPP
