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
    // TODO :Not managed yet
    default: break;
    }

    switch (mAddedDegree)
    {
    // TODO :Not managed yet
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
Chord::printChord(Mode iMode, ModeType iModeType, Note iScale)
{
    std::string oString;
    Mode        wMode       = iMode;
    ModeType    wModeType   = iModeType;
    Note        wScale      = iScale;

    // Validating input and member variable
    if(iMode == NoDefinedMode)
    {
        if(mMode == NoDefinedMode)
        {
            wMode = Ionian;
            logger->log("No chord mode specified, Ionian mode assumed", Warning);
        }
        else
        {
            wMode = mMode;
        }
    }

    if(iModeType == NoDefinedModeType)
    {
        if(mModeType == NoDefinedModeType)
        {
            wModeType = NaturalMode;
            logger->log("No chord mode type specified, Natural mode type assumed", Warning);
        }
        else
        {
            wModeType = mModeType;
        }
    }

    if(iScale == NoDefinedNote)
    {
        if(mScale == NoDefinedNote)
        {
            wScale = C;
            logger->log("No chord root specified, C assumed", Warning);
        }
        else
        {
            wScale = iScale;
        }
    }

    if(!mDegree)
    {
        logger->log("Chord has no specified degree", Error);
        return "";
    }

    int wNoteValue = 0;
    Alteration wSharpOrFlat = calculateSharpOrFlat(wScale, wMode, wModeType);

    // Getting count of semitones separating note from scale root
    int wIntervalFromRoot = 0;
    wIntervalFromRoot = calculateModeDegreeInterval(mDegree, wMode, wModeType);
    wIntervalFromRoot = rootDegreeInterval(mDegree, wMode, wModeType);

    // Preparing secondary degree added interval value
    switch(mSecondaryDegree)
    {
    case  IV: wNoteValue = 5;  break;
    case   V: wNoteValue = 7;  break;
    case VII: wNoteValue = 11; break;
    default : break;
    }

    //
    //
    //
    // fill all chord objetc members when initializing progression.
    //
    //
    //
    //

    // Converting result between 0 and 11
    wNoteValue += (wScale + wIntervalFromRoot + mAlteration) % 12;

    oString.append(intToNote(wNoteValue,wSharpOrFlat));

    switch (mTriad)
    {
    case MinorTriad:
        oString.append("m");
        break;

    case AugmentedTriad:
        oString.append("+");
        break;

    case DiminishedTriad:
        oString.append("°");
        break;

    default: break;
    }

    switch (mSuspendedDegree)
    {
    case Sus2: oString.append("sus2"); break;
    case Sus4: oString.append("sus4"); break;
    default: break;
    }

    switch (mAddedDegree)
    {
    // TODO :Not managed yet
    default: break;
    }


    switch(mInversion)
    {
    case (First | Six):
        oString.append("/");
        if((mTriad == MinorTriad) | (mTriad == DiminishedTriad))
        {
            oString.append(intToNote(wNoteValue + 3, wSharpOrFlat));
        }
        else
        {
            oString.append(intToNote(wNoteValue + 4, wSharpOrFlat));
        }
        break;

    case (Second | SixFour):
        oString.append("/");
        oString.append(intToNote(wNoteValue + 7, wSharpOrFlat));
        break;

    case Third:
        // TODO :Not managed yet
        break;

    default: break;
    }

    return oString;
}


std::string
Chord::intToNote(int iNoteValue, Alteration iSharpOrFlat)
{
    switch(iNoteValue % 12)
    {
    case  C         :    return "C";
    case (Cs | Db)  :    return iSharpOrFlat ? "C#" : "Db";
    case  D         :    return "D";
    case (Ds | Eb)  :    return iSharpOrFlat ? "D#" : "Eb";
    case  E         :    return "E";
    case  F         :    return "F";
    case (Fs | Gb)  :    return iSharpOrFlat ? "F#" : "Gb";
    case  G         :    return "G";
    case (Gs | Ab)  :    return iSharpOrFlat ? "G#" : "Ab";
    case  A         :    return "A";
    case (As | Bb)  :    return iSharpOrFlat ? "A#" : "Bb";
    case  B         :    return "B";
    default:
        logger->log("No valid note passed to intToNote()",Error);
        return "";
    }
}

Alteration
Chord::calculateSharpOrFlat(Note iScale, Mode iMode, ModeType iModeType)
{
    switch(calculateEquivalentIonianRoot(iScale, iMode, iModeType))
    {
    case C :
    case G :
    case D :
    case A :
    case E :
    case B :
    case (Fs | Gb) :
        return Sharp;

    case F :
    case Bb :
    case Eb :
    case Ab :
    case Db :
        return Flat;

    default :
        logger->log("Unable to calculate Sharp or Flat representation", Error);
        return NoAlteration;
    }
}

Note
Chord::calculateEquivalentIonianRoot(Note iScale, Mode iMode, ModeType iModeType)
{
    int wIonianNoteDistance = 0;

    // Natural Ionian intervals vector
    std::vector<int> wBaseIntervalVector  = { 2,2,1,2,2,2,1 };

    if(iModeType == HarmonicMode)
    {
        // Adjust vector from natural to harmonic interval
        wBaseIntervalVector[3] += 1;
        wBaseIntervalVector[4] -= 1;
    }

    // Sum remaining intervals to establish distance from relative Ionian root note
    std::accumulate(wBaseIntervalVector.begin() + wBaseIntervalVector[iMode - 1], wBaseIntervalVector.end(), wIonianNoteDistance);

    return static_cast<Note>((iScale + wIonianNoteDistance) % 12);
}
