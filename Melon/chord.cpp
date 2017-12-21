#include "MelonUtil.h"
#include "Chord.h"

std::string
Chord::toString()
{
    std::string oString;

    switch (mSecondaryDegree)
    {
    case IV:    oString.append("IV/");   break;
    case V:     oString.append("V/");    break;
    case VII:   oString.append("VII/");  break;
    default: break;
    }

    switch (mDegree)
    {
    case 1: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("i")   : oString.append("I");      break;
    case 2: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("ii")  : oString.append("II");     break;
    case 3: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("iii") : oString.append("III");	break;
    case 4: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("iv")  : oString.append("IV");     break;
    case 5: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("v")   : oString.append("V");      break;
    case 6: (mTriad == MinorTriad || mTriad == DiminishedTriad) ? oString.append("vi")  : oString.append("VI");     break;
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
    default:
        oString.append("");
        break;

    }

    return oString;
}

std::string
Chord::printChord(Mode iMode, ModeType iModeType)
{
    std::string oString;

    int wIntervalFromRoot = calculateModeDegreeInterval(mDegree, iMode, iModeType);
    // prendre root
    //mScale
    // additionner le degré selon l'intervalle
        // selon le mode, déterminer combien ajouter
    // additionner ou soustraire selon altération
    // additionner 5(IV), 7(V) ou 11(VII) si c'est un degré secondaire

    return oString;
}
