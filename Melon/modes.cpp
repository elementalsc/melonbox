#include "Modes.h"
#include "Progression.h"

//=====================================================================================================================
//	INSERTING MODE CHORDS
//=====================================================================================================================
int
applyModeTriads(Progression& oProgression, Mode iMode, ModeType iModeType)
{
    MelonLogger* logger = logger->getInstance();

    for(int i = 0; i < oProgression.size(); ++i)
    {
        if(oProgression[i].getTriad() == NoDefinedTriad)
        {
            switch(iModeType)
            {
            case NaturalMode :
                oProgression[i].setTriad(mNaturalTriads[((oProgression[i].getDegree() - 1) + (iMode - 1)) % 7]);
                logger->getInstance()->logProgression(oProgression, "Applying mode : ");
                break;
            case HarmonicMode :
                oProgression[i].setTriad(mHarmonicTriads[((oProgression[i].getDegree() - 1) + (iMode - 1)) % 7]);
                logger->getInstance()->logProgression(oProgression, "Applying mode : ");
                break;
            default:
                logger->getInstance()->log("Failed to apply mode");
                return FAILURE;
                break;
            }
        }
        else
        {
            std::string wLogMessage = "Chord ";
            wLogMessage.append(std::to_string(i));
            wLogMessage.append(" already has a defined triad : ");
            logger->getInstance()->logProgression(oProgression, wLogMessage);
        }
    }
    return SUCCESS;
}

//=====================================================================================================================
//	CALCULATE MODE INTERVAL
//=====================================================================================================================
int
rootDegreeInterval(int iDegree, Mode iMode, ModeType iModeType)
{
    MelonLogger* logger = logger->getInstance();

    switch (iModeType)
    {
    case NaturalMode:
        switch(iMode)
        {
        case Ionian     : return naturalIonianScale[iDegree];
        case Dorian     : return naturalDorianScale[iDegree];
        case Phrygian   : return naturalPhrygianScale[iDegree];
        case Lydian     : return naturalLydianScale[iDegree];
        case Mixolydian : return naturalMixolydianScale[iDegree];
        case Aeolian    : return naturalAeolianScale[iDegree];
        case Locrian    : return naturalLocrianScale[iDegree];
        default:
            logger->getInstance()->log("Failed to evaluate Mode");
            return -1;
        }

    case HarmonicMode:
        switch(iMode)
        {
        case Ionian     : return harmonicIonianScale[iDegree];
        case Dorian     : return harmonicDorianScale[iDegree];
        case Phrygian   : return harmonicPhrygianScale[iDegree];
        case Lydian     : return harmonicLydianScale[iDegree];
        case Mixolydian : return harmonicMixolydianScale[iDegree];
        case Aeolian    : return harmonicAeolianScale[iDegree];
        case Locrian    : return harmonicLocrianScale[iDegree];
        default:
            logger->getInstance()->log("Failed to evaluate Mode");
            return -1;
        }

    default:
        logger->getInstance()->log("Failed to evaluate ModeType");
        return -1;
    }

}

int
calculateModeDegreeInterval(int iDegree, Mode iMode = Ionian, ModeType iModeType = NaturalMode)
{
    return getModeScale(iMode, iModeType)[iDegree];

    /*
    int oIntervalValue = 0;

    // Natural Ionian intervals vector
    std::vector<int> wBaseIntervalVector  = { 2,2,1,2,2,2,1 };

    if(iModeType == HarmonicMode)
    {
        // Adjust vector from natural to harmonic interval
        wBaseIntervalVector[3] += 1;
        wBaseIntervalVector[4] -= 1;
    }

    // Cycle wBaseIntervalVector according to iMode to have good root-degree interval for asked mode
    std::vector<int> wOutputIntervalVector;
    for(int i = 0; i < 7; ++i)
    {
        wOutputIntervalVector.push_back(wBaseIntervalVector[ (i + iMode - 1) % 7 ]);
    }

    for(int i = 0; (i+1) < iDegree; ++i)
    {
        oIntervalValue += wOutputIntervalVector[i];
    }

    return oIntervalValue;
    */
}

bool
isMajorMode(Mode iMode)
{
    MelonLogger* logger = logger->getInstance();

    switch(iMode)
    {
    case Ionian :
    case Lydian :
    case Mixolydian :
        return true;
    case Dorian :
    case Phrygian :
    case Aeolian :
    case Locrian :
        return false;
    default:
        logger->log("Unable to evaluate if mode is Major or Minor",Error);
        return false;
    }
}

std::vector<int>
getModeScale(Mode iMode, ModeType iModeType)
{
    MelonLogger* logger = logger->getInstance();

    switch(iModeType)
    {
    case NaturalMode :
        switch(iMode)
        {
        case Ionian :       return naturalIonianScale;
        case Dorian :       return naturalDorianScale;
        case Phrygian :     return naturalPhrygianScale;
        case Lydian :       return naturalLydianScale;
        case Mixolydian :   return naturalMixolydianScale;
        case Aeolian :      return naturalAeolianScale;
        case Locrian :      return naturalLocrianScale;
        default :           goto error;
        }

    case HarmonicMode :
        switch(iMode)
        {
        case Ionian :       return harmonicIonianScale;
        case Dorian :       return harmonicDorianScale;
        case Phrygian :     return harmonicPhrygianScale;
        case Lydian :       return harmonicLydianScale;
        case Mixolydian :   return harmonicMixolydianScale;
        case Aeolian :      return harmonicAeolianScale;
        case Locrian :      return harmonicLocrianScale;
        default :           goto error;
        }

    default :           goto error;
    }

    error:
    logger->log("Not able to return scale for unspecified mode", Error);
    return {};
}

