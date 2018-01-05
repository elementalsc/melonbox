#ifndef MODES_H
#define MODES_H

#include <vector>
#include <iostream>
#include "MelonLogger.h"

typedef std::vector<int> NoteVector;

#define SUCCESS 1
#define FAILURE 0

enum Mode
{
    NoDefinedMode   = 0,
    Ionian          = 1,
    Dorian          = 2,
    Phrygian        = 3,
    Lydian          = 4,
    Mixolydian      = 5,
    Aeolian         = 6,
    Locrian         = 7
};

enum ModeType
{
    NoDefinedModeType   = 0,
    NaturalMode         = 1,
    HarmonicMode        = 2
};

//=====================================================================================================================
//	SCALES
//=====================================================================================================================

static const NoteVector naturalLydianScale		= { NULL,0,2,4,6,7,9,11 };
static const NoteVector naturalIonianScale      = { NULL,0,2,4,5,7,9,11 };
static const NoteVector naturalMixolydianScale	= { NULL,0,2,4,5,7,9,10 };
static const NoteVector naturalDorianScale		= { NULL,0,2,3,5,7,9,10 };
static const NoteVector naturalAeolianScale		= { NULL,0,2,3,5,7,8,10 };
static const NoteVector naturalPhrygianScale	= { NULL,0,1,3,5,7,8,10 };
static const NoteVector naturalLocrianScale		= { NULL,0,1,3,5,6,8,10 };

static const NoteVector harmonicIonianScale		= { NULL,0,2,4,5,8,9,11 };
static const NoteVector harmonicDorianScale		= { NULL,0,2,3,6,7,9,10 };
static const NoteVector harmonicPhrygianScale	= { NULL,0,1,4,5,7,8,10 };
static const NoteVector harmonicLydianScale		= { NULL,0,3,4,6,7,9,11 };
static const NoteVector harmonicMixolydianScale	= { NULL,0,1,3,4,6,8,9  };
static const NoteVector harmonicAeolianScale	= { NULL,0,2,3,5,7,8,11 };
static const NoteVector harmonicLocrianScale	= { NULL,0,1,3,5,6,9,10 };

//=====================================================================================================================
//	METHODS
//=====================================================================================================================

int applyModeTriads(Progression& oProgression, Mode iMode, ModeType iModeType);
int calculateModeDegreeInterval(int iDegree, Mode iMode, ModeType iModeType);
std::vector<int> getModeScale(Mode iMode, ModeType iModeType);
int rootDegreeInterval(int iDegree, Mode iMode, ModeType iModeType);
bool isMajorMode(Mode iMode);
#endif // MODES_H
