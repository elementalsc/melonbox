#include "Modes.h"
#include "Chord.h"
#include "Progression.h"

/* useless?
ModeType
getModeType(Mode mode)
{
    switch (mode)
    {
    case 1:
    case 4:
    case 5:
        return ModeType::MajorMode; break;

    case 2:
    case 3:
    case 6:
        return ModeType::MinorMode; break;

    case 7:
        return ModeType::DiminishedMode; break;

    default:
        return ModeType::NoDefinedModeType; break;
    }
}
*/

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

//
//	INSERTING MODE CHORDS
//
void
applyModeTriads(Progression& oProgression, Mode iMode, bool iNaturalOrHarmonic)
{
    for(int i = 0; i < oProgression.size(); ++i)
    {
        oProgression[i].mTriad = mNaturalTriads[((oProgression[i].mDegree - 1) + (iMode - 1)) % 7];
    }
}
