#pragma once
#include "MelonUtil.h"
#include "Chords.h"
#include "ConceptChord.cpp"

typedef vector<int> NoteVector;



enum Mode
{
    Ionian = 1,
    Dorian = 2,
    Phrygian = 3,
    Lydian = 4,
    Mixolydian = 5,
    Aeolian = 6,
    Locrian = 7
};

enum ModeType
{
    NoDefinedMode = 0,
    MajorMode = 1,
    MinorMode = 2,
    DiminishedMode = 3
};

ModeType getModeType(Mode mode)
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
        return ModeType::NoDefinedMode; break;
    }
}


//
// MODE SCALE INTERVALS
//
static const NoteVector ionianInterval		= { NULL,2,2,1,2,2,2,1 };
static const NoteVector dorianInterval		= { NULL,2,1,2,2,2,1,2 };
static const NoteVector phrygianInterval	= { NULL,1,2,2,2,1,2,2 };
static const NoteVector lydianInterval		= { NULL,2,2,2,1,2,2,1 };
static const NoteVector mixolydianInterval	= { NULL,2,2,1,2,2,1,2 };
static const NoteVector aeolianInterval		= { NULL,2,1,2,2,1,2,2 };
static const NoteVector locrianInterval		= { NULL,1,2,2,1,2,2,2 };

int Invervals(Mode mode, int degree)
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

//
// MODE NEXT TRIAD STEP
//
static const NoteVector ionianNextTriad		= { NULL,4,3,3,4,4,3,3 };
static const NoteVector dorianNextTriad		= { NULL,3,3,4,4,3,3,4 };
static const NoteVector phrygianNextTriad	= { NULL,3,4,4,3,3,4,3 };
static const NoteVector lydianNextTriad		= { NULL,4,4,3,3,4,3,3 };
static const NoteVector mixolydianNextTriad = { NULL,4,3,3,4,3,3,4 };
static const NoteVector aeolianNextTriad	= { NULL,3,3,4,3,3,4,4 };
static const NoteVector locrianNextTriad	= { NULL,3,4,3,3,4,4,3 };

int NextTriad(Mode mode, int degree)
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

//
// MODE SCALE NOTE POSITION
//
static const NoteVector ionianPosition		= { NULL,0,2,4,5,7,9,11 };
static const NoteVector dorianPosition		= { NULL,0,2,3,5,7,9,10 };
static const NoteVector phrygianPosition	= { NULL,0,1,3,5,7,8,10 };
static const NoteVector lydianPosition		= { NULL,0,2,4,6,7,9,11 };
static const NoteVector mixolydianPosition	= { NULL,0,2,4,5,7,9,10 };
static const NoteVector aeolianPosition		= { NULL,0,2,3,5,7,8,10 };
static const NoteVector locrianPosition		= { NULL,0,1,3,5,6,8,10 };


int Position(Mode mode, int degree)
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

