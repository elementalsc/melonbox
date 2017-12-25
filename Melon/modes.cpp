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
            oProgression[i].mTriad = mNaturalTriads[((oProgression[i].mDegree - 1) + (iMode - 1)) % 7];
            logger->getInstance()->logProgression(oProgression, "Modes applied : ");
            return SUCCESS;
            break;
        case HarmonicMode :
            oProgression[i].mTriad = mHarmonicTriads[((oProgression[i].mDegree - 1) + (iMode - 1)) % 7];
            logger->getInstance()->logProgression(oProgression, "Modes applied : ");
            return SUCCESS;
            break;
        default:
            logger->getInstance()->log("Failed to apply mode");
            return FAILURE;
            break;
        }
    }
    logger->getInstance()->log("Failed to apply mode");
    return FAILURE;
}

//=====================================================================================================================
//	CALCULATE MODE INTERVAL
//=====================================================================================================================
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



