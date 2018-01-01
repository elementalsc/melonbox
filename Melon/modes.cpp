#include "Modes.h"
#include "Progression.h"

int
Intervals(Mode mode, int degree)
{
    switch (mode)
    {
    case 1: return ionianInterval[degree];
    case 2: return dorianInterval[degree];
    case 3: return phrygianInterval[degree];
    case 4: return lydianInterval[degree];
    case 5: return mixolydianInterval[degree];
    case 6: return aeolianInterval[degree];
    case 7: return locrianInterval[degree];
    default: return -1;
    }
}

int
NextTriad(Mode mode, int degree)
{
    switch (mode)
    {
    case 1: return ionianNextTriad[degree];
    case 2: return dorianNextTriad[degree];
    case 3: return phrygianNextTriad[degree];
    case 4: return lydianNextTriad[degree];
    case 5: return mixolydianNextTriad[degree];
    case 6: return aeolianNextTriad[degree];
    case 7: return locrianNextTriad[degree];
    default: return -1;
    }
}

int
Position(Mode mode, int degree)
{
    switch (mode)
    {
    case 1: return ionianPosition[degree];
    case 2: return dorianPosition[degree];
    case 3: return phrygianPosition[degree];
    case 4: return lydianPosition[degree];
    case 5: return mixolydianPosition[degree];
    case 6: return aeolianPosition[degree];
    case 7: return locrianPosition[degree];
    default: return -1;
    }
}

//=====================================================================================================================
//	INSERTING MODE CHORDS
//=====================================================================================================================
int
applyModeTriads(Progression& oProgression, Mode iMode = Ionian, ModeType iModeType = NaturalMode)
{
    MelonLogger* logger = logger->getInstance();

    for(int i = 0; i < oProgression.size(); ++i)
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
}



